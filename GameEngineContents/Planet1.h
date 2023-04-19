#pragma once

// Ό³Έν :
class Planet1
{
public:
	// constrcuter destructer
	Planet1();
	~Planet1();

	// delete Function
	Planet1(const Planet1& _Other) = delete;
	Planet1(Planet1&& _Other) noexcept = delete;
	Planet1& operator=(const Planet1& _Other) = delete;
	Planet1& operator=(Planet1&& _Other) noexcept = delete;

protected:

private:

};

