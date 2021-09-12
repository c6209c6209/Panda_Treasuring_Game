#ifndef MAINSETTINGSCENE_HPP_INCLUDED
#define MAINSETTINGSCENE_HPP_INCLUDED

#include "IScene.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"

class MainSettingScene final : public Engine::IScene {
private:
	ALLEGRO_SAMPLE_INSTANCE* bgmInstance;
public:
    Group* UIGroup;
	explicit MainSettingScene() = default;
	void Initialize() override;
	void PlayOnClick(int stage);
	/*void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);*/
};

#endif // MAINSETTINGSCENE_HPP_INCLUDED
