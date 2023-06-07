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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_pRender = nullptr;
	TileDeg m_sDeg = {};
};

