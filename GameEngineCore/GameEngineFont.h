#pragma once
#include "GameEngineResource.h"

#include "ThirdParty/FW1Font/Inc/FW1FontWrapper.h"

#pragma comment(lib, "FW1FontWrapper.lib")

// 설명 :
class GameEngineFont : public GameEngineResource<GameEngineFont>
{
	friend class FontFactoryCreator;
	static IFW1Factory* Factory;

public:
	// constrcuter destructer
	GameEngineFont();
	~GameEngineFont();

	// delete Function
	GameEngineFont(const GameEngineFont& _Other) = delete;
	GameEngineFont(GameEngineFont&& _Other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _Other) = delete;
	GameEngineFont& operator=(GameEngineFont&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineFont> Load(const std::string_view& _FontName)
	{
		std::shared_ptr<GameEngineFont> Res = GameEngineFont::Create(_FontName);
		Res->LoadFont(_FontName);
		return Res;
	}

	static void	FontInstall(const std::string_view& _Path)
	{
		std::string Path = _Path.data();
		// 폰트 설치

		if (0 == AddFontResource(GameEngineString::AnsiToUniCode(Path).c_str()) )
		{
			// 폰트 설치 실패
			MsgAssert("font 설치 실패");
		}
		
		if (S_OK != SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, 0, 0))
		{
			MsgAssert("font 적용 실패");
		}
		
		FontRemove(_Path);
	}

	static void	FontRemove(const std::string_view& _Path)
	{
		std::string Path = _Path.data();

		if (0 == RemoveFontResource(GameEngineString::AnsiToUniCode(Path).c_str()))
		{
			// 폰트 제거 실패
			MsgAssert("font 제거 실패");
		}
	}

	void FontDraw(const std::string_view& _Text, const float4& _Pos, float _FontScale, const float4& _Color, FW1_TEXT_FLAG _FwTextPlag);

protected:

private:
	IFW1FontWrapper* Font;
	void LoadFont(const std::string_view& _Path);
};

