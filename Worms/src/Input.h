#pragma once

class Input
{
public:
	Input( const Input& ) = delete;
	Input( Input&& ) = delete;

	static Input& Get()
	{
		static Input input{};
		return input;
	}

	float horizontal;
	float vertical;

	float camera_horizontal;
	float camera_vertical;


private:
	Input() = default;

};