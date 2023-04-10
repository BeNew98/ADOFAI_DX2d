#pragma once

// Ό³Έν :
class GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineDirectBuffer();
	~GameEngineDirectBuffer();

	// delete Function
	GameEngineDirectBuffer(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer(GameEngineDirectBuffer&& _Other) noexcept = delete;
	GameEngineDirectBuffer& operator=(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer& operator=(GameEngineDirectBuffer&& _Other) noexcept = delete;

protected:

private:

};

