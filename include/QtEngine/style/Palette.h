#pragma once

#include <string>

namespace QtEngine
{

	class Palette
	{
	public:
		Palette();
		~Palette();


		std::string Light;
		std::string Main;
		std::string Dark;
		std::string Darker;
	};
}