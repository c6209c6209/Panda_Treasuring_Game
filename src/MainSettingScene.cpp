#include "MainSettingScene.hpp"
#include "PlayScene.hpp"
#include "AudioHelper.hpp"
//#include "Slider.hpp"
#include "LOG.hpp"

void MainSettingScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("stage-select/blue.png", halfW - 200, halfH / 5 - 50, 400, 100));
	AddNewObject(new Engine::Label("Mode", "pirulen.ttf", 48, halfW, halfH / 5, 0, 0, 0, 255, 0.5, 0.5));

    /*btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 5 - 50, 400, 100);
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Mode", "pirulen.ttf", 48, halfW, halfH / 5, 0, 0, 0, 255, 0.5, 0.5));*/

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 350, halfH * 2 / 3 - 50, 700, 100);
    btn->SetOnClickCallback(std::bind(&MainSettingScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Single Player", "pirulen.ttf", 30, halfW, halfH * 2 / 3, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 350, halfH * 17 / 15 - 50, 700, 100);
    btn->SetOnClickCallback(std::bind(&MainSettingScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Two Players - Cooperate", "pirulen.ttf", 30, halfW, halfH * 17 / 15, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 350, halfH * 8 / 5 - 50, 700, 100);
    btn->SetOnClickCallback(std::bind(&MainSettingScene::PlayOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Two Players - Compete", "pirulen.ttf", 30, halfW, halfH * 8 / 5 , 0, 0, 0, 255, 0.5, 0.5));

    //sliders.
    /*Slider *sliderBGM, *sliderSFX;

    sliderBGM = new Slider(40 + halfW - 95, halfH - 50 - 2, 190, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&StageSelectScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH - 50, 255, 255, 255, 255, 0.5, 0.5));


    sliderSFX = new Slider(40 + halfW - 95, halfH + 50 - 2, 190, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&StageSelectScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH + 50, 255, 255, 255, 255, 0.5, 0.5));*/


    // Not a safe way, however we only free while change scene, so it's fine.
    bgmInstance = al_create_sample_instance(Engine::Resources::GetInstance().GetSample("Feuerwerk.ogg").get());
    al_set_sample_instance_playmode(bgmInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgmInstance, al_get_default_mixer());
    al_play_sample_instance(bgmInstance);
    /*sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);*/
}
void MainSettingScene::PlayOnClick(int mode) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    //scene->MapId = stage;
    scene->MapId = 1;
    if (mode == 1){
        Engine::GameEngine::GetInstance().ChangeScene("single-setting");
    }
    else if (mode == 2){
        Engine::GameEngine::GetInstance().ChangeScene("two-cooperate-setting");
    }
    else if (mode == 3){
        Engine::GameEngine::GetInstance().ChangeScene("two-cooperate-setting");
    }

}
/*void MainSettingScene::BGMSlideOnValueChanged(float value) {
    al_set_sample_instance_gain(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void MainSettingScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}*/
