#ifndef HPBOTTLE_HPP_INCLUDED
#define HPBOTTLE_HPP_INCLUDED

#include "Treasure.hpp"
class HPbottle : public Treasure {
protected:
	const float rotateRadian = 2 * ALLEGRO_PI;
//	std::list<Ice*>::iterator lockedBulletIterator;
public:
	explicit HPbottle(float x, float y, float w, float h, int score);
	void Update(float deltaTime) override;
	void OnExplode(Enemy* enemy) override;
};

#endif // HPBOTTLE_HPP_INCLUDED
