#ifndef TURRET4_HPP_INCLUDED
#define TURRET4_HPP_INCLUDED
#include "PlayScene.hpp"
#include "Bullet.hpp"
#include "Turret.hpp"

class PlayScene;
class Turret4: public Turret {
public:
	static const int Price;
    Turret4(float x, float y, float w, float h);
    void CreateBullet() override;
};
#endif // TURRET4_HPP_INCLUDED
