#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "GameEngine.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Sprite.hpp"
#include "Turret.hpp"

class Turret;
class PlayScene;
class Bullet;
class Enemy : public Engine::Sprite {
protected:
 	std::vector<Engine::Point> path;
	float speed;
	PlayScene* getPlayScene();
    virtual void OnExplode();
public:
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float w, float h, float radius, float speed);
	void UpdatePath(const std::vector<std::vector<int>>& mapDistance);
	void Update(float deltaTime) override;
	void Draw() const override;
	void Hit(float damage);
};
#endif // ENEMY_HPP
