#ifndef STARTSCENE_HPP
#define STARTSCENE_HPP
#include "IScene.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"

class StartScene final : public Engine::IScene {
private:
	float ticks;
public:
    Group* UIGroup;
	explicit StartScene() = default;
	void Initialize() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
};

#endif // WINSCENE_HPP
