// https://github.com/kabipoyo/library_AC/blob/master/acl/segtree_search.hpp
// 非負の要素の区間和に対する境界探索。0-indexed、区間[l,r)。
// 参考: https://atcoder.github.io/ac-library/production/document_ja/segtree.html
#pragma once
#include "segtree.hpp"
#include <cassert>

namespace acl_segtree_search {
using Seg = acl_segtree_sum::Seg;
// 和がlimit以下となる最大の右端。全要素が非負、limit>=0。
inline int max_right_sum_le(const Seg& seg, int l, long long limit) {
	assert(limit >= 0);
	return seg.max_right(l, [limit](long long sum) { return sum <= limit; });
}
// 和がlimit以下となる最小の左端。全要素が非負、limit>=0。
inline int min_left_sum_le(const Seg& seg, int r, long long limit) {
	assert(limit >= 0);
	return seg.min_left(r, [limit](long long sum) { return sum <= limit; });
}
// sum[l,p+1)>=targetとなる最初の添字p。なければN。target>0。
inline int first_prefix_sum_ge(const Seg& seg, int l, long long target) {
	assert(target > 0);
	return seg.max_right(l, [target](long long sum) { return sum < target; });
}
}
