#include "PrecompileHeader.h"
#include "DFICore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "TitleLevel.h"

DFICore::DFICore()
{
}

DFICore::~DFICore()
{
}

void DFICore::GameStart()
{
	// ������ �Ž��� ������� �־�� �Ѵ�.

	new int();

	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::ChangeLevel("PlayLevel");
}

void DFICore::GameEnd()
{

}