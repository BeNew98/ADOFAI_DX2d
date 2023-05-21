#include "PrecompileHeader.h"
#include "DFICore.h"
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "EditLevel.h"
#include "CenterLevel.h"

DFICore::DFICore()
{
}

DFICore::~DFICore()
{
}

void DFICore::ContentsResourcesCreate()
{
	// 텍스처 로드만 각 레벨별로 하고 정리하는 습관 들이기


}


void DFICore::GameStart()
{
	// 이전에 매쉬는 만들어져 있어야 한다.

	new int();

	//GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");


	ContentsResourcesCreate();


	GameEngineCore::CreateLevel<EditLevel>();
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::CreateLevel<CenterLevel>();
	GameEngineCore::ChangeLevel("CenterLevel");
}

void DFICore::GameEnd()
{

}