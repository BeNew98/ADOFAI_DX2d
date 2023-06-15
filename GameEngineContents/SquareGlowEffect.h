#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class SquareGlowEffect :public GameEngineActor
{
public:
	// constrcuter destructer
	SquareGlowEffect();
	~SquareGlowEffect();

	// delete Function
	SquareGlowEffect(const SquareGlowEffect& _Other) = delete;
	SquareGlowEffect(SquareGlowEffect&& _Other) noexcept = delete;
	SquareGlowEffect& operator=(const SquareGlowEffect& _Other) = delete;
	SquareGlowEffect& operator=(SquareGlowEffect&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer>GetRender()
	{
		return m_pRender;
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
	int m_iIndex = 0;
	bool m_bColor = false;
	bool m_bCheckValue = false;
};

