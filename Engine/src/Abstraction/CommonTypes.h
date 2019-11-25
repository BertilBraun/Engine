#pragma once

#include <memory>
#include <vector>
#include <string>
#include <stack>


namespace Engine
{
	template <typename T>
	using Vector = std::vector<T>;

	template <typename T>
	using Stack = std::stack<T>;

	using String = std::string;

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using Own = std::unique_ptr<T>;

	template <typename T, typename... Args>
	Ref<T> MakeRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename... Args>
	Own<T> MakeOwn(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


}