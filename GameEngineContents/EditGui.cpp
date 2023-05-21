#include "PrecompileHeader.h"
#include "EditGui.h"
#include "Tiles.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

EditGui::EditGui() 
{
}

EditGui::~EditGui() 
{
}

void EditGui::Start()
{
	AllStage.resize(LevelSize);
}

void EditGui::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{
	if (ImGui::Button("Start"))
	{
	}
	
}

void EditGui::CreateTile(TileDeg _Deg)
{
		switch (_Deg)
		{
		case TileDeg::Start:
		{

			std::shared_ptr<GameEngineSpriteRenderer> m_Start = CreateComponent<GameEngineSpriteRenderer>();
			m_Start->SetScaleToTexture("tiles_editor_basic_12.png");
			m_Start->SetFlipX();
			break;
		}
		case TileDeg::Deg90:
		{
			std::shared_ptr<GameEngineSpriteRenderer>m_90 = CreateComponent<GameEngineSpriteRenderer>();
			m_90->SetScaleToTexture("tiles_editor_basic_0.png");
			break;
		}
		case TileDeg::Deg180:
		{
			std::shared_ptr<GameEngineSpriteRenderer>m_180 = CreateComponent<GameEngineSpriteRenderer>();
			m_180->SetScaleToTexture("tiles_editor_basic_4.png");
			break;
		}
		case TileDeg::Deg270:
		{
			std::shared_ptr<GameEngineSpriteRenderer>m_270 = CreateComponent<GameEngineSpriteRenderer>();
			m_270->SetScaleToTexture("tiles_editor_basic_0.png");
			m_270->SetFlipY();
			break;
		}
		case TileDeg::End:
		{
			std::shared_ptr<GameEngineSpriteRenderer> m_End = CreateComponent<GameEngineSpriteRenderer>();
			m_End->SetScaleToTexture("tiles_editor_basic_12.png");
			m_End->SetFlipX();
			break;
		}
		default:
			break;
		}
	
}
