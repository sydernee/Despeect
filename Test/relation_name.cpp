#include <gtest/gtest.h>
#include "../header/DSAdapter.hpp"
#include "../header/DSRelation.hpp"
#include "../header/DSItem.hpp"

#include <string>

using std::string;


TEST(DSAdapter, WrongRelationName) {
    DSAdapter* b=DSAdapter::createAdapter();
    string voice_path("../../Despeect/SpeectLib/voices/cmu_arctic_slt/voice.json");
    b->loadVoice(voice_path);
    b->loadText("I'm a test");
    b->execUttType("text");
    b->getRel("I'm a relation");
    EXPECT_EQ(b->hasError(),0);
}

TEST(DSAdapter, CorrectRelationName) {
    DSAdapter* b=DSAdapter::createAdapter();
    string voice_path("../../Despeect/SpeectLib/voices/cmu_arctic_slt/voice.json");
    b->loadVoice(voice_path);
    b->loadText("I'm a test");
    b->execUttType("text");
    EXPECT_EQ(b->getRel("Token")->getName(),"Token");
}
