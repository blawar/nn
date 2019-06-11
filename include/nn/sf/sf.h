#pragma once

#include <memory>

namespace nn::sf
{
	template<class T>
	using SharedPointer = std::shared_ptr<T>;
}