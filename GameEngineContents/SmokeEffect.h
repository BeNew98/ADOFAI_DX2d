#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class SmokeEffect :public GameEngineActor
{
public:
	// constrcuter destructer
	SmokeEffect();
	~SmokeEffect();

	// delete Function
	SmokeEffect(const SmokeEffect& _Other) = delete;
	SmokeEffect(SmokeEffect&& _Other) noexcept = delete;
	SmokeEffect& operator=(const SmokeEffect& _Other) = delete;
	SmokeEffect& operator=(SmokeEffect&& _Other) noexcept = delete;

	void SetColor(float4 _Color);
protected:
	void Start() override;
	void Update(float _DeltaTime)override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_pRender = nullptr;
	float m_fTime = 0.f;
	float m_fRatio = 1.f;
};

