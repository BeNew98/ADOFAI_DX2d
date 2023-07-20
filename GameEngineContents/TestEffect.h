#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

struct testValue
{
	float4 fTime;
	float4 ScreenSize;
	float4 PlusColor = float4::Red;
	float4 Dir = { 0.f,1.f,0.f,0.f };
};

// ���� :
class TestEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	TestEffect();
	~TestEffect();

	// delete Function
	TestEffect(const TestEffect& _Other) = delete;
	TestEffect(TestEffect&& _Other) noexcept = delete;
	TestEffect& operator=(const TestEffect& _Other) = delete;
	TestEffect& operator=(TestEffect&& _Other) noexcept = delete;

	void SetColor(float4 _Color)
	{
		m_sBaseValue.PlusColor = _Color;
	}
	void SetDir(float4 _Dir)
	{
		m_sBaseValue.Dir = _Dir;
	}
protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	testValue m_sBaseValue;
	std::shared_ptr<GameEngineRenderUnit> m_pFWUnit;
	bool m_bUpdate = false;
};
