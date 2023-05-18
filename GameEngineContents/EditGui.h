#pragma once

// Ό³Έν :
class EditGui
{
public:
	// constrcuter destructer
	EditGui();
	~EditGui();

	// delete Function
	EditGui(const EditGui& _Other) = delete;
	EditGui(EditGui&& _Other) noexcept = delete;
	EditGui& operator=(const EditGui& _Other) = delete;
	EditGui& operator=(EditGui&& _Other) noexcept = delete;

protected:

private:

};

