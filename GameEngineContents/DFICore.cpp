#include "PrecompileHeader.h"
#include "DFICore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "TitleLevel.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

DFICore::DFICore()
{
}

DFICore::~DFICore()
{
}

void DFICore::ContentsResourcesCreate()
{
	// �ؽ�ó �ε常 �� �������� �ϰ� �����ϴ� ���� ���̱�


}


void DFICore::GameStart()
{
	// ������ �Ž��� ������� �־�� �Ѵ�.

	new int();

	//GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");


	ContentsResourcesCreate();



	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::ChangeLevel("TitleLevel");
}

void DFICore::GameEnd()
{

}