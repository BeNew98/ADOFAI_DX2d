#pragma once

// Ό³Έν :
class GameEngineVertex
{
public:
	// constrcuter destructer
	GameEngineVertex();
	~GameEngineVertex();

	// delete Function
	GameEngineVertex(const GameEngineVertex& _Other) = delete;
	GameEngineVertex(GameEngineVertex&& _Other) noexcept = delete;
	GameEngineVertex& operator=(const GameEngineVertex& _Other) = delete;
	GameEngineVertex& operator=(GameEngineVertex&& _Other) noexcept = delete;

protected:

private:

};

