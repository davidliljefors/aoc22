#pragma once

#include <algorithm>

namespace ops
{

constexpr inline auto max = []<typename T>( T left, T right ) -> T
{
	return std::max<T>( left, right );
};

constexpr inline auto min = []<typename T>( T left, T right ) -> T
{
	return std::min<T>( left, right );
};

constexpr inline auto plus = []<typename T>( T left, T right ) -> T
{
	return left + right;
};

constexpr inline auto minus = []<typename T>( T left, T right ) -> T
{
	return left - right;
};

constexpr inline auto multiplies = []<typename T>( T left, T right )-> T
{
	return left * right;
};

constexpr inline auto negate = []<typename T>( T value ) -> T
{
	return -value;
};

}