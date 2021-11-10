#pragma once
// @SFINAE: Substitution failure is not an error

#include <utility>
#include <iomanip>


template<typename T1, typename T2>
auto Plus(T1&& t1, T2&& t2) ->
decltype(std::forward<T1>(t1) + std::forward<T2>(t2)) {
	return std::forward<T1>(t1) + std::forward<T2>(t2);
}