#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class GlowEffect :public GameEngineActor
{
public:
	// constrcuter destructer
	GlowEffect();
	~GlowEffect();

	// delete Function
	GlowEffect(const GlowEffect& _Other) = delete;
	GlowEffect(GlowEffect&& _Other) noexcept = delete;
	GlowEffect& operator=(const GlowEffect& _Other) = delete;
	GlowEffect& operator=(GlowEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

