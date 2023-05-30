#include "PrecompileHeader.h"
#include "EditGui.h"

#include <GameEngineBase/GameEngineSerializer.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Tiles.h"
#include "EditLevel.h"

EditGui::EditGui() 
{
}

EditGui::~EditGui() 
{
}

void EditGui::Start()
{
	AllStage.resize(m_LevelSize);
	
	CreateTile(GameEngineCore::GetCurLevel(), TileDeg::Deg0);
}

void EditGui::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{

	TileInfo CurTileInfo = AllStage[m_CurLevel].AllTile[AllStage[m_CurLevel].TileSize - 1];
	ImGui::Text("CurDegree: %s", GameEngineString::ToString(m_CurDegree).c_str());
	ImGui::Separator();

	ImGui::Text("<CurTile Info>");
	ImGui::Columns(2);
	ImGui::Text("Position");
	ImGui::NextColumn();
	ImGui::Text("x: %f", CurTileInfo.Position.x);
	ImGui::Text("y: %f", CurTileInfo.Position.y);
	ImGui::Text("z: %f", CurTileInfo.Position.z);
	ImGui::Text("w: %f", CurTileInfo.Position.w);
	ImGui::NextColumn();
	ImGui::Separator();

	ImGui::Text("StartPivotPos");
	ImGui::NextColumn();
	ImGui::Text("x: %f", CurTileInfo.Tile->GetStartPivotPos().x);
	ImGui::Text("y: %f", CurTileInfo.Tile->GetStartPivotPos().y);
	ImGui::Text("z: %f", CurTileInfo.Tile->GetStartPivotPos().z);
	ImGui::Text("w: %f", CurTileInfo.Tile->GetStartPivotPos().w);
	ImGui::NextColumn();
	ImGui::Separator();


	ImGui::Text("EndPivotPos");
	ImGui::NextColumn();
	ImGui::Text("x: %f", CurTileInfo.Tile->GetEndPivotPos().x);
	ImGui::Text("y: %f", CurTileInfo.Tile->GetEndPivotPos().y);
	ImGui::Text("z: %f", CurTileInfo.Tile->GetEndPivotPos().z);
	ImGui::Text("w: %f", CurTileInfo.Tile->GetEndPivotPos().w);
	ImGui::NextColumn();
	ImGui::Columns(1);
	ImGui::Separator();


	ImGui::Text("Create Tile:");
	if (ImGui::Button("0")) { CreateTile(Level, TileDeg::Deg0); }
	ImGui::SameLine();
	if (ImGui::Button("45")) { CreateTile(Level, TileDeg::Deg45); }
	ImGui::SameLine();
	if (ImGui::Button("60")) { CreateTile(Level, TileDeg::Deg60); }
	ImGui::SameLine();
	if (ImGui::Button("90")) { CreateTile(Level, TileDeg::Deg90); }
	ImGui::SameLine();
	if (ImGui::Button("120")) { CreateTile(Level, TileDeg::Deg120); }
	ImGui::SameLine();
	if (ImGui::Button("135")) { CreateTile(Level, TileDeg::Deg135); }

	if (ImGui::Button("225")) { CreateTile(Level, TileDeg::Deg225); }
	ImGui::SameLine();
	if (ImGui::Button("240")) { CreateTile(Level, TileDeg::Deg240); }
	ImGui::SameLine();
	if (ImGui::Button("270")) { CreateTile(Level, TileDeg::Deg270); }
	ImGui::SameLine();
	if (ImGui::Button("300")) { CreateTile(Level, TileDeg::Deg300); }
	ImGui::SameLine();
	if (ImGui::Button("310")) { CreateTile(Level, TileDeg::Deg315); }
	ImGui::Separator();

	if (ImGui::Button("Delete CurTile")) { DeleteCurTile(); }

	if (ImGui::Button("Save")) { Save(); }
	ImGui::SameLine();
	if (ImGui::Button("Load")) { Load(); };
}

