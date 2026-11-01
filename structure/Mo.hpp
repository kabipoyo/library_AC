// https://github.com/kabipoyo/library_AC/blob/master/structure/Mo.hpp
// 区間[l,r)のオフラインクエリ用比較。ブロック幅Mは1以上。
// 参考: https://ei1333.hateblo.jp/entry/2017/09/11/211011
#pragma once
#include "base.hpp"
int M = 1;  // 分割する区間サイズ。必ず1以上。
bool mo_tuple_less(const tuple<lint, lint, lint>& lhs, const tuple<lint, lint, lint>& rhs) {
	lint a, b, c, x, y, z;
	tie(a, b, c) = lhs;
	tie(x, y, z) = rhs;
	if (a / M < x / M) return true;
	if (a / M == x / M && b < y) return true;
	return false;
}

bool mo_pair_less(const pair<int, int>& lhs, const pair<int, int>& rhs) {
	if (lhs.first / M < rhs.first / M) return true;
	if (lhs.first / M == rhs.first / M && lhs.second < rhs.second) return true;
	return false;
}
