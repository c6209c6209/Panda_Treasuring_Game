#ifndef TREASUREBAMBOO_HPP_INCLUDED
#define TREASUREBAMBOO_HPP_INCLUDED

#include "Treasure.hpp"
class TreasureBamboo : public Treasure {
protected:
	const float rotateRadian = 2 * ALLEGRO_PI;
//	std::list<Ice*>::iterator lockedBulletIterator;
public:
	explicit TreasureBamboo(float x, float y, float w, float h, int score);
	void Update(float deltaTime) override;
	void OnExplode(Enemy* enemy) override;
};

#endif // TREASUREBAMBOO_HPP_INCLUDED
