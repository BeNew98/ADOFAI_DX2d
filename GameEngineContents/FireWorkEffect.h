#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

// ���� :
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
	RenderBaseValue m_sBaseValue;
	std::shared_ptr<GameEngineRenderUnit> m_pFWUnit;

};

