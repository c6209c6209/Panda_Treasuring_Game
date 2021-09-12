#ifndef TREASURE_HPP_INCLUDED
#define TREASURE_HPP_INCLUDED

#include "Sprite.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"
#include <random>

class PlayScene;
class Panda;

class Treasure : public Engine::Sprite {
protected:
	float speed;
	float damage;
	int score;
	Panda* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(Enemy* enemy);
public:
    float x, y;
    float vx, vy;
	Enemy* Target = nullptr;
	explicit Treasure(std::string img, float x, float y, float w , float h, int score);
	void Hit();
	void Update(float deltaTime) override;
};

#endif // TREASURE_HPP_INCLUDED
