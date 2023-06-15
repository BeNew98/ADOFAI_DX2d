#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class RoundGlowEffect :public GameEngineActor
{
public:
	// constrcuter destructer
	RoundGlowEffect();
	~RoundGlowEffect();

	// delete Function
	RoundGlowEffect(const RoundGlowEffect& _Other) = delete;
	RoundGlowEffect(RoundGlowEffect&& _Other) noexcept = delete;
	RoundGlowEffect& operator=(const RoundGlowEffect& _Other) = delete;
	RoundGlowEffect& operator=(RoundGlowEffect&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_pRender = nullptr;

};

