// [main.cpp]
// this template is provided for the 2D tower defense game.
// Program entry point.
// Returns program exit code.
#include "GameEngine.hpp"
#include "LOG.hpp"
#include "StageSelectScene.hpp"
#include "PlayScene.hpp"
#include "WinScene.hpp"
#include "LoseScene.hpp"
#include "StartScene.hpp"
#include "MainSettingScene.hpp"
#include "SingleSettingScene.hpp"
#include "TwoCooperateSettingScene.hpp"
#include "BridgingScene.hpp"
int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();
	game.AddNewScene("stage-select", new StageSelectScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
	// TODO 1 (1/2): Add a New Scene here and change the start scene below.
	game.AddNewScene("Start", new StartScene());
	game.AddNewScene("main-setting", new MainSettingScene());
	game.AddNewScene("single-setting", new SingleSettingScene());
	game.AddNewScene("two-cooperate-setting", new TwoCooperateSettingScene());
	game.AddNewScene("Bridge", new BridgingScene());
	game.Start("Start", 60, 1600, 832);
	return 0;
}

