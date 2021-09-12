#include <string>
#include <queue>
#include <fstream>
#include "Image.hpp"
#include "Label.hpp"
#include "ImageButton.hpp"
#include "PlayScene.hpp"
#include "LOG.hpp"
#include "Enemy.hpp"
#include "PlaneEnemy.hpp"
#include "SoldierEnemy.hpp"
#include "TankEnemy.hpp"
#include "Enemy4.hpp"
#include "MachineGunTurret.hpp"
#include "LaserTurret.hpp"
#include "MissileTurret.hpp"
#include "Turret4.hpp"
#include "TurretButton.hpp"
#include "Plane.hpp"
#include "Panda.hpp"
#include "csPanda.hpp"
#include "ipePanda.hpp"
#include "nthuPanda.hpp"
#include "Treasure.hpp"
#include "Hpbottle.hpp"
#include "TreasureBamboo.hpp"
#include "DirtyEffect.hpp"
#include "AudioHelper.hpp"
#include <iostream>
#include "StartScene.hpp"
#include "BridgingScene.hpp"
using namespace std;

bool PlayScene::DebugMode = false;
const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 20, PlayScene::MapHeight = 13;
const int PlayScene::BlockSize = 64;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(MapWidth, MapHeight - 1);
const std::vector<int> PlayScene::code = { ALLEGRO_KEY_N, ALLEGRO_KEY_T, ALLEGRO_KEY_H, ALLEGRO_KEY_U, ALLEGRO_KEY_DOWN};
Engine::Point PlayScene::GetClientSize() {
	return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void PlayScene::Initialize() {
	// TODO 5 (1/2): There's a bug in this file, which crashes the game when you win. Try to find it.
	// TODO 5 (2/2): There's a cheat code in this file. Try to find it.
	mapState.clear();
	keyStrokes.clear();
	ticks = 0;
	lives = 10;
	money = 0;
	score = 0;
	finalScore = 0;
	SpeedMult = 1;
	// Add groups from bottom to top.
	AddNewObject(TileMapGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
	AddNewObject(DebugIndicatorGroup = new Group());
	AddNewObject(TowerGroup = new Group());
	AddNewObject(EnemyGroup = new Group());
	AddNewObject(BulletGroup = new Group());
	AddNewObject(EffectGroup = new Group());
	AddNewObject(IceGroup = new Group());
	AddNewObject(TreasureGroup = new Group());
	//	AddNewObject(PlayerGroup = new Group());
	// Should support buttons.
	//Player 1; initial , bottom center.
    AddNewControlObject(PlayerGroup = new Group());
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w/2;
  //  ipePanda* ipePlayer;
    cout << Character1Id << Character2Id << endl;
    switch(Character1Id){
        case 1:
            PlayerGroup->AddNewObject(player1 = new csPanda(halfW, h-50, 64, 64));
            break;
        case 2:
            PlayerGroup->AddNewObject(player1 = new ipePanda(halfW, h-50, 64, 64));
            break;
        case 3:
            PlayerGroup->AddNewObject(player1 = new nthuPanda(halfW, h-50, 64, 64));
            break;
    }
    switch(Character2Id){
        case 1:
            PlayerGroup->AddNewObject(player2 = new csPanda(halfW - 150, h-50, 64, 64));
            break;
        case 2:
            PlayerGroup->AddNewObject(player2 = new ipePanda(halfW - 150, h-50, 64, 64));
            break;
        case 3:
            PlayerGroup->AddNewObject(player2 = new nthuPanda(halfW - 150, h-50, 64, 64));
            break;
        default:
            break;
    }

 //   PlayerGroup->AddNewObject(ipePlayer = (new ipePanda(halfW, h-50, 50, 50)));
	// Should support buttons.
/*
	Engine::ImageButton* pausebtn;
    pausebtn = new Engine::ImageButton("play/pause.png", "play/pauseIn.png", halfH*2-50, 50, 50, 50);
    pausebtn->SetOnClickCallback(std::bind(&PlayScene::PlayOnClick, this, 1));//back to setting scene.*/
  //  AddNewControlObject(btn);
 //   AddNewObject(new Engine::Label("Stage 1", "pirulen.ttf", 48, halfW, halfH / 2, 0, 0, 0, 255, 0.5, 0.5));
	AddNewControlObject(UIGroup = new Group());
	ReadMap();
	ReadBamboo();
	ReadHPbottle();
	ReadEnemyWave();
	mapDistance = CalculateBFSDistance();
	ConstructUI();
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	//	ipePlayer = new ipePanda(halfW, h-50, 50, 50);
	UIGroup->AddNewObject(imgTarget);
	AudioHelper::PlayBGM("Yellow.ogg");
}
void PlayScene::Update(float deltaTime) {
	// Fake speed up.
	deltaTime *= SpeedMult;
	// If we use deltaTime directly, then we might have Bullet-through-paper problem.
	// Reference: Bullet-Through-Paper
	if (deltaTime < 3) {
		IScene::Update(deltaTime);
	} else if (deltaTime < 6) {
		IScene::Update(deltaTime / 2);
		IScene::Update(deltaTime / 2);
	} else if (deltaTime < 9) {
		IScene::Update(deltaTime / 3);
		IScene::Update(deltaTime / 3);
		IScene::Update(deltaTime / 3);
	} else {
		IScene::Update(deltaTime / 4);
		IScene::Update(deltaTime / 4);
		IScene::Update(deltaTime / 4);
		IScene::Update(deltaTime / 4);
	}
	if (preview) {
		preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	}
	// Check if we should create new enemy.
	ticks += deltaTime;
	if (score == finalScore) {
		if (BambooID == 1 && HPbottleID == 1) {
			// Free resources.
			/*delete TileMapGroup;
			delete GroundEffectGroup;
			delete DebugIndicatorGroup;
			delete TowerGroup;
			delete EnemyGroup;
			delete BulletGroup;
			delete EffectGroup;
			delete UIGroup;
			delete imgTarget;*/
			// Win.
			BambooID += 1;
			HPbottleID += 1;
			Engine::GameEngine::GetInstance().ChangeScene("Bridge");
		}
		else {
            Engine::GameEngine::GetInstance().ChangeScene("win");
		}
		//return;
	}
	auto current = enemyWaveData.front();
	if (ticks < current.second)
		return;
	ticks -= current.second;
	enemyWaveData.pop_front();
	const Engine::Point SpawnCoordinate = Engine::Point(SpawnGridPoint.x * BlockSize + BlockSize / 2, SpawnGridPoint.y * BlockSize + BlockSize / 2);
	Enemy* enemy;
	switch (current.first) {
	case 0:
		EnemyGroup->AddNewObject(enemy = new SoldierEnemy(SpawnCoordinate.x, SpawnCoordinate.y, 64, 64));
		break;
	case 1:
		EnemyGroup->AddNewObject(enemy = new TankEnemy(SpawnCoordinate.x, SpawnCoordinate.y, 64, 64));
		break;
	case 2:
		EnemyGroup->AddNewObject(enemy = new Enemy4(SpawnCoordinate.x, SpawnCoordinate.y, 64, 64));
		break;
	// TODO 2 (7/8): You need to modify 'resources/enemy1.txt', or 'resources/enemy2.txt' to spawn the 4th enemy.
	//         The format is "[EnemyId] [TimeDelay] [Repeat]".
	// TODO 2 (8/8): Enable the creation of the 4th enemy.
	default:
		return;
	}


	//mapDistance = CalculateBFSDistance();
	enemy->UpdatePath(mapDistance);
	// Compensate the time lost.
	enemy->Update(ticks);

	enemy->Update(ticks);
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w/2;
    player1->Update(ticks);
    if (player2 != NULL){
        player2->Update(ticks);
    }

    /*for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			if (mapState[i][j] == TILE_PANDA){
                mapState[i][j] = TILE_DIRT;
			}
		}
	}

	const int x = player1->Position.x * 20 / 800;
	const int y = player1->Position.y * 13 / 600;
	mapState[x][y] = TILE_PANDA;*/
	//cout << BlockSize <<endl;
}
void PlayScene::Draw() const {
	IScene::Draw();
	if (DebugMode) {
		// Draw reverse BFS distance on all reachable blocks.
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				if (mapDistance[i][j] != -1) {
					// Not elegant nor efficient, but it's quite enough for debugging.
					Engine::Label label(std::to_string(mapDistance[i][j]), "pirulen.ttf", 32, (j + 0.5) * BlockSize, (i + 0.5) * BlockSize);
					label.Anchor = Engine::Point(0.5, 0.5);
					label.Draw();
				}
			}
		}
	}
}
void PlayScene::OnMouseDown(int button, int mx, int my) {
	/*if ((button & 1) && !imgTarget->Visible && preview) {
		// Cancel turret construct.
		UIGroup->RemoveObject(preview->GetObjectIterator());
		preview = nullptr;
	}
	IScene::OnMouseDown(button, mx, my);*/
}
void PlayScene::OnMouseMove(int mx, int my) {
	IScene::OnMouseMove(mx, my);
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (!preview || x < 0 || x >= MapWidth || y < 0 || y >= MapHeight) {
		imgTarget->Visible = false;
		return;
	}
	imgTarget->Visible = true;
	imgTarget->Position.x = x * BlockSize;
	imgTarget->Position.y = y * BlockSize;
}
void PlayScene::OnMouseUp(int button, int mx, int my) {
	/*IScene::OnMouseUp(button, mx, my);
	if (!imgTarget->Visible)
		return;
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (button & 1) {
		if (mapState[y][x] != TILE_OCCUPIED) {
			if (!preview)
				return;
			// Check if valid.
			if (!CheckSpaceValid(x, y)) {
				Engine::Sprite* sprite;
				GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png", 1, x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2));
				sprite->Rotation = 0;
				return;
			}
			// Purchase.
			EarnMoney(-preview->GetPrice());
			// Remove Preview.
			preview->GetObjectIterator()->first = false;
			UIGroup->RemoveObject(preview->GetObjectIterator());
			// Construct real turret.
			preview->Position.x = x * BlockSize + BlockSize / 2;
			preview->Position.y = y * BlockSize + BlockSize / 2;
			preview->Enabled = true;
			preview->Preview = false;
			preview->Tint = al_map_rgba(255, 255, 255, 255);
			TowerGroup->AddNewObject(preview);
			// Remove Preview.
			preview = nullptr;

			mapState[y][x] = TILE_OCCUPIED;
			OnMouseMove(mx, my);
		}
	}*/
}
void PlayScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);
	if (keyCode == ALLEGRO_KEY_TAB) {
		DebugMode = !DebugMode;
	}
	else {
		keyStrokes.push_back(keyCode);
		if (keyStrokes.size() > code.size())
			keyStrokes.pop_front();
		if (keyCode == ALLEGRO_KEY_ENTER && keyStrokes.size() == code.size()) {
			auto it = keyStrokes.begin();
			for (int c : code) {
				if (*it != c && (c == ALLEGRO_KEYMOD_SHIFT && *it != ALLEGRO_KEY_LSHIFT && *it != ALLEGRO_KEY_RSHIFT))
					return;
				++it;
			}
			EffectGroup->AddNewObject(new Plane());
			score += 10000;
		}
	}
	/*if (keyCode == ALLEGRO_KEY_Q) {
		// Hotkey for MachineGunTurret.
		UIBtnClicked(0);
	}
	else if (keyCode == ALLEGRO_KEY_W) {
		// Hotkey for LaserTurret.
		UIBtnClicked(1);
	}
	else if (keyCode == ALLEGRO_KEY_E) {
		// Hotkey for MissileTurret.
		UIBtnClicked(2);
	}
	// TODO 2 (5/8): Make the R key to create the 4th turret.
	else*/ if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
		// Hotkey for Speed up.
		SpeedMult = keyCode - ALLEGRO_KEY_0;
	}

	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w/2;
	//Use key to move pandas.
