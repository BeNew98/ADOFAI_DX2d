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

protected:	
	void Start()override;

private:

};

