#pragma once

#include <string>

namespace QtEngine
{
	class Alarm
	{
	public:
		Alarm();
		~Alarm();

		std::string Trace;
		std::string Debug;
		std::string Info;
		std::string Warning;
		std::string Error;
		std::string Fatal;
	};
}