//	ipePanda* player1;
//	player1 = (new ipePanda(halfW, h-50, 50, 50));
//	PlayerGroup->AddNewObject(ipePlayer = (new ipePanda(halfW, h-50, 50, 50)));

     //Use key to move pandas.
    player1->updateVx(0);
    player1->updateVy(0);
    if(keyCode == ALLEGRO_KEY_UP){
        player1->Rotation = ALLEGRO_PI;
        player1->updateVy(-2*BlockSize);
    }
    if(keyCode==ALLEGRO_KEY_DOWN){
        player1->Rotation = 0;
        player1->updateVy(2*BlockSize);
    }
    if(keyCode==ALLEGRO_KEY_LEFT){
        player1->Rotation = ALLEGRO_PI/2;
        player1->updateVx(-2*BlockSize);
    }
    if(keyCode==ALLEGRO_KEY_RIGHT){
        player1->Rotation = ALLEGRO_PI*3/2;
        player1->updateVx(2*BlockSize);
    }
    //SPACE to shoot ICE.
    if(keyCode == ALLEGRO_KEY_SPACE){
        //player1->shoot = true;
        player1->CreateIce();
    }
            //Use key to move  second pandas.
    if (player2 != NULL){
        player2->updateVx(0);
        player2->updateVy(0);
        if(keyCode == ALLEGRO_KEY_W){
            player2->Rotation = ALLEGRO_PI;
            player2->updateVy(-2*BlockSize);
        }
        if(keyCode==ALLEGRO_KEY_S){
            player2->Rotation = 0;
            player2->updateVy(2*BlockSize);
        }
        if(keyCode==ALLEGRO_KEY_A){
            player2->Rotation = ALLEGRO_PI/2;
            player2->updateVx(-2*BlockSize);
        }
        if(keyCode==ALLEGRO_KEY_D){
            player2->Rotation = ALLEGRO_PI*3/2;
            player2->updateVx(2*BlockSize);
        }
        //Q to shoot ICE.
        if(keyCode == ALLEGRO_KEY_Q){
            //player1->shoot = true;
            player2->CreateIce();
        }
    }

}
void PlayScene::OnKeyUp(int keyCode){
    IScene::OnKeyUp(keyCode);
    if(keyCode==ALLEGRO_KEY_UP || keyCode==ALLEGRO_KEY_DOWN || keyCode==ALLEGRO_KEY_LEFT || keyCode==ALLEGRO_KEY_RIGHT ){
        player1->updateVx(0);
        player1->updateVy(0);
    }
    if(keyCode == ALLEGRO_KEY_SPACE){
        player1->shoot = false;
    }
    if(keyCode==ALLEGRO_KEY_W || keyCode==ALLEGRO_KEY_S || keyCode==ALLEGRO_KEY_A || keyCode==ALLEGRO_KEY_D ){
        player2->updateVx(0);
        player2->updateVy(0);
    }
    if(keyCode == ALLEGRO_KEY_Q){
        player2->shoot = false;
    }
}
void PlayScene::Hit() {
	lives--;
	UILives->Text = std::string("Life ") + std::to_string(lives);
	if (lives <= 0) {
		Engine::GameEngine::GetInstance().ChangeScene("lose");
	}
}
int PlayScene::GetMoney() const {
	return money;
}
int PlayScene::GetScore() const {
	return score;
}
void PlayScene::EarnMoney(int money) {
	this->money += money;
	UIMoney->Text = std::string("$") + std::to_string(this->money);
}
void PlayScene::EarnScore(int score) {
	this->score += score;
	UIScore->Text = std::string("Score : ") + std::to_string(this->score);
}
void PlayScene::ReadMap() {
	std::string filename = std::string("resources/map") + std::to_string(MapId) + ".txt";
	// Read map file.
	char c;
	std::vector<bool> mapData;
	std::ifstream fin(filename);
	while (fin >> c) {
		switch (c) {
		case '0': mapData.push_back(false); break;
		case '1': mapData.push_back(true); break;
		case '\n':
		case '\r':
			if (static_cast<int>(mapData.size()) / MapWidth != 0)
				throw std::ios_base::failure("Map data is corrupted.");
			break;
		default: throw std::ios_base::failure("Map data is corrupted.");
		}
	}
	fin.close();
	// Validate map data.
	if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
		throw std::ios_base::failure("Map data is corrupted.");
	// Store map in 2d array.
	mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			const int num = mapData[i * MapWidth + j];
			mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
			if (num)
				TileMapGroup->AddNewObject(new Engine::Image("play/sand.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
			else
				TileMapGroup->AddNewObject(new Engine::Image("play/sand.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
		}
	}
}

void PlayScene::ReadHPbottle() {
	std::string filename = std::string("resources/HPbottle") + std::to_string(HPbottleID) + ".txt";
	// Read map file.
	char c;
	std::vector<bool> mapData;
	std::ifstream fin(filename);
	while (fin >> c) {
		switch (c) {
		case '0': mapData.push_back(false); break;
		case '1': mapData.push_back(true); break;
		case '\n':
		case '\r':
			if (static_cast<int>(mapData.size()) / MapWidth != 0)
				throw std::ios_base::failure("Map data is corrupted.");
			break;
		default: throw std::ios_base::failure("Map data is corrupted.");
		}
	}
	fin.close();
	// Validate map data.
	if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
		throw std::ios_base::failure("Map data is corrupted.");
	// Store map in 2d array.
	mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			const int num = mapData[i * MapWidth + j];
			mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
			HPbottle* hpbox;
			if (num){
                TreasureGroup->AddNewObject(hpbox = new HPbottle(j * BlockSize, i * BlockSize, BlockSize, BlockSize, 100));
                finalScore += 100;
			}
			else{}
		//		TileMapGroup->AddNewObject(new Engine::Image("play/dirt.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
		}
	}
}

