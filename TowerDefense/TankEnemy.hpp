#ifndef TANKENEMY_HPP
#define TANKENEMY_HPP
#include "Enemy.hpp"

class TankEnemy : public Enemy {
private:
	Sprite head;
	float targetRotation;
public:
	TankEnemy(int x, int y, int w , int h);
	void Draw() const override;
	void Update(float deltaTime) override;
};
#endif // TANKENEMY_HPP
