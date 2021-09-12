#include "ipePanda.hpp"
#include "GreenIce.hpp"
#include "AudioHelper.hpp"
ipePanda::ipePanda(int x, int y, int w, int h) : Panda("play/ipepanda.png", x, y, w, h, 100) {
 // TODO 2 (6/8): You can imitate the 2 files: 'SoldierEnemy.hpp', 'SoldierEnemy.cpp' to create a new enemy.
}

void ipePanda::CreateIce() {
    //diffence?.
 Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
 float rotation = atan2(diff.y, diff.x);
 Engine::Point normalized = diff.Normalize();
 Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
 // Change Ice position to the front of the gun barrel.
 /*   if(Rotation == 0){//shoot downward.
        Position.x = x;
        Position.y = y+50;
        getPlayScene()->IceGroup->AddNewObject(new GreenIce(Position + normalized * 10 - normal * 6, diff, rotation, this));
    }
    else if(Rotation == ALLEGRO_PI/2){//Shoot Left.
            Position.x = x-50;
            Position.y = y;
            getPlayScene()->IceGroup->AddNewObject(new GreenIce(Position + normalized * 10 - normal * 6, diff, rotation, this));
    }
    else if(Rotation == ALLEGRO_PI){//Shoot Upward.
            Position.x = x;
            Position.y = y-50;
            getPlayScene()->IceGroup->AddNewObject(new GreenIce(Position + normalized * 10 - normal * 6, diff, rotation, this));
    }
    else if(Rotation == ALLEGRO_PI*3/2){//Shoot Right.
                Position.x = x+50;
                Position.y = y;
        getPlayScene()->IceGroup->AddNewObject(new GreenIce(Position + normalized * 10 - normal * 6, diff, rotation, this));
    }*/
 getPlayScene()->IceGroup->AddNewObject(new GreenIce(Position + normalized * 10 - normal * 6, diff, rotation, this));
// getPlayScene()->IceGroup->AddNewObject(new GreenIce(Position + normalized * 10 + normal * 6, diff, rotation, this));
// AudioHelper::PlayAudio("missile.wav");
}
