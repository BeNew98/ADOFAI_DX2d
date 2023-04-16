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
	// 이전에 매쉬는 만들어져 있어야 한다.

	new int();

	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::ChangeLevel("PlayLevel");
}

void DFICore::GameEnd()
{

}