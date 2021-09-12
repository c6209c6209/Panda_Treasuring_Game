#ifndef GREENICE_HPP_INCLUDED
#define GREENICE_HPP_INCLUDED



#endif // GREENICE_HPP_INCLUDED
#include "Ice.hpp"
class GreenIce : public Ice {
protected:
	const float rotateRadian = 2 * ALLEGRO_PI;
//	std::list<Ice*>::iterator lockedBulletIterator;
public:
	explicit GreenIce(Engine::Point position, Engine::Point forwardDirection, float rotation, Panda* parent);
	void Update(float deltaTime) override;
	void OnExplode(Enemy* enemy) override;
};