void PlayScene::ReadBamboo() {
	std::string filename = std::string("resources/Bamboo") + std::to_string(BambooID) + ".txt";
	// Read map file.
	char c;
	std::vector<bool> mapData;
	std::ifstream fin(filename);
	while (fin >> c) {
		switch (c) {
		case '0': mapData.push_back(false); break;
		case '1': mapData.push_back(true); break;
		case '\n':
		case '\r':
			if (static_cast<int>(mapData.size()) / MapWidth != 0)
				throw std::ios_base::failure("Map data is corrupted.");
			break;
		default: throw std::ios_base::failure("Map data is corrupted.");
		}
	}
	fin.close();
	// Validate map data.
	if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
		throw std::ios_base::failure("Map data is corrupted.");
	// Store map in 2d array.
	mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			const int num = mapData[i * MapWidth + j];
			mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
			TreasureBamboo* treaBamboo;
			if (num){
                TreasureGroup->AddNewObject(treaBamboo = new TreasureBamboo( j * BlockSize, i * BlockSize, BlockSize, BlockSize, 50));
                finalScore += 50;
			}
			else{}
			//	TileMapGroup->AddNewObject(new Engine::Image("play/dirt.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
		}
	}
}
void PlayScene::ReadEnemyWave() {
	std::string filename = std::string("resources/enemy") + std::to_string(MapId) + ".txt";
	// Read enemy file.
	float type, wait, repeat;
	enemyWaveData.clear();
	std::ifstream fin(filename);
	while (fin >> type && fin >> wait && fin >> repeat) {
		for (int i = 0; i < repeat; i++)
			enemyWaveData.emplace_back(type, wait);
	}
	fin.close();
}
void PlayScene::ConstructUI() {
	// Background
	UIGroup->AddNewObject(new Engine::Image("play/floor.png", 1280, 0, 320, 832));
	// Text
	UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 32, 1294, 0));
	UIGroup->AddNewObject(UIScore = new Engine::Label(std::string("Score : ") + std::to_string(score), "pirulen.ttf", 32, 1294, 250));
	UIGroup->AddNewObject(UILives = new Engine::Label(std::string("Life ") + std::to_string(lives), "pirulen.ttf", 24, 1294, 88));
	//UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$ ") + std::to_string(money), "pirulen.ttf", 24, 1294, 48));
    //pause button.
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w/2;
    Engine::ImageButton* pausebtn;
    pausebtn = new Engine::ImageButton("play/pause.png", "play/pauseIn.png", halfW*2-100, 20, 50, 50);
    pausebtn->SetOnClickCallback(std::bind(&PlayScene::Pause, this));//back to setting scene.*/
    AddNewControlObject(pausebtn);

    //Player 1; initial , bottom center.
  //  PlayerGroup->AddNewObject(new Engine::Sprite("play/ipepanda.png", halfW, h-50, 50, 50, 0, 0));

	/*TurretButton* btn;

	// Button 1
	btn = new TurretButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
		Engine::Sprite("play/turret-1.png", 1294, 136 - 8, 0, 0, 0, 0)
		, 1294, 136, MachineGunTurret::Price);
	// Reference: Class Member Function Pointer and std::bind.
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 0));
	UIGroup->AddNewControlObject(btn);
	// Button 2
	btn = new TurretButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1370, 136, 0, 0, 0, 0),
		Engine::Sprite("play/turret-2.png", 1370, 136 - 8, 0, 0, 0, 0)
		, 1370, 136, LaserTurret::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 1));
	UIGroup->AddNewControlObject(btn);
	// Button 3
	btn = new TurretButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1446, 136, 0, 0, 0, 0),
		Engine::Sprite("play/turret-3.png", 1446, 136, 0, 0, 0, 0)
		, 1446, 136, MissileTurret::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 2));
	UIGroup->AddNewControlObject(btn);
	// TODO 2 (3/8): Create a button to support constructing the 4th tower.
	// Button 4
	btn = new TurretButton("play/floor.png", "play/dirt.png",
        Engine::Sprite("play/tower-base.png", 1522, 136, 0, 0, 0, 0),
		Engine::Sprite("play/turret-4.png", 1522, 136+8, 0, 0, 0, 0)
		, 1522, 136, MissileTurret::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
	UIGroup->AddNewControlObject(btn);*/
}

