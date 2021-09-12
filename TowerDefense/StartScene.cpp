#include "StartScene.hpp"
#include "Label.hpp"
#include "AudioHelper.hpp"
#include "PlayScene.hpp"
#include "Image.hpp"
void StartScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewControlObject(UIGroup = new Group());
	UIGroup->AddNewObject(new Engine::Image("start/Background.jpg", 150, 0, 1280, 832));
	AddNewObject(new Engine::Label("Bad Panda", "pirulen.ttf", 72, halfW, halfH-50, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 350, halfH * 4/3 - 50, 700, 100);
	btn->SetOnClickCallback(std::bind(&StartScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Enter Game...", "pirulen.ttf", 48, halfW, halfH * 4/3, 0, 0, 0, 255, 0.5, 0.5));
	AudioHelper::PlayAudio("AllFallsDown.ogg");
}
void StartScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		AudioHelper::PlayBGM("AllFallsDown.ogg");
	}
}
void StartScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("main-setting");
}
