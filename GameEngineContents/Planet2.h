#pragma once

// Ό³Έν :
class Planet2
{
public:
	// constrcuter destructer
	Planet2();
	~Planet2();

	// delete Function
	Planet2(const Planet2& _Other) = delete;
	Planet2(Planet2&& _Other) noexcept = delete;
	Planet2& operator=(const Planet2& _Other) = delete;
	Planet2& operator=(Planet2&& _Other) noexcept = delete;

protected:

private:

};

