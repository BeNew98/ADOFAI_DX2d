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
	// ������ �Ž��� ������� �־�� �Ѵ�.


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
			MsgAssert("��Ʈ ��ġ�� �����߽��ϴ�.");
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
			MsgAssert("��Ʈ ������ �����߽��ϴ�.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}
