#include "SingleSettingScene.hpp"
#include "PlayScene.hpp"
#include "AudioHelper.hpp"
#include "Slider.hpp"
#include "LOG.hpp"

void SingleSettingScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    AddNewControlObject(UIGroup = new Group());
    AddNewObject(CharacterGroup = new Group());

	UIGroup->AddNewObject(new Engine::Image("stage-select/blue.png", halfW - 400, halfH / 5 - 50, 800, 100));
	AddNewObject(new Engine::Label("Choose Your Panda", "pirulen.ttf", 48, halfW, halfH / 5, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 550, halfH / 5 + 80, 350, 350);
    btn->SetOnClickCallback(std::bind(&SingleSettingScene::PlayOnClick, this, 1, 1, 1));
    AddNewControlObject(btn);

    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("play/cspanda.png", halfW - 550, halfH / 5 + 80, 350, 350));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 150, halfH / 5 + 80, 350, 350);
    btn->SetOnClickCallback(std::bind(&SingleSettingScene::PlayOnClick, this, 2, 1 ,1));
    AddNewControlObject(btn);

    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("play/ipepanda.png", halfW - 150, halfH / 5 + 80, 350, 350));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 260, halfH / 5 + 80, 350, 350);
    btn->SetOnClickCallback(std::bind(&SingleSettingScene::PlayOnClick, this, 3, 1, 1));
    AddNewControlObject(btn);

    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("play/nthu_panda.png", halfW + 250, halfH / 5 + 80, 350, 350));

    //sliders.
    Slider *sliderBGM, *sliderSFX;

    sliderBGM = new Slider(40 + halfW - 95, halfH * 3 / 2 - 50, 190, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&SingleSettingScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH * 3 / 2 - 48, 255, 255, 255, 255, 0.5, 0.5));

    sliderSFX = new Slider(40 + halfW - 95, halfH * 3 / 2 + 50, 190, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&SingleSettingScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH * 3 / 2 + 52, 255, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 70, halfH * 3 / 2 + 100, 130, 100);
    btn->SetOnClickCallback(std::bind(&SingleSettingScene::PlayOnClick, this, 4, 1 , 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("GO~", "pirulen.ttf", 30, halfW, halfH * 3 / 2 + 150 , 0, 0, 0, 255, 0.5, 0.5));

    // Not a safe way, however we only free while change scene, so it's fine.
    bgmInstance = al_create_sample_instance(Engine::Resources::GetInstance().GetSample("Feuerwerk.ogg").get());
    al_set_sample_instance_playmode(bgmInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgmInstance, al_get_default_mixer());
    al_play_sample_instance(bgmInstance);
    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);
}
void SingleSettingScene::PlayOnClick(int mode, int BamID, int HPID) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = 1;
    scene->BambooID = BamID;
    scene->HPbottleID = HPID;
    if (mode == 1){
        scene->Character1Id = 1;
        if (!CharacterGroup->GetObjects().empty()){
            this->CharacterGroup->RemoveObject(CharacterGroup->GetObjects().front()->GetObjectIterator());
        }
        CharacterGroup->AddNewObject(new Engine::Image("stage-select/red-rectangle.png", 170, 140, 515, 400));
    }
    else if (mode == 2){
        scene->Character1Id = 2;
        if (!CharacterGroup->GetObjects().empty()){
            this->CharacterGroup->RemoveObject(CharacterGroup->GetObjects().front()->GetObjectIterator());
        }
        CharacterGroup->AddNewObject(new Engine::Image("stage-select/red-rectangle.png", 570, 140, 515, 400));
    }
    else if (mode == 3){
        scene->Character1Id = 3;
        if (!CharacterGroup->GetObjects().empty()){
            this->CharacterGroup->RemoveObject(CharacterGroup->GetObjects().front()->GetObjectIterator());
        }
        CharacterGroup->AddNewObject(new Engine::Image("stage-select/red-rectangle.png", 980, 140, 515, 400));
    }
    else if (mode == 4){
        if (CharacterGroup->GetObjects().size() == 1){
            Engine::GameEngine::GetInstance().ChangeScene("play");
        }
    }
}
void SingleSettingScene::BGMSlideOnValueChanged(float value) {
    al_set_sample_instance_gain(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void SingleSettingScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}
