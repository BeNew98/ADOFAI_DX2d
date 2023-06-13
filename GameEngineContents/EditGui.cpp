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


EditGui* EditGui::Editor = nullptr;

EditGui::EditGui() 
{
	Editor = this;
}

EditGui::~EditGui() 
{
}

void EditGui::Start()
{
	m_vecAllStage.resize(m_iLevelSize);
	
	//CreateTile(GameEngineCore::GetCurLevel(), TileDeg::Deg0);
}
int iCurTileNum = 0;
void EditGui::OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime)
{
	if (0<m_vecAllStage[m_iCurLevel].AllTile.size())
	{	
		TileInfo CurTileInfo = m_vecAllStage[m_iCurLevel].AllTile[m_vecAllStage[m_iCurLevel].AllTile.size() - 1];
		ImGui::Text("<CurTile Info>");
		ImGui::Separator();

		ImGui::Text("CurDegree: %s", GameEngineString::ToString(m_iCurDegree).c_str());
		ImGui::Text("CurTileNumber : %d", m_vecAllStage[m_iCurLevel].AllTile.size() - 1);
		ImGui::Columns(2);
		ImGui::Separator();

		ImGui::Text("Position");
		ImGui::NextColumn();
		ImGui::Text("x: %f", CurTileInfo.m_pTile->GetTransform()->GetLocalPosition().x);
		ImGui::Text("y: %f", CurTileInfo.m_pTile->GetTransform()->GetLocalPosition().y);
		ImGui::Text("z: %f", CurTileInfo.m_pTile->GetTransform()->GetLocalPosition().z);
		ImGui::Text("w: %f", CurTileInfo.m_pTile->GetTransform()->GetLocalPosition().w);
		ImGui::NextColumn();
		ImGui::Separator();

		ImGui::Text("StartPivotPos");
		ImGui::NextColumn();
		ImGui::Text("x: %f", CurTileInfo.m_pTile->GetStartPivotPos().x);
		ImGui::Text("y: %f", CurTileInfo.m_pTile->GetStartPivotPos().y);
		ImGui::Text("z: %f", CurTileInfo.m_pTile->GetStartPivotPos().z);
		ImGui::Text("w: %f", CurTileInfo.m_pTile->GetStartPivotPos().w);
		ImGui::NextColumn();
		ImGui::Separator();


		ImGui::Text("EndPivotPos");
		ImGui::NextColumn();
		ImGui::Text("x: %f", CurTileInfo.m_pTile->GetEndPivotPos().x);
		ImGui::Text("y: %f", CurTileInfo.m_pTile->GetEndPivotPos().y);
		ImGui::Text("z: %f", CurTileInfo.m_pTile->GetEndPivotPos().z);
		ImGui::Text("w: %f", CurTileInfo.m_pTile->GetEndPivotPos().w);
		ImGui::NextColumn();
		ImGui::Columns(1);
		ImGui::Separator();
	}


	ImGui::Text("Create Tile:");
	if (ImGui::Button("0")) { CreateTile(_Level, TileDeg::Deg0); }
	ImGui::SameLine();
	if (ImGui::Button("45")) { CreateTile(_Level, TileDeg::Deg45); }
	ImGui::SameLine();
	if (ImGui::Button("60")) { CreateTile(_Level, TileDeg::Deg60); }
	ImGui::SameLine();
	if (ImGui::Button("90")) { CreateTile(_Level, TileDeg::Deg90); }
	ImGui::SameLine();
	if (ImGui::Button("120")) { CreateTile(_Level, TileDeg::Deg120); }
	ImGui::SameLine();
	if (ImGui::Button("135")) { CreateTile(_Level, TileDeg::Deg135); }

	if (ImGui::Button("225")) { CreateTile(_Level, TileDeg::Deg225); }
	ImGui::SameLine();
	if (ImGui::Button("240")) { CreateTile(_Level, TileDeg::Deg240); }
	ImGui::SameLine();
	if (ImGui::Button("270")) { CreateTile(_Level, TileDeg::Deg270); }
	ImGui::SameLine();
	if (ImGui::Button("300")) { CreateTile(_Level, TileDeg::Deg300); }
	ImGui::SameLine();
	if (ImGui::Button("310")) { CreateTile(_Level, TileDeg::Deg315); }
	ImGui::Separator();

	if (ImGui::Button("Square")) { CreateSquare(_Level, TileDeg::Square); }
	ImGui::SameLine();
	if (ImGui::Button("Blank")) { CreateSquare(_Level, TileDeg::Blank); }
	ImGui::SameLine();
	if (ImGui::Button("NextRow")) { ++m_iY; m_iX = 0; CreateSquare(_Level, TileDeg::Square); }
	ImGui::Separator();

	if (ImGui::Button("Delete CurTile")) { DeleteCurTile(); }

	if (ImGui::Button("Save")) { Save(); }
	ImGui::SameLine();
	if (ImGui::Button("Load")) { Load(); };
	ImGui::Separator();

	if (ImGui::Button("PlayerCreate")) { CreatePlayer(_Level); };

	if (ImGui::InputInt("CamMoveToTile", &iCurTileNum))
	{
		if (iCurTileNum<0|| iCurTileNum>=m_vecAllStage[m_iCurLevel].AllTile.size())
		{
			return;
		}
		_Level->GetMainCamera()->GetTransform()->SetWorldPosition(m_vecAllStage[m_iCurLevel].AllTile[iCurTileNum].m_pTile->GetTransform()->GetLocalPosition());
	}

}

