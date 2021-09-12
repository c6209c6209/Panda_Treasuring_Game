#include "TwoCooperateSettingScene.hpp"
#include "PlayScene.hpp"
#include "AudioHelper.hpp"
#include "Slider.hpp"
#include "LOG.hpp"

void TwoCooperateSettingScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    AddNewControlObject(UIGroup = new Group());
    AddNewObject(Character1Group = new Group());
    AddNewObject(Character2Group = new Group());

	UIGroup->AddNewObject(new Engine::Image("stage-select/blue.png", halfW - 400, halfH / 5 - 50, 800, 100));
	AddNewObject(new Engine::Label("Choose Your Panda", "pirulen.ttf", 48, halfW, halfH / 5, 0, 0, 0, 255, 0.5, 0.5));

	AddNewObject(new Engine::Label("Player 1", "pirulen.ttf", 48, halfW - 600, halfH / 5 + 150, 255, 102, 0, 255, 0.5, 0.5));
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 400, halfH / 5 + 80, 150, 150);
    btn->SetOnClickCallback(std::bind(&TwoCooperateSettingScene::PlayOnClick, this, 1, 1, 1));
    AddNewControlObject(btn);

    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("play/cspanda.png", halfW - 400, halfH / 5 + 80, 150, 150));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW, halfH / 5 + 80, 150, 150);
    btn->SetOnClickCallback(std::bind(&TwoCooperateSettingScene::PlayOnClick, this, 2, 1, 1));
    AddNewControlObject(btn);

    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("play/ipepanda.png", halfW, halfH / 5 + 80, 150, 150));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 400, halfH / 5 + 80, 150, 150);
    btn->SetOnClickCallback(std::bind(&TwoCooperateSettingScene::PlayOnClick, this, 3, 1, 1));
    AddNewControlObject(btn);

    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("play/nthu_panda.png", halfW + 400, halfH / 5 + 80, 150, 150));


	AddNewObject(new Engine::Label("Player 2", "pirulen.ttf", 48, halfW - 600, halfH / 5 + 350, 255, 102, 0, 255, 0.5, 0.5));
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 400, halfH / 5 + 280, 150, 150);
    btn->SetOnClickCallback(std::bind(&TwoCooperateSettingScene::PlayOnClick, this, 4, 1, 1));
    AddNewControlObject(btn);

    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("play/cspanda.png", halfW - 400, halfH / 5 + 280, 150, 150));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW, halfH / 5 + 280, 150, 150);
    btn->SetOnClickCallback(std::bind(&TwoCooperateSettingScene::PlayOnClick, this, 5, 1, 1));
    AddNewControlObject(btn);

    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("play/ipepanda.png", halfW, halfH / 5 + 280, 150, 150));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 400, halfH / 5 + 280, 150, 150);
    btn->SetOnClickCallback(std::bind(&TwoCooperateSettingScene::PlayOnClick, this, 6, 1, 1));
    AddNewControlObject(btn);

    AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("play/nthu_panda.png", halfW + 400, halfH / 5 + 280, 150, 150));


    //sliders.
    Slider *sliderBGM, *sliderSFX;

    sliderBGM = new Slider(40 + halfW - 95, halfH * 3 / 2 - 50, 190, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&TwoCooperateSettingScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH * 3 / 2 - 48, 255, 255, 255, 255, 0.5, 0.5));

    sliderSFX = new Slider(40 + halfW - 95, halfH * 3 / 2 + 50, 190, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&TwoCooperateSettingScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH * 3 / 2 + 52, 255, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 70, halfH * 3 / 2 + 100, 130, 100);
    btn->SetOnClickCallback(std::bind(&TwoCooperateSettingScene::PlayOnClick, this, 7, 1, 1));
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
void TwoCooperateSettingScene::PlayOnClick(int mode, int BamID, int HPID) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = 1;
    scene->BambooID = BamID;
    scene->HPbottleID = HPID;
    if (mode == 1){
        if (scene->Character2Id != 1){
            scene->Character1Id = 1;
            if (!Character1Group->GetObjects().empty()){
                this->Character1Group->RemoveObject(Character1Group->GetObjects().front()->GetObjectIterator());
            }
            Character1Group->AddNewObject(new Engine::Image("stage-select/red-rectangle.png", 366, 150, 220, 178));
        }
    }
    else if (mode == 2){
        if (scene->Character2Id != 2){
                scene->Character1Id = 2;
            if (!Character1Group->GetObjects().empty()){
                this->Character1Group->RemoveObject(Character1Group->GetObjects().front()->GetObjectIterator());
            }
            Character1Group->AddNewObject(new Engine::Image("stage-select/red-rectangle.png", 766, 150, 220, 178));
        }
    }
    else if (mode == 3){
        if (scene->Character2Id != 3){
            scene->Character1Id = 3;
            if (!Character1Group->GetObjects().empty()){
                this->Character1Group->RemoveObject(Character1Group->GetObjects().front()->GetObjectIterator());
            }
            Character1Group->AddNewObject(new Engine::Image("stage-select/red-rectangle.png", 1165, 150, 220, 178));
        }
    }
    else if (mode == 4){
        if (scene->Character1Id != 1){
            scene->Character2Id = 1;
            if (!Character2Group->GetObjects().empty()){
                this->Character2Group->RemoveObject(Character2Group->GetObjects().front()->GetObjectIterator());
            }
            Character2Group->AddNewObject(new Engine::Image("stage-select/green-rectangle.png", 386, 350, 177, 176));
        }
    }
    else if (mode == 5){
        if (scene->Character1Id != 2){
            scene->Character2Id = 2;
            if (!Character2Group->GetObjects().empty()){
                this->Character2Group->RemoveObject(Character2Group->GetObjects().front()->GetObjectIterator());
            }
            Character2Group->AddNewObject(new Engine::Image("stage-select/green-rectangle.png", 786, 350, 177, 176));
        }
    }
    else if (mode == 6){
        if (scene->Character1Id != 3){
            scene->Character2Id = 3;
            if (!Character2Group->GetObjects().empty()){
                this->Character2Group->RemoveObject(Character2Group->GetObjects().front()->GetObjectIterator());
            }
            Character2Group->AddNewObject(new Engine::Image("stage-select/green-rectangle.png", 1186, 350, 177, 176));
        }
    }
    else if (mode == 7){
        if (Character1Group->GetObjects().size() == 1 && Character2Group->GetObjects().size() == 1){
            Engine::GameEngine::GetInstance().ChangeScene("play");
        }
    }
}
void TwoCooperateSettingScene::BGMSlideOnValueChanged(float value) {
    al_set_sample_instance_gain(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void TwoCooperateSettingScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}

