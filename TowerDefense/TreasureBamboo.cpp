#include "TreasureBamboo.hpp"
#include "DirtyEffect.hpp"
#include"Panda.hpp"
TreasureBamboo::TreasureBamboo(float x, float y, float w, float h, int score) :
	Treasure("play/bamboo.png", x, y, w, h, score) {
}
void TreasureBamboo::Update(float deltaTime) {


	//we place ice, ice don't attack enemy.
/*	if (!Target) {
		float minDistance = INFINITY;
		Enemy* enemy = nullptr;
		for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
			Enemy* e = dynamic_cast<Enemy*>(it);
			float distance = (e->Position - Position).Magnitude();
			if (distance < minDistance) {
				minDistance = distance;
				enemy = e;
			}
		}
		if (!enemy) {
			Ice::Update(deltaTime);
			return;
		}
		Target = enemy;
//		Target->lockedBullets.push_back(this);
//		lockedBulletIterator = std::prev(Target->lockedBullets.end());
	}

	Engine::Point originVelocity = Velocity.Normalize();
	Engine::Point targetVelocity = (Target->Position - Position).Normalize();
	float maxRotateRadian = rotateRadian * deltaTime;
	float cosTheta = originVelocity.Dot(targetVelocity);
	// Might have floating-point precision error.
	if (cosTheta > 1) cosTheta = 1;
	else if (cosTheta < -1) cosTheta = -1;
	float radian = acos(cosTheta);
	if (abs(radian) <= maxRotateRadian)
		Velocity = targetVelocity;
	else
		Velocity = ((abs(radian) - maxRotateRadian) * originVelocity + maxRotateRadian * targetVelocity) / radian;

	Velocity = speed * Velocity.Normalize();*/
//	Rotation = atan2(Velocity.y, Velocity.x) + ALLEGRO_PI / 2;
	Treasure::Update(deltaTime);
}
void TreasureBamboo::OnExplode(Enemy* enemy) {
/*	Target->lockedBullets.erase(lockedBulletIterator);
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4, 10);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-3.png", dist(rng), enemy->Position.x, enemy->Position.y));*/
}
