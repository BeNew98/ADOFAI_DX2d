#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :

struct TileInfo
{
	float NextRatio = 0;
	bool Slow = false;
	bool Fast = false;
	bool EndTile = false;
};

struct StageInfo
{
	std::vector<TileInfo> AllTile;
	int BPM = 0;
	float fitch = 0.f;
};
class EditLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EditLevel();
	~EditLevel();

	// delete Function
	EditLevel(const EditLevel& _Other) = delete;
	EditLevel(EditLevel&& _Other) noexcept = delete;
	EditLevel& operator=(const EditLevel& _Other) = delete;
	EditLevel& operator=(EditLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	std::map<int, StageInfo> AllStage;
};

