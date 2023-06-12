#include "PrecompileHeader.h"
#include "Portal.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Portal::Portal() 
{
}

Portal::~Portal() 
{
}

void Portal::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::MAP);
	pRender->SetTexture("tiles_portal_circle_new_inner_Sprite.png");
	pRender->GetTransform()->SetLocalScale({ 64.f,64.f });
}

void Portal::Update(float _DeltaTime)
{
	if (m_Ptr !=nullptr)
	{
		m_Ptr();
		m_Ptr = nullptr;
	}
}

