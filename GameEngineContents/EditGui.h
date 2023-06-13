#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "MapSettingStruct.h"

struct TileInfo
{
	std::shared_ptr<class Tiles> m_pTile = nullptr;

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
	EditGui(EditGui&& _Other) noexcept = delete;
	EditGui& operator=(const EditGui& _Other) = delete;
	EditGui& operator=(EditGui&& _Other) noexcept = delete;

	static EditGui* Editor;

	void LoadtoString(std::string_view _FileName = "");

	StageInfo GetStageInfo(int _Index)
	{
		return m_vecAllStage[_Index];
	}

	void SetLevel(int _Level)
	{
		m_iLevelValue = _Level;
	}

protected:
	void Start() override; 
	void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) override;

private:
	int m_iLevelSize = 1;
	int m_iCurLevel = 0;
	int m_iCurDegree = 0;
	int m_iX = 0;
	int m_iY = 0;
	int m_iLevelValue = 0;
	float m_iTileSize = 96.f;


	std::vector<StageInfo> m_vecAllStage;

	std::shared_ptr<class Player> m_pPlayer = nullptr;

	void CreateTile(std::shared_ptr< GameEngineLevel> _Level, float4 _Data);
	void CreateTile(std::shared_ptr< GameEngineLevel> _Level, TileDeg _Deg);
	void CreateSquare(std::shared_ptr< GameEngineLevel> _Level, TileDeg _Deg);
	void Save();
	void Load();

	void CreatePlayer(std::shared_ptr< GameEngineLevel> _Level);
	void DeleteCurTile();
	void ClearAllTile();
};

