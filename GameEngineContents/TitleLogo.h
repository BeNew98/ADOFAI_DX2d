#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TitleLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;

	void AlphaSwitch()
	{
		m_bAlpha = !m_bAlpha;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_pLogo = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_pLogoShadow = nullptr;

	bool m_bAlpha = false;
	float m_fAlpha = 0.f;

};

