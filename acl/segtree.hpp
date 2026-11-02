// https://github.com/kabipoyo/library_AC/blob/master/acl/segtree.hpp
// ACLの設定例。必要なnamespaceを選んでコピー。0-indexed、区間[l,r)。
// 参考: https://atcoder.github.io/ac-library/production/document_ja/segtree.html
#pragma once
#include <atcoder/segtree>
#include <algorithm>
#include <limits>
#include <numeric>

namespace acl_segtree_sum {
using S = long long;
inline S op(S a, S b) { return a + b; }
inline S e() { return 0; }
using Seg = atcoder::segtree<S, op, e>;
// Seg seg(values); seg.set(p,x); auto sum = seg.prod(l,r);
}

namespace acl_segtree_min {
using S = long long;
inline S op(S a, S b) { return std::min(a, b); }
inline S e() { return std::numeric_limits<S>::max(); }
using Seg = atcoder::segtree<S, op, e>;
// Seg seg(values); auto minimum = seg.prod(l,r); 空区間はe()。
}

namespace acl_segtree_max {
using S = long long;
inline S op(S a, S b) { return std::max(a, b); }
inline S e() { return std::numeric_limits<S>::lowest(); }
using Seg = atcoder::segtree<S, op, e>;
// Seg seg(values); auto maximum = seg.prod(l,r); 空区間はe()。
}

namespace acl_segtree_gcd {
using S = long long;
inline S op(S a, S b) { return std::gcd(a, b); }
inline S e() { return 0; }
using Seg = atcoder::segtree<S, op, e>;
// 非負整数。Seg seg(values); auto gcd = seg.prod(l,r);
}

namespace acl_segtree_xor {
using S = unsigned long long;
inline S op(S a, S b) { return a ^ b; }
inline S e() { return 0; }
using Seg = atcoder::segtree<S, op, e>;
// vector<unsigned long long>から構築。auto value = seg.prod(l,r);
}

namespace acl_segtree_argmin {
struct S { long long value; int index; };
inline S op(S a, S b) {
	if (a.index == -1) return b;
	if (b.index == -1) return a;
	if (a.value != b.value) return a.value < b.value ? a : b;
	return a.index < b.index ? a : b;
}
inline S e() { return {0, -1}; }
using Seg = atcoder::segtree<S, op, e>;
// 葉は{値,元の添字}。同値なら小さい添字。空区間はindex=-1。
}
