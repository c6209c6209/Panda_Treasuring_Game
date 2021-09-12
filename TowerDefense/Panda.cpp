#include <random>
#include <allegro5/allegro_primitives.h>
#include "PlayScene.hpp"
#include "Label.hpp"
#include "Panda.hpp"
#include "AudioHelper.hpp"
#include "Treasure.hpp"
#include "ExplosionEffect.hpp"
#include "DirtyEffect.hpp"

PlayScene* Panda::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Panda::Panda(std::string img, float x, float y, float w, float h, float hp) :
	Engine::Sprite(img, x, y, w, h),  hp(hp){
    CollisionRadius = 15;
}
void Panda::Update(float deltaTime) {
	//Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	// Pre-calculate the velocity.
	//move panda.
     Velocity.x = vx;
     Velocity.y = vy;

     for (auto& it : scene->TreasureGroup->GetObjects()) {
		Treasure* treasure = dynamic_cast<Treasure*>(it);
		if (!treasure->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, treasure->Position, treasure->CollisionRadius)) {
			treasure->Hit();
			return;
		}
	}

 //   getPlayScene()->PlayerGroup->RemoveObject(objectIterator);
 //   getPlayScene()->PlayerGroup->AddNewObject(objectIterator);
//	float remainSpeed = speed * deltaTime;
/*	while (remainSpeed != 0) {
/*		if (path.empty()) {
			// Reach end point.
			getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
			getPlayScene()->Hit();
			return;
		}
		Engine::Point target = path.back() * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
		Engine::Point vec = target - Position;
		Engine::Point normalized = vec.Normalize();
		if (remainSpeed - vec.Magnitude() > 0) {
			Position = target;
			path.pop_back();
			remainSpeed -= vec.Magnitude();
		}
		else {
			Velocity = normalized * remainSpeed / deltaTime;
			remainSpeed = 0;
		}
	}*/
//	Rotation = atan2(Velocity.y, Velocity.x);
    if(shoot){
        CreateIce();
    }
	Sprite::Update(deltaTime);
}
	/*imgBase.Position = Position;
	imgBase.Tint = Tint;
	if (!Enabled)
		return;
	if (Target) {
		Engine::Point diff = Target->Position - Position;
		if (diff.Magnitude() > CollisionRadius) {
			Target->lockedTurrets.erase(lockedTurretIterator);
			Target = nullptr;
			lockedTurretIterator = std::list<Turret*>::iterator();
		}
	}
	if (!Target) {
		// Lock first seen target.
		// Can be improved by Spatial Hash, Quad Tree, ...
		// However simply loop through all enemies is enough for this program.
		for (auto& it : scene->EnemyGroup->GetObjects()) {
			Engine::Point diff = it->Position - Position;
			if (diff.Magnitude() <= CollisionRadius) {
				Target = dynamic_cast<Enemy*>(it);
				Target->lockedTurrets.push_back(this);
				lockedTurretIterator = std::prev(Target->lockedTurrets.end());
				break;
			}
		}
	}
	if (Target) {
		Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
		Engine::Point targetRotation = (Target->Position - Position).Normalize();
		float maxRotateRadian = rotateRadian * deltaTime;
		float cosTheta = originRotation.Dot(targetRotation);
		// Might have floating-point precision error.
		if (cosTheta > 1) cosTheta = 1;
		else if (cosTheta < -1) cosTheta = -1;
		float radian = acos(cosTheta);
		Engine::Point rotation;
		if (abs(radian) <= maxRotateRadian)
			rotation = targetRotation;
		else
			rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
		// Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
		Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
		// Shoot reload.
		reload -= deltaTime;
		if (reload <= 0) {
			// shoot.
			reload = coolDown;
			CreateBullet();
		}
	}*/

/*void Panda::Hit() {
    getPlayScene()->DecreaseLife(score);
}*/

void Panda::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}

void Panda::updateVx(float newVx){
    vx = newVx;
}
void Panda::updateVy(float newVy){
    vy = newVy;
}
float Panda::getVx(){
    return Velocity.x;
}
float Panda::getVy(){
    return Velocity.y;
}
float Panda::getX(){
    return Position.x;
}
float Panda::getY(){
    return Position.y;
}

void Panda::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
	AudioHelper::PlayAudio("explosion.wav");
}

