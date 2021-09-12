#include "BridgingScene.hpp"
#include "PlayScene.hpp"
#include "AudioHelper.hpp"
#include "Slider.hpp"
#include "LOG.hpp"
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void BridgingScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    //int to string.
    int next_stage = BridgeID + 1;
    string nextStage = to_string(next_stage);
  /*  stringstream ss;
    int next_stage = BridgeID + 1;
    ss<<next_stage;
     string nextStage= next_stage.str();*/
    //¥ÑBridgeID decides what next stage.
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 250, halfH / 2 - 50, 500, 100);
    btn->SetOnClickCallback(std::bind(&BridgingScene::PlayOnClick, this, 2,2,2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next stage", "pirulen.ttf", 36, halfW-50, halfH / 2, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label( nextStage, "pirulen.ttf", 36, halfW+200, halfH / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 250, halfH * 3 / 2 - 50, 500, 100);
    btn->SetOnClickCallback(std::bind(&BridgingScene::PlayOnClick, this, 1, 1, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back to menu...", "pirulen.ttf", 36, halfW-5, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    //sliders.
  /*  Slider *sliderBGM, *sliderSFX;

    sliderBGM = new Slider(40 + halfW - 95, halfH - 50 - 2, 190, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&StageSelectScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH - 50, 255, 255, 255, 255, 0.5, 0.5));


    sliderSFX = new Slider(40 + halfW - 95, halfH + 50 - 2, 190, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&StageSelectScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH + 50, 255, 255, 255, 255, 0.5, 0.5));


    // Not a safe way, however we only free while change scene, so it's fine.
    bgmInstance = al_create_sample_instance(Engine::Resources::GetInstance().GetSample("Feuerwerk.ogg").get());
    al_set_sample_instance_playmode(bgmInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgmInstance, al_get_default_mixer());
    al_play_sample_instance(bgmInstance);
    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);*/
}
void BridgingScene::PlayOnClick(int stage, int BamID, int HPID) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    if (stage == 1){
        Engine::GameEngine::GetInstance().ChangeScene("Start");
    }
    else if (stage == 2){
        scene->MapId = stage;
        scene->HPbottleID = HPID;
        scene->BambooID = BamID;
        Engine::GameEngine::GetInstance().ChangeScene("play");
    }


}
void BridgingScene::BGMSlideOnValueChanged(float value) {
    al_set_sample_instance_gain(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void BridgingScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}

