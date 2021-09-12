#ifndef BRIDGINGSCENE_HPP_INCLUDED
#define BRIDGINGSCENE_HPP_INCLUDED

#endif // BRIDGINGSCENE_HPP_INCLUDED
#include "IScene.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"

class BridgingScene final : public Engine::IScene {
private:
	ALLEGRO_SAMPLE_INSTANCE* bgmInstance;
public:
	explicit BridgingScene() = default;
	void Initialize() override;
	void PlayOnClick(int stage, int BamID, int HPID);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
	int BridgeID = 1;
};
