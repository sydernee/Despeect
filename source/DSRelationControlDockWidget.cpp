#include "DSRelationControlDockWidget.hpp"


void DSRelationControlDockWidget::setupUI() {

    //start view model definition
    list_view->setModel(rel_list_model);

    QStringList strList;
    strList << "empty Relations List";
    //rel_list_model->setStringList(strList);

    // end view model definition

    // start widget definition

    viewBox = new QGroupBox(tr("Relations List"));
    buttonBox = new QDialogButtonBox;

    showAllButton = new QPushButton(tr("Show All"));

    buttonBox->addButton(showAllButton,QDialogButtonBox::ActionRole);

    // end widget definition

    // start create Layout

    QVBoxLayout* viewLayout = new QVBoxLayout;
    viewLayout->addWidget(list_view);
    viewBox->setLayout(viewLayout);

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(buttonBox);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(viewBox);
    mainLayout->addLayout(horizontalLayout);

    QWidget* internalWidget = new QWidget();
    internalWidget->setLayout(mainLayout);
    setWidget(internalWidget);
    setWindowTitle("Relation List");

    // end create Layout

}


void DSRelationControlDockWidget::doConnections() {

    QObject::connect(showAllButton,SIGNAL(clicked),this,SLOT(showAll()));
}


void DSRelationControlDockWidget::showAll() {
    rel_list_model->fetchData();
}

DSRelationControlDockWidget::DSRelationControlDockWidget(QWidget* parent,DSAdapter* adapter)
    :QDockWidget (parent)
{
    list_view = new QListView;
    rel_list_model = new DSRelListModel(this,adapter);
    setupUI();
}