void EditGui::CreateTile(std::shared_ptr<GameEngineLevel> _Level, float4 _Data)
{
	m_iX = static_cast<int>(_Data.x);
	m_iY = static_cast<int>(_Data.y);
	CreateTile(_Level, static_cast<TileDeg>(_Data.z));
}

void EditGui::CreateTile(std::shared_ptr<class GameEngineLevel> _Level, TileDeg _Deg)
{
	if (_Deg == TileDeg::Square|| _Deg == TileDeg::Blank)
	{
		CreateSquare(_Level, _Deg);
		return;
	}
	std::shared_ptr<Tiles> pTile = _Level->CreateActor<Tiles>();
	pTile->CreateTile(_Deg);

	int iDeg = static_cast<int>(_Deg);
	int m_CurTileSize = static_cast<int>(m_vecAllStage[m_iCurLevel].AllTile.size());

	if (m_CurTileSize != 0)
	{
		//이전 타일
		std::shared_ptr<Tiles> PrevTile = m_vecAllStage[m_iCurLevel].AllTile[m_CurTileSize - 1].m_pTile;		

		float4 PrevTilesEndPivotPos = PrevTile->GetEndPivotPos();
		
		pTile->GetTransform()->SetLocalRotation({ 0.f,0.f,static_cast<float>(m_iCurDegree) });
		float4 StartBetPos = pTile->GetStartBetPos();
		StartBetPos.RotaitonZDeg(static_cast<float>(m_iCurDegree));

		
		float4 CurSettingPos = PrevTilesEndPivotPos - StartBetPos;
		
		pTile->GetTransform()->SetLocalPosition(CurSettingPos);		
		
		m_iCurDegree += iDeg;

		if (m_iCurDegree >=360)
		{
			m_iCurDegree -= 360;
		}
	}

	TileInfo Info = {};
	Info.m_pTile = pTile;
	Info.m_pTile->m_fData.z = static_cast<float>(iDeg);
	m_vecAllStage[m_iCurLevel].AllTile.push_back(Info);


	_Level->GetMainCamera()->GetTransform()->SetWorldPosition(pTile->GetTransform()->GetWorldPosition());
}

void EditGui::CreateSquare(std::shared_ptr<GameEngineLevel> _Level, TileDeg _Deg)
{
	std::shared_ptr<Tiles> pTile = _Level->CreateActor<Tiles>();
	pTile->CreateTile(_Deg);

	int iDeg = static_cast<int>(_Deg);
	
	pTile->GetTransform()->SetLocalPosition({ m_iX * m_iTileSize ,-m_iY * m_iTileSize });
	
	

	TileInfo Info = {};
	Info.m_pTile = pTile;
	Info.m_pTile->m_fData.x = static_cast<float>(m_iX);
	Info.m_pTile->m_fData.y = static_cast<float>(m_iY);
	Info.m_pTile->m_fData.z = static_cast<float>(iDeg);
	m_vecAllStage[m_iCurLevel].AllTile.push_back(Info);

	++m_iX;

	_Level->GetMainCamera()->GetTransform()->SetWorldPosition(pTile->GetTransform()->GetWorldPosition());
}

void EditGui::Save()
{	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Text");

	std::string Initpath = NewDir.GetPath().GetFullPath();
	std::wstring strTileFolderPath = GameEngineString::AnsiToUniCode(Initpath);


	OPENFILENAME ofn = {};
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
	for (size_t i = 0; i < m_vecAllStage[m_iCurLevel].AllTile.size(); i++)
	{
		Ser.Write(&m_vecAllStage[m_iCurLevel].AllTile[i].m_pTile->m_fData, sizeof(float4));
	}
	
	std::wstring filename = szFilePath;
	GameEngineString::UniCodeToAnsi(filename);

	GameEngineFile file = GameEngineFile(filename);
	
	file.SaveBin(Ser);
}

