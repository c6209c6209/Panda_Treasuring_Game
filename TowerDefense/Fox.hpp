#ifndef FOX_HPP_INCLUDED
#define FOX_HPP_INCLUDED

#include "GameEngine.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Sprite.hpp"

class PlayScene;
class Fox : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
public:
    float x, y;//coordinates.
	float vx, vy;//speed in x, y directions.
	Fox(std::string img, float x, float y, float w, float h);//constructors.
	void Hit(float damage);
 	void Update(float deltaTime);
 	void Draw() const override;
};

#endif // FOX_HPP_INCLUDED
