#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "MapSettingStruct.h"

// ���� :
class EditGui : public GameEngineGUIWindow
{
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
	int LevelSize = 1;
	int CurDegree = 180;
	std::vector<StageInfo> AllStage;

	std::shared_ptr<GameEngineSpriteRenderer> m_Start;

	void CreateTile(TileDeg _Deg);
};

