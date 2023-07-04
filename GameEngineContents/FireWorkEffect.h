#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

struct FWCBValue
{
	float4 fTime;
	float4 ScreenSize;
	float4 PlusColor = float4::Red;
};
// Ό³Έν :
class FireWorkEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	FireWorkEffect();
	~FireWorkEffect();

	// delete Function
	FireWorkEffect(const FireWorkEffect& _Other) = delete;
	FireWorkEffect(FireWorkEffect&& _Other) noexcept = delete;
	FireWorkEffect& operator=(const FireWorkEffect& _Other) = delete;
	FireWorkEffect& operator=(FireWorkEffect&& _Other) noexcept = delete;
protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	FWCBValue m_sBaseValue;
	std::shared_ptr<GameEngineRenderUnit> m_pFWUnit;
};

