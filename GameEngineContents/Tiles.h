#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Tiles : public GameEngineActor
{
public:
	// constrcuter destructer
	Tiles();
	~Tiles();

	// delete Function
	Tiles(const Tiles& _Other) = delete;
	Tiles(Tiles&& _Other) noexcept = delete;
	Tiles& operator=(const Tiles& _Other) = delete;
	Tiles& operator=(Tiles&& _Other) noexcept = delete;

	static Tiles* Tile;

	void CreateTile(TileDeg _TileDeg);

protected:
	void Start() override;

private:

};

