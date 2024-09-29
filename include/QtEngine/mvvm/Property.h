#pragma once

#include <functional>

namespace QtEngine
{
	template<typename T>
	class Property
	{
	public:
		Property();
		~Property();
		void Update();
		void SetCallback(std::function<void(T)>);

		virtual void operator=(T newValue)
		{
			value = newValue;
			callback(value);
		}

		T value;
		std::function<void(T)> callback = [](T v) {};
	};
}  // namespace QtEngine

#include "QtEngine/mvvm/Property.tpp"