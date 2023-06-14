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

	std::shared_ptr<class GameEngineSpriteRenderer>GetRender()
	{
		return m_pRender;
	}
	void SetGlow(GlowType _Type)
	{
		m_sType = _Type;
	}
	void SetIndex(int _Index)
	{
		m_iIndex = _Index;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_pRender = nullptr;
	TileDeg m_sDeg = {};
	GlowType m_sType = GlowType::ROUND;
	int m_iIndex = 0;
	float m_fTime = 0.f;
	bool m_bColor = false;

	bool m_bCheckValue = false;
};

