#ifndef BULLET6_HPP_INCLUDED
#define BULLET6_HPP_INCLUDED
#include "Bullet.hpp"
class Bullet6 : public Bullet {
public:
	explicit Bullet6(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // BULLET6_HPP_INCLUDED
