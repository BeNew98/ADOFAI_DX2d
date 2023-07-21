#include "PrecompileHeader.h"
#include "DFICore.h"
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "EditLevel.h"
#include "CenterLevel.h"
#include "EditGui.h"

DFICore::DFICore()
{
}

DFICore::~DFICore()
{
}



void DFICore::GameStart()
{
	// 이전에 매쉬는 만들어져 있어야 한다.


	//GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");

	

	ContentsResourcesCreate();

	InstallFont();

	GameEngineCore::CreateLevel<EditLevel>();
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>() ;
	GameEngineCore::CreateLevel<CenterLevel>();
	std::string Level = "PlayLevel";
	if (Level== "PlayLevel")
	{
		EditGui::Editor->SetLevel(1);
		EditGui::Editor->SetBPM(150);
	}
	GameEngineCore::ChangeLevel("CenterLevel");

}

void DFICore::GameEnd()
{
	RemoveFont();
}


void DFICore::InstallFont()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Text");
	std::vector<GameEngineFile> FontFiles = Dir.GetAllFile({ ".otf", ".ttf" });
	for (GameEngineFile& File : FontFiles)
	{
		if (0 == AddFontResourceA(File.GetFullPath().c_str()))
		{
			MsgAssert("폰트 설치에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}

void DFICore::RemoveFont()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Text");
	std::vector<GameEngineFile> FontFiles = Dir.GetAllFile({ ".otf", ".ttf" });
	for (GameEngineFile& File : FontFiles)
	{
		if (0 == RemoveFontResourceA(File.GetFullPath().data()))
		{
			MsgAssert("폰트 삭제에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}
