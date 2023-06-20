#pragma once
#include <GameEngineCore/GameEngineGUI.h>

struct TileInfo
{
	std::shared_ptr<class Tiles> m_pTile = nullptr;

};
struct StageInfo
{
	std::vector<TileInfo> AllTile;
	int BPM = 0;
	float RotSpeed = 0.f;
	float fitch = 0.f;
};

// 설명 :
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

	void LoadtoString(const std::string_view& _FileName = "");

	StageInfo GetStageInfo(int _Index)
	{
		return m_vecAllStage[_Index];
	}

	void SetLevel(int _Level)
	{
		m_iLevelValue = _Level;
	}
	
	void SetBPM(int _BPM)
	{
		if (_BPM == 0)
		{
			MsgAssert("BPM이 0입니다");
			return;
		}
		m_vecAllStage[0].RotSpeed = static_cast<float>(180.f * (_BPM / 60.f));
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

	bool m_bSwitch = false;


	std::vector<StageInfo> m_vecAllStage;

	void CreateTile(std::shared_ptr< GameEngineLevel> _Level, float4 _Data);
	void CreateTile(std::shared_ptr< GameEngineLevel> _Level, TileDeg _Deg);
	void CreateSquare(std::shared_ptr< GameEngineLevel> _Level, TileDeg _Deg);
	void Save();
	void Load();

	void CreatePlayer(std::shared_ptr< GameEngineLevel> _Level);
	void DeleteCurTile();
};

