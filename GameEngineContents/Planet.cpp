#include "PrecompileHeader.h"
#include "Planet.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "EditGui.h"

int Planet::m_iUseCount = 0;

Planet::Planet()
{
}

Planet::~Planet() 
{
}
 

void Planet::Start()
{
	if (m_iUseCount!=0)
	{
		std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>(OrderNum::PLANET);
		render->SetTexture("ballsprites_blue_sheet_grid_0_Sprite.png");
		render->GetTransform()->SetLocalScale({ 64.f, 64.f, 0.f });

		std::shared_ptr<GameEngineCollision> m_pCollision = CreateComponent<GameEngineCollision>(OrderNum::PLANET);
		m_pCollision->GetTransform()->SetLocalScale({ 64.f, 64.f, 0.f });
		m_iUseCount += render.use_count();

	}
	else
	{
		TransformData data = GetTransform()->GetTransDataRef();
		std::shared_ptr<GameEngineSpriteRenderer> prender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::PLANET);
		prender->SetTexture("ballsprites_red_sheet_grid_0_Sprite.png");
		prender->GetTransform()->SetLocalScale({ 64.f, 64.f, 0.f });
		m_bCenter = true;


		std::shared_ptr<GameEngineCollision> m_pCollision = CreateComponent<GameEngineCollision>(OrderNum::PLANET);
		m_pCollision->GetTransform()->SetLocalScale({ 64.f, 64.f, 0.f });


		std::shared_ptr<GameEngineSpriteRenderer> pEffectRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
		pEffectRender->SetScaleToTexture("bottomglow_E2.png");
		pEffectRender->SetOrder(static_cast<int>(OrderNum::EFFECT));
		pEffectRender->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());

		m_iUseCount += prender.use_count();

	}



}

void Planet::Update(float _DeltaTime)
{
	if (m_bCenter==true)
	{
		GetTransform()->AddLocalRotation({ 0.f,0.f,-180.f * _DeltaTime });
	}
}