void EditGui::CreateTile(std::shared_ptr<class GameEngineLevel> Level, TileDeg _Deg)
{
	std::shared_ptr<Tiles> pTile = Level->CreateActor<Tiles>();
	pTile->CreateTile(_Deg);
	int iDeg = static_cast<int>(_Deg);

	int m_CurTileSize = static_cast<int>(AllStage[m_CurLevel].AllTile.size());

	if (m_CurTileSize != 0)
	{
		//이전 타일
		std::shared_ptr<Tiles> PrevTile = AllStage[m_CurLevel].AllTile[m_CurTileSize - 1].Tile;		

		float4 PrevTilesEndPivotPos = PrevTile->GetEndPivotPos();
		
		pTile->GetTransform()->SetLocalRotation({ 0.f,0.f,static_cast<float>(m_CurDegree) });
		float4 StartBetPos = pTile->GetStartBetPos();
		StartBetPos.RotaitonZDeg(static_cast<float>(m_CurDegree));

		
		float4 CurSettingPos = PrevTilesEndPivotPos - StartBetPos;
		
		pTile->GetTransform()->SetLocalPosition(CurSettingPos);
		
		
		m_CurDegree += iDeg;

		if (m_CurDegree >=360)
		{
			m_CurDegree -= 360;
		}
	}

	TileInfo Info = {};
	Info.Tile = pTile;
	Info.NextRatio = static_cast<float>(iDeg);
	Info.Position = pTile->GetTransform()->GetWorldPosition();
	AllStage[m_CurLevel].AllTile.push_back(Info);


	//AllStage[m_CurLevel].AllTile[AllStage[m_CurLevel].TileSize]=Info;

	//AllStage[m_CurLevel].AllTile[m_CurTileSize].NextRatio = static_cast<float>(iDeg);
	//
	//AllStage[m_CurLevel].AllTile[m_CurTileSize].Tile = pTile;
	//AllStage[m_CurLevel].AllTile[m_CurTileSize].Position = pTile->GetTransform()->GetWorldPosition();
	++AllStage[m_CurLevel].TileSize;


	Level->GetMainCamera()->GetTransform()->SetWorldPosition(pTile->GetTransform()->GetWorldPosition());
}

void EditGui::Save()
{	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Text");
	std::string Initpath = NewDir.GetPath().GetFullPath();


	OPENFILENAME ofn = {};


	std::wstring strTileFolderPath = {};
	strTileFolderPath.assign(Initpath.begin(), Initpath.end());
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = NULL;//'\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;


	GameEngineSerializer Ser = {};

	for (size_t i = 0; i < AllStage[m_CurLevel].TileSize; i++)
	{
		Ser.Write(&AllStage[m_CurLevel].AllTile[i].NextRatio, sizeof(float));
	}

	std::string dir = {};
	std::wstring filename = szFilePath;
	dir.assign(filename.begin(), filename.end());

	GameEngineFile file = GameEngineFile(dir);
	
	file.SaveBin(Ser);
}

void EditGui::Load()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Text");
	std::string Initpath = NewDir.GetPath().GetFullPath();


	OPENFILENAME ofn = {};


	std::wstring strTileFolderPath = {};
	strTileFolderPath.assign(Initpath.begin(), Initpath.end());
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = NULL; //'\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	std::string dir = {};
	std::wstring filename = szFilePath;
	dir.assign(filename.begin(), filename.end());

	GameEngineFile file = GameEngineFile(dir);


	GameEngineSerializer Ser = {};
	file.LoadBin(Ser);
	float fRatio = 0.f;
	TileInfo Info = {};

	for (size_t i = 0; i < AllStage[m_CurLevel].AllTile.size(); i++)
	{
		AllStage[m_CurLevel].AllTile[i].Tile->Death();
	}
	size_t TileSize = file.GetFileSize() / sizeof(float);
	AllStage[m_CurLevel].AllTile.clear();
	AllStage[m_CurLevel].AllTile.reserve(TileSize);
	
	for (size_t i = 0; i < TileSize; i++)
	{
		Ser.Read(&fRatio, sizeof(float));
		if (i == 0)
		{
			m_CurDegree = 0;
			AllStage[m_CurLevel].TileSize = 0;
			//continue;
		}
		CreateTile(GameEngineCore::GetCurLevel(), static_cast<TileDeg>(fRatio));
	}
}

void EditGui::DeleteCurTile()
{
	if (0 == AllStage[m_CurLevel].TileSize - 1)
	{
		MessageBoxA(nullptr,  "첫 타일은 지울수 없습니다.", "주의", MB_OK);
		return;
	}
	TileInfo info = AllStage[m_CurLevel].AllTile[AllStage[m_CurLevel].TileSize-1];
	info.Tile->Death();
	std::vector<TileInfo>::iterator iter = AllStage[m_CurLevel].AllTile.end();
	AllStage[m_CurLevel].AllTile.erase(iter -1);
	m_CurDegree -= static_cast<int>(info.NextRatio);
	--AllStage[m_CurLevel].TileSize;
}