#include "Sprite.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"
#include "Panda.hpp"
#include "Treasure.hpp"
#include "LOG.hpp"
#include "DirtyEffect.hpp"
using namespace std;
PlayScene* Treasure::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Treasure::OnExplode(Enemy* enemy) {
}
Treasure::Treasure(std::string img, float x, float y, float w, float h, int score) :
	Sprite(img,x,y, w, h), speed(speed), damage(damage), parent(parent), score(score) {
/*	Velocity = forwardDirection.Normalize() * speed;
	Rotation = rotation;*/
	CollisionRadius = 15;
}
void Treasure::Update(float deltaTime) {
	PlayScene* scene = getPlayScene();
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However simply loop through all enemies is enough for this program.
        vx = vy = 0;
        Velocity.x = vx;
        Velocity.y = vy;
        Sprite::Update(deltaTime);
    //if eaten by Panda, should disappear.
    //Below is for auto shoot.(including explosion effect)
    /*
	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		//if no enemy, do nothing.
		if (!enemy->Visible)
			continue;
        //in shooting region.
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
			OnExplode(enemy);
			enemy->Hit(damage);
			getPlayScene()->IceGroup->RemoveObject(objectIterator);
			return;
		}
	}*/
	// Check if out of boundary.
    /*
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
		getPlayScene()->IceGroup->RemoveObject(objectIterator);
    */
}

void Treasure::Hit() {
    getPlayScene()->EarnScore(score);
    getPlayScene()->TreasureGroup->RemoveObject(objectIterator);
}
