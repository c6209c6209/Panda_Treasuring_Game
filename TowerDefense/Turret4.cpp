#include "PlayScene.hpp"
#include "Turret4.hpp"
#include "Bullet6.hpp"
#include "AudioHelper.hpp"

const int Turret4::Price = 400;
Turret4::Turret4(float x, float y, float w, float h) :
	Turret("play/tower-base.png", "play/turret-4.png", x, y, w,h, 1000, Price, 4) {
}
void Turret4::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new Bullet6(Position + normalized * 10 - normal * 6, diff, rotation, this));
	getPlayScene()->BulletGroup->AddNewObject(new Bullet6(Position + normalized * 10 + normal * 6, diff, rotation, this));
	AudioHelper::PlayAudio("missile.wav");
}
