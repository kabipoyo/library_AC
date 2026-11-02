// https://github.com/kabipoyo/library_AC/blob/master/sample/predicate_binary_search.hpp
#pragma once
#include <cassert>
#include <numeric>
#include <type_traits>

namespace cp_binary_search {
// C++20以上。okは真、ngは偽の既知端点（どちらが大きくてもよい）。
// 区間内で判定が単調であること。端点の判定は呼ばず、仮想端点も指定可。
// 隣接するまで縮め、真側の境界を返す。解なしは利用側で仮想端点から判定。
template<class Int, class Predicate> Int boundary(Int ok, Int ng, Predicate pred) {
	static_assert(std::is_integral_v<Int> && !std::is_same_v<Int, bool>);
	assert(ok != ng);
	while (true) {
		Int mid = std::midpoint(ok, ng);
		if (mid == ok) return ok;
		if (pred(mid)) ok = mid;
		else ng = mid;
	}
}
}