void PlayScene::UIBtnClicked(int id) {
	if (preview)
		UIGroup->RemoveObject(preview->GetObjectIterator());
	if (id == 0 && money >= MachineGunTurret::Price)
		preview = new MachineGunTurret(0, 0, 50, 50);
	else if (id == 1 && money >= LaserTurret::Price)
		preview = new LaserTurret(0, 0, 50, 50);
	else if (id == 2 && money >= MissileTurret::Price)
		preview = new MissileTurret(0, 0, 50, 50);
	// TODO 2 (4/8): On callback, create the 4th tower.
	else if (id == 3 && money >= Turret4::Price)
		preview = new Turret4(0, 0, 50, 50);

	if (!preview)
		return;
	preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	preview->Tint = al_map_rgba(255, 255, 255, 200);
	preview->Enabled = false;
	preview->Preview = true;
	UIGroup->AddNewObject(preview);
	OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);
}
void PlayScene::Pause() {
    StartScene* scene = dynamic_cast<StartScene*>(Engine::GameEngine::GetInstance().GetScene("Start"));
    Engine::GameEngine::GetInstance().ChangeScene("Start");
}
bool PlayScene::CheckSpaceValid(int x, int y) {//TILE_DIRT才能走，map紀錄現在位置走到起點(最右下角的距離)
	if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
		return false;
	auto map00 = mapState[y][x];
	mapState[y][x] = TILE_OCCUPIED;
	std::vector<std::vector<int>> map = CalculateBFSDistance();
	mapState[y][x] = map00;
	if (map[0][0] == -1)
		return false;
	for (auto& it : EnemyGroup->GetObjects()) {
		Engine::Point pnt;
		pnt.x = floor(it->Position.x / BlockSize);
		pnt.y = floor(it->Position.y / BlockSize);
		if (pnt.x < 0 || pnt.x >= MapWidth || pnt.y < 0 || pnt.y >= MapHeight)
			continue;
		if (map[pnt.y][pnt.x] == -1)
			return false;
	}
	// All enemy have path to exit.
	mapState[y][x] = TILE_OCCUPIED;
	mapDistance = map;
	for (auto& it : EnemyGroup->GetObjects())
		dynamic_cast<Enemy*>(it)->UpdatePath(mapDistance);
	return true;
}
std::vector<std::vector<int>> PlayScene::CalculateBFSDistance() {
	// Reverse BFS to find path.
	std::vector<std::vector<int>> map(MapHeight, std::vector<int>(std::vector<int>(MapWidth, -1)));
	std::queue<Engine::Point> que;
	// Push end point.
	// BFS from end point.
	if (mapState[MapHeight - 1][MapWidth - 1] != TILE_DIRT)//dirt --> it's empty. Fill number.
		return map;
	que.push(Engine::Point(MapWidth - 1, MapHeight - 1));
	map[MapHeight - 1][MapWidth - 1] = 0;//起點(最右下角)
	while (!que.empty()) {//queue沒空才能pop
		Engine::Point p = que.front();//運用p來看
		que.pop();//
		//std::cout << "test1"<<endl;
		// TODO 3 (1/1): Implement a BFS starting from the most right-bottom block in the map.
		//               For each step you should assign the corresponding distance to the most right-bottom block.
		//               mapState[y][x] is TILE_DIRT if it is empty.
        if(p.x-1>=0 && mapState[p.y][p.x-1]==TILE_DIRT && map[p.y][p.x-1]==-1){
            map[p.y][p.x-1] = map[p.y][p.x]+1;
            que.push(Engine::Point(p.x-1,p.y));
         //   std::cout << "map if test1"<<endl;
        }
        if(p.y-1>=0 && mapState[p.y-1][p.x]==TILE_DIRT &&map[p.y-1][p.x]==-1){
            map[p.y-1][p.x] = map[p.y][p.x]+1;
            que.push(Engine::Point(p.x,p.y-1));
         //   std::cout << "map if test2"<<endl;
        }
        if(p.y+1<MapHeight && mapState[p.y+1][p.x]==TILE_DIRT &&map[p.y+1][p.x]==-1){
            map[p.y+1][p.x] = map[p.y][p.x]+1;
            que.push(Engine::Point(p.x,p.y+1));
         //   std::cout << "map if test3"<<endl;
        }
        if(p.x+1<MapWidth && mapState[p.y][p.x+1]==TILE_DIRT &&map[p.y][p.x+1]==-1){
            map[p.y][p.x+1] = map[p.y][p.x]+1;
            que.push(Engine::Point(p.x+1,p.y));
         //   std::cout << "map if test4"<<endl;
        }
        else{
         //   throw std::logic_error("CalculateBFSDistance is not implemented yet.");
        }
		//throw std::logic_error("CalculateBFSDistance is not implemented yet.");
	}
	return map;
}
