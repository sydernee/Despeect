#include "DSFlowControlDockWidget.hpp"
#include "DSTreeItem.hpp"
#include <vector>
#include <string>
#include <QAction>
#include "QDebug"


void DSFlowControlDockWidget::setupUI() {
    doConnections();

    tree_view->setModel(tree_model);

    v_layout->addWidget(tree_view);
    v_layout->addLayout(h_layout);
    h_layout->addWidget(run_all_button);
    h_layout->addWidget(run_step_button);
    h_layout->addWidget(reset_button);

    QWidget* internal_widget = new QWidget();
    internal_widget->setLayout(v_layout);
    setWidget(internal_widget);
    setWindowTitle("Flow Control");
}

void DSFlowControlDockWidget::fillQueue() {
    //FIXME Vedi sotto..
    /*
         * Meglio usare una coda di QPersistentModelIndex, per evitare successivamente di
         * non riuscire a distinguere tra utt_proc omonimi ma appartenenti ad utt_type
         * diversi, volendo selezionare quello giusto in run_step
         */
    reset_clicked();

    DSTreeItem* root = tree_model->getRoot();
    if(root) {
        for(int i = 0; i < root->childCount(); i++) {
            DSTreeItem* utt_type = root->child(i);
            for(int j = 0; j < utt_type->childCount(); j++) {
                DSTreeItem* utt_proc = utt_type->child(j);
                if(utt_proc->isChecked())
                    proc_queue.enqueue(utt_proc->data(0).toString());
            }
        }
    }
}

void DSFlowControlDockWidget::doConnections() {
    connect(run_all_button, &QPushButton::clicked, this, &DSFlowControlDockWidget::run_all_clicked);
    connect(run_step_button, &QPushButton::clicked, this, &DSFlowControlDockWidget::run_step_clicked);
    connect(reset_button, &QPushButton::clicked, this, &DSFlowControlDockWidget::reset_clicked);
}

void DSFlowControlDockWidget::run_all_clicked() {
    fillQueue();
    std::vector<std::string> proc_list;
    while(!proc_queue.isEmpty())
        proc_list.push_back(proc_queue.dequeue().toStdString());
    emit execUttProcList(proc_list);
    //TODO Set arrow icon (and select) on last processor inside the view
}

void DSFlowControlDockWidget::run_step_clicked() {
    if(proc_queue.isEmpty())
        fillQueue();
    if(!proc_queue.isEmpty()) {
        emit execUttProc(proc_queue.dequeue().toStdString());
    }
    //TODO Set arrow icon (and select) on last processor inside the view
}

void DSFlowControlDockWidget::reset_clicked() {
    proc_queue.clear();
    emit resetUtterance();
    //TODO Remove arrow icon (and select) from last processor inside the view
}

void DSFlowControlDockWidget::fetchData() { tree_model->fetchData(); }

DSFlowControlDockWidget::DSFlowControlDockWidget(QWidget *parent, DSAdapter* adapter):
    QDockWidget(parent),
    tree_model(new DSTreeModel(this, adapter)),
    tree_view(new QTreeView(this)),
    v_layout(new QVBoxLayout),
    h_layout(new QHBoxLayout),
    run_all_button(new QPushButton("Run All")),
    run_step_button(new QPushButton("Run Step")),
    reset_button(new QPushButton("Reset"))
{
    setupUI();
}
