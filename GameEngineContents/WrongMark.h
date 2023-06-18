#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

// Ό³Έν :
class WrongMark : public GameEngineActor
{
public:
	// constrcuter destructer
	WrongMark();
	~WrongMark();

	// delete Function
	WrongMark(const WrongMark& _Other) = delete;
	WrongMark(WrongMark&& _Other) noexcept = delete;
	WrongMark& operator=(const WrongMark& _Other) = delete;
	WrongMark& operator=(WrongMark&& _Other) noexcept = delete;

	void SetTxt(const std::string_view& _Text)
	{
		m_pFontRenderer->SetText(_Text);
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_pRender = nullptr;
	std::shared_ptr<GameEngineFontRenderer> m_pFontRenderer = nullptr;
	bool m_bAlpha = false;
	float m_fAlpha = 1.f;




};