void EditGui::Load()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Text");
	std::string Initpath = NewDir.GetPath().GetFullPath();
	std::wstring strTileFolderPath = GameEngineString::AnsiToUniCode(Initpath);


	OPENFILENAME ofn = {};


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

	std::wstring filename = szFilePath;
	GameEngineString::UniCodeToAnsi(filename);

	GameEngineFile file = GameEngineFile(filename);
	

	size_t uSize = file.GetFileSize();
	GameEngineSerializer Ser = {};

	Ser.BufferResize(uSize+1);
	file.LoadBin(Ser);

	float4 fRatio = float4::Zero;
	TileInfo Info = {};

	for (size_t i = 0; i < m_vecAllStage[m_iCurLevel].AllTile.size(); i++)
	{
		m_vecAllStage[m_iCurLevel].AllTile[i].m_pTile->Death();
	}
	size_t TileSize = file.GetFileSize() / sizeof(float4);

	m_vecAllStage[m_iCurLevel].AllTile.clear();
	m_vecAllStage[m_iCurLevel].AllTile.reserve(TileSize);
	
	for (size_t i = 0; i < TileSize; i++)
	{
		Ser.Read(&fRatio, sizeof(float4));
		if (i == 0)
		{
			m_iCurDegree = 0;
			m_iX = 0;
			m_iY = 0;
		}
		CreateTile(GameEngineCore::GetCurLevel(),fRatio);
	}
	for (size_t i = 0; i < m_vecAllStage[m_iCurLevel].AllTile.size(); i++)
	{
		m_vecAllStage[m_iCurLevel].AllTile[i].m_pTile->DeathPivot();
	}
}
void EditGui::LoadtoString(std::string_view _FileName)
{
	std::string FileName = _FileName.data();
	if (_FileName =="")
	{
		FileName = "Level" + GameEngineString::ToString(m_iLevelValue);
	}
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Text");
	std::string Initpath = NewDir.GetPath().GetFullPath() + "\\" + FileName;


	GameEngineFile file = GameEngineFile(Initpath);


	size_t uSize = file.GetFileSize();
	GameEngineSerializer Ser = {};

	Ser.BufferResize(uSize + 1);
	file.LoadBin(Ser);

	float4 fRatio = float4::Zero;
	TileInfo Info = {};

	for (size_t i = 0; i < m_vecAllStage[m_iCurLevel].AllTile.size(); i++)
	{
		m_vecAllStage[m_iCurLevel].AllTile[i].m_pTile->Death();
	}
	size_t TileSize = file.GetFileSize() / sizeof(float4);

	m_vecAllStage[m_iCurLevel].AllTile.clear();
	m_vecAllStage[m_iCurLevel].AllTile.reserve(TileSize);

	for (size_t i = 0; i < TileSize; i++)
	{
		Ser.Read(&fRatio, sizeof(float4));
		if (i == 0)
		{
			m_iCurDegree = 0;
			m_iX = 0;
			m_iY = 0;
		}
		CreateTile(GameEngineCore::GetCurLevel(), fRatio);
	}
	for (size_t i = 0; i < m_vecAllStage[m_iCurLevel].AllTile.size(); i++)
	{
		m_vecAllStage[m_iCurLevel].AllTile[i].m_pTile->DeathPivot();
	}
}
void EditGui::CreatePlayer(std::shared_ptr<class GameEngineLevel> _Level)
{


}

void EditGui::DeleteCurTile()
{

	if (0 > m_vecAllStage[m_iCurLevel].AllTile.size() - 1)
	{
		return;
	}

	TileInfo info = m_vecAllStage[m_iCurLevel].AllTile[m_vecAllStage[m_iCurLevel].AllTile.size()-1];
	if (info.m_pTile->m_fData.z==360.f)
	{
		if (m_iX==0)
		{
			--m_iY;
			m_iX = m_vecAllStage[m_iCurLevel].AllTile[m_vecAllStage[m_iCurLevel].AllTile.size() - 1].m_pTile->m_fData.ix();
		}
		else
		{
			--m_iX;
		}
	}
	info.m_pTile->Death();
	std::vector<TileInfo>::iterator iter = m_vecAllStage[m_iCurLevel].AllTile.end();
	m_vecAllStage[m_iCurLevel].AllTile.erase(iter -1);
	m_iCurDegree -= static_cast<int>(info.m_pTile->m_fData.z);
}