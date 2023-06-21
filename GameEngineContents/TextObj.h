#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

// Ό³Έν :
class TextObj : public GameEngineActor
{
public:
	// constrcuter destructer
	TextObj();
	~TextObj();

	// delete Function
	TextObj(const TextObj& _Other) = delete;
	TextObj(TextObj&& _Other) noexcept = delete;
	TextObj& operator=(const TextObj& _Other) = delete;
	TextObj& operator=(TextObj&& _Other) noexcept = delete;

	void SetTxt(const std::string_view& _Text)
	{
		m_pFontRenderer->SetText(_Text);
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFontRenderer> m_pFontRenderer = nullptr;
	bool m_bAlpha = false;
	float m_fAlpha = 1.f;
};

