#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "MapSettingStruct.h"

struct TileInfo
{
	std::shared_ptr<class Tiles> m_pTile;
	float m_fNextRatio = 0;
	bool m_Slow = false;
	bool m_Fast = false;
};

struct StageInfo
{
	std::vector<TileInfo> AllTile;
	int BPM = 0;
	float fitch = 0.f;
};

// Ό³Έν :
class EditGui : public GameEngineGUIWindow
{
	friend class EditLevel;
	friend class Player;
public:
	// constrcuter destructer
	EditGui();
	~EditGui();

	// delete Function
	EditGui(const EditGui& _Other) = delete;
	EditGui(EditGui&& _OLevelther) noexcept = delete;
	EditGui& operator=(const EditGui& _Other) = delete;
	EditGui& operator=(EditGui&& _Other) noexcept = delete;

	static EditGui* Editor;

protected:
	void Start() override; 
	void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) override;

private:
	int m_iLevelSize = 1;
	int m_iCurLevel = 0;
	int m_iCurDegree = 0;
	std::vector<StageInfo> m_vecAllStage;

	void CreateTile(std::shared_ptr< GameEngineLevel> _Level, TileDeg _Deg);
	void Save();
	void Load();
	void CreatePlayer(std::shared_ptr< GameEngineLevel> _Level);
	void DeleteCurTile();
	void ClearAllTile();
};

