// https://github.com/kabipoyo/library_AC/blob/master/math/integer_division.hpp
#pragma once
#include <cassert>
#include <limits>
#include <type_traits>

namespace cp_integer_division {
// 符号付き整数の数学的なfloor/ceil。浮動小数点・加算による丸めを使わない。
// b!=0。最小値/-1は答えが型に収まらないため禁止。引数は同じ型。
template<class Int> Int floor_div(Int a, Int b) {
	static_assert(std::is_integral_v<Int> && std::is_signed_v<Int>);
	assert(b!=0 && !(a==std::numeric_limits<Int>::min() && b==Int(-1)));
	Int q=a/b, r=a%b;
	if (r!=0 && ((r<0)!=(b<0))) --q;
	return q;
}
template<class Int> Int ceil_div(Int a, Int b) {
	static_assert(std::is_integral_v<Int> && std::is_signed_v<Int>);
	assert(b!=0 && !(a==std::numeric_limits<Int>::min() && b==Int(-1)));
	Int q=a/b, r=a%b;
	if (r!=0 && ((r<0)==(b<0))) ++q;
	return q;
}
}
