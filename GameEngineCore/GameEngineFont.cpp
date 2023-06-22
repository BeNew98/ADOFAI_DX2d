#include "PrecompileHeader.h"
#include "GameEngineFont.h"


IFW1Factory* GameEngineFont::Factory = nullptr;

class FontFactoryCreator
{
public:
	FontFactoryCreator()
	{
		FW1CreateFactory(FW1_VERSION, &GameEngineFont::Factory);
	}

	~FontFactoryCreator()
	{
		if (nullptr != GameEngineFont::Factory)
		{
			// �ٽ� ����Ҷ� ����ִٴ°��� �˷��ֱ� ���ؼ�
			// ���α׷��� ����ɶ� �Ǵ°�.
			GameEngineFont::Factory->Release();
			GameEngineFont::Factory = nullptr;
		}
	}
};

FontFactoryCreator InitFont;

GameEngineFont::GameEngineFont()
{
}

GameEngineFont::~GameEngineFont()
{
	if (nullptr != Font)
	{
		Font->Release();
		Font = nullptr;
	}

}

void GameEngineFont::LoadFont(const std::string_view& _Path)
{
	std::wstring WPath = GameEngineString::AnsiToUniCode(_Path.data());

	D3D11_BLEND_DESC blendDesc = { 0, };
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	for (int i = 0; i < 4; ++i) {
		//blendDesc.RenderTarget[i].BlendEnable = TRUE;
		//blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
		//blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		//blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		//blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		//blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
		//blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		//blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		blendDesc.RenderTarget[i].BlendEnable = true;
		blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;

	}


	if (S_OK != GameEngineFont::Factory->CreateFontWrapper(GameEngineDevice::GetDevice(), WPath.c_str(), blendDesc, &Font))
	{
		MsgAssert("��Ʈ ���� ����");
		return;
	}
}


void GameEngineFont::FontInstall(const std::string_view& _Path)
{
	std::string Path = _Path.data();
	// ��Ʈ ��ġ

	if (0 == AddFontResource(GameEngineString::AnsiToUniCode(Path).c_str()))
	{
		// ��Ʈ ��ġ ����
		MsgAssert("font ��ġ ����");
	}

	if (S_OK != SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, 0, 0))
	{
		MsgAssert("font ���� ����");
	}
	//HDC dc = GetDC(NULL);
	//EnumFontFamilies(dc,NULL,static_cast<FONTENUMPROC>ENUMFONTFAMILESPROC)

	FontRemove(_Path);
}

void GameEngineFont::FontRemove(const std::string_view& _Path)
{
	std::string Path = _Path.data();

	if (0 == RemoveFontResource(GameEngineString::AnsiToUniCode(Path).c_str()))
	{
		// ��Ʈ ���� ����
		MsgAssert("font ���� ����");
	}
}

void GameEngineFont::FontDraw(const std::string_view& _Text, const float4& _Pos, float _FontScale, const float4& _Color, FW1_TEXT_FLAG _FwTextFlag)
{
	std::wstring Text = GameEngineString::AnsiToUniCode(_Text);

	float4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };

	Font->DrawString(GameEngineDevice::GetContext(), Text.c_str(), _FontScale, _Pos.x, _Pos.y, _Color.ColorToUint(), _FwTextFlag);
}