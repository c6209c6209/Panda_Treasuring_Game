#ifndef PANDA_HPP_INCLUDED
#define PANDA_HPP_INCLUDED
//#endif // PANDA_HPP_INCLUDED

#include "GameEngine.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Sprite.hpp"
#include "Ice.hpp"
#include "Treasure.hpp"

class PlayScene;
class Treasure;
//class Ice;
class Panda : public Engine::Sprite {
protected:
	float hp;
	PlayScene* getPlayScene();
    float x, y;//coordinates.
    float vx, vy;//speed in x, y directions.
public:
	bool shoot = false;
	virtual void CreateIce() = 0;
	Panda(std::string img, float x, float y, float w, float h,  float hp);//constructors.
 	void Update(float deltaTime);
 	void Hit(float damage);
 	void Draw() const override;
 	void updateVx(float newVx);
 	void updateVy(float newVy);
 	float getVx();
 	float getVy();
 	float getX();
 	float getY();
 	void OnExplode();
 	//void Hit();
};
#endif // PANDA_HPP_INCLUDED
