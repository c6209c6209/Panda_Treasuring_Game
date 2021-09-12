#ifndef SINGLESETTINGSCENE_HPP_INCLUDED
#define SINGLESETTINGSCENE_HPP_INCLUDED

#include "IScene.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"

class SingleSettingScene final : public Engine::IScene {
private:
	ALLEGRO_SAMPLE_INSTANCE* bgmInstance;
public:
    Group* UIGroup;
    Group* CharacterGroup;
	explicit SingleSettingScene() = default;
	void Initialize() override;
	void PlayOnClick(int stage, int BamID, int HPID);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif // SINGLESETTINGSCENE_HPP_INCLUDED
