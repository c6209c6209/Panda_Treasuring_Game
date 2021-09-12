#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <vector>
#include "IScene.hpp"
#include "Sprite.hpp"
#include "Label.hpp"
#include "Turret.hpp"
#include "ImageButton.hpp"
#include "Panda.hpp"
class Panda;
class PlayScene final : public Engine::IScene {
private:
	enum TileType {
		TILE_DIRT,
		TILE_FLOOR,
		TILE_OCCUPIED,
		TILE_PANDA
	};
protected:
	int lives;
	int money;
	int SpeedMult;
	int score;
	int finalScore;
public:
	static bool DebugMode;
	static const std::vector<Engine::Point> directions;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const Engine::Point SpawnGridPoint;
	static const Engine::Point EndGridPoint;
	static const std::vector<int> code;
	int MapId;
	int Character1Id, Character2Id;;
	int BambooID, HPbottleID;
	float ticks;
	// Map tiles.
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* DebugIndicatorGroup;
	Group* BulletGroup;
	Group* TowerGroup;
	Group* EnemyGroup;
	Group* EffectGroup;
	Group* UIGroup;
	Group* PlayerGroup;
	Group* IceGroup;
	Group* TreasureGroup;
	Engine::Label* UIMoney;
	Engine::Label* UILives;
	Engine::Label* UIScore;
	Engine::Image* imgTarget;
	Turret* preview;
    Panda* player1;
	Panda* player2;
	std::vector<std::vector<TileType>> mapState;
	std::vector<std::vector<int>> mapDistance;
	std::list<std::pair<int, float>> enemyWaveData;
	std::list<int> keyStrokes;
	static Engine::Point GetClientSize();
	explicit PlayScene() = default;
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void Hit();
	int GetMoney() const;
	int GetScore() const;
	void EarnMoney(int money);
	void EarnScore(int score);
	void ReadMap();
	void ReadBamboo();
	void ReadHPbottle();
	void ReadEnemyWave();
	void ConstructUI();
	void UIBtnClicked(int id);
	bool CheckSpaceValid(int x, int y);
	std::vector<std::vector<int>> CalculateBFSDistance();
	void Pause();
	// void ModifyReadMapTiles();
};
#endif // PLAYSCENE_HPP
