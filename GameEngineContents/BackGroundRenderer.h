#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// Ό³Έν :
class BackGroundRenderer :public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	BackGroundRenderer();
	~BackGroundRenderer();

	// delete Function
	BackGroundRenderer(const BackGroundRenderer& _Other) = delete;
	BackGroundRenderer(BackGroundRenderer&& _Other) noexcept = delete;
	BackGroundRenderer& operator=(const BackGroundRenderer& _Other) = delete;
	BackGroundRenderer& operator=(BackGroundRenderer&& _Other) noexcept = delete;
	static void SwitchMonoChrome(bool _Value)
	{
		if (_Value)
		{
			m_pMonoChrome.x = 1.f;
		}
		else
		{
			m_pMonoChrome.x = 0.f;
		}
	}
protected:	
	void Start()override;
	void Update(float _Deltatime)override;
private:
	static float4 m_pMonoChrome;
};

