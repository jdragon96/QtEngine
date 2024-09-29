#pragma once
#include "QtEngine/mvvm/Property.h"


namespace QtEngine
{
	template<typename T>
	Property<T>::Property()
	{

	}

	template<typename T>
	Property<T>::~Property()
	{

	}

	template<typename T>
	void Property<T>::Update()
	{
		callback(value);
	}

	template<typename T>
	void Property<T>::SetCallback(std::function<void(T)> cb)
	{
		callback = cb;
	}
}
