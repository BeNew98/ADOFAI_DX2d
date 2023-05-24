#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "MapSettingStruct.h"

struct TileInfo
{
	std::shared_ptr<class Tiles> Tile;
	float4 Position = float4::Zero;
	float NextRatio = 0;
	bool Slow = false;
	bool Fast = false;
	bool EndTile = false;
};

struct StageInfo
{
	std::vector<TileInfo> AllTile;
	int TileSize = 0;
	int BPM = 0;
	float fitch = 0.f;
};

// Ό³Έν :
class EditGui : public GameEngineGUIWindow
{
	friend class EditLevel;
public:
	// constrcuter destructer
	EditGui();
	~EditGui();

	// delete Function
	EditGui(const EditGui& _Other) = delete;
	EditGui(EditGui&& _Other) noexcept = delete;
	EditGui& operator=(const EditGui& _Other) = delete;
	EditGui& operator=(EditGui&& _Other) noexcept = delete;

protected:
	void Start() override; 
	void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) override;

private:
	int m_LevelSize = 3;
	int m_CurLevel = 0;
	int m_CurDegree = 0;
	std::vector<StageInfo> AllStage;

	void CreateTile(std::shared_ptr<class GameEngineLevel> Level, TileDeg _Deg);

};

