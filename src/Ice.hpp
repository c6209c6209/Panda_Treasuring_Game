#ifndef ICE_HPP_INCLUDED
#define ICE_HPP_INCLUDED
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"
#include <random>

class PlayScene;
class Enemy;
class Panda;

class Ice : public Engine::Sprite {
protected:
	float speed;
	float damage;
	Panda* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(Enemy* enemy);
public:
    float x, y;
    float vx, vy;
    bool shoot = false;
	Enemy* Target = nullptr;
	explicit Ice(std::string img,float w, float h, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Panda* parent);
	void Update(float deltaTime) override;
};
#endif // ICE_HPP_INCLUDED
