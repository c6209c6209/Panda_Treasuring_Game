#ifndef TWOCOOPERATESETTINGSCENE_HPP_INCLUDED
#define TWOCOOPERATESETTINGSCENE_HPP_INCLUDED

#include "IScene.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"

class TwoCooperateSettingScene final : public Engine::IScene {
private:
	ALLEGRO_SAMPLE_INSTANCE* bgmInstance;
public:
    Group* UIGroup;
    Group* Character1Group;
    Group* Character2Group;
	explicit TwoCooperateSettingScene() = default;
	void Initialize() override;
	void PlayOnClick(int stage, int BamID, int HPID);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};


#endif // TWOCOOPERATESETTINGSCENE_HPP_INCLUDED
