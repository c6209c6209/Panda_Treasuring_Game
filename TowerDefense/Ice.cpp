#include "Sprite.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"
#include "Panda.hpp"
#include "Ice.hpp"
#include "LOG.hpp"
#include "DirtyEffect.hpp"
using namespace std;
PlayScene* Ice::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Ice::OnExplode(Enemy* enemy) {
}
Ice::Ice(std::string img, float w, float h, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Panda* parent) :
	Sprite(img, position.x, position.y, w, h), speed(speed), damage(damage), parent(parent) {
	Velocity = forwardDirection.Normalize() * speed;
	Rotation = rotation;
	CollisionRadius = 4;
}
void Ice::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However simply loop through all enemies is enough for this program.
	//Below is for auto shoot.(including explosion effect)
        vx = vy = 0;
        /*if(scene->player1->Rotation == 0){//shoot downward.
                Position.x = scene->player1->x;
                Position.y = scene->player1->y+50;
                vy =  50;
        }
        else if(scene->player1->Rotation == ALLEGRO_PI/2){//Shoot Left.
                Position.x = scene->player1->x-50;
                Position.y = scene->player1->y;
                vx = -50;
        }
        else if(scene->player1->Rotation == ALLEGRO_PI){//Shoot Upward.
                Position.x = scene->player1->x;
                Position.y = scene->player1->y-50;
                vy = -50;
        }
        else if(scene->player1->Rotation == ALLEGRO_PI*3/2){//Shoot Right.
                Position.x = scene->player1->x+50;
                Position.y = scene->player1->y;
                vx = 50;
        }*/
        Velocity.x = vx;
        Velocity.y = vy;
     //   Sprite::Update(deltaTime);
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

	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
		getPlayScene()->IceGroup->RemoveObject(objectIterator);

}
