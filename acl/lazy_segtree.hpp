// https://github.com/kabipoyo/library_AC/blob/master/acl/lazy_segtree.hpp
// ACLの作用設定例。必要なnamespaceを選ぶ。0-indexed、区間[l,r)。
// composition(f,g)はgを先、fを後に適用。整数の値・和・作用はlong long内。
// Seg(n)はe()で埋まる。実要素はmake_data(values)またはzeros(n)で構築する。
// 参考: https://atcoder.github.io/ac-library/production/document_ja/lazysegtree.html
#pragma once
#include <atcoder/lazysegtree>
#include <atcoder/modint>
#include <algorithm>
#include <cassert>
#include <limits>
#include <optional>
#include <vector>

namespace acl_lazy_add_sum {
// Seg seg(make_data(values)); または Seg seg(zeros(n)); Seg(n)は実要素0配列ではない。
// composition(f,g)はgを先、fを後に適用。区間[l,r)、0-indexed。
struct S { long long sum; int len; };
using F = long long;
inline S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
inline S e() { return {0, 0}; }
inline S mapping(F f, S x) { return {x.sum + f * x.len, x.len}; }
inline F composition(F f, F g) { return f + g; }
inline F id() { return 0; }
using Seg = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
inline std::vector<S> make_data(const std::vector<long long>& a) {
	std::vector<S> v; v.reserve(a.size());
	for (auto x : a) v.push_back({x, 1});
	return v;
}
inline std::vector<S> zeros(int n) { assert(n >= 0); return std::vector<S>(n, {0, 1}); }
// Seg seg(zeros(n)); seg.apply(l,r,delta); auto sum = seg.prod(l,r).sum;
}

namespace acl_lazy_add_min {
// Seg seg(make_data(values)); または Seg seg(zeros(n)); Seg(n)は実要素0配列ではない。
// composition(f,g)はgを先、fを後に適用。区間[l,r)、0-indexed。
struct S { long long value; int len; };
using F = long long;
inline S op(S a, S b) {
	if (!a.len) return b;
	if (!b.len) return a;
	return {std::min(a.value, b.value), a.len + b.len};
}
inline S e() { return {std::numeric_limits<long long>::max(), 0}; }
inline S mapping(F f, S x) { if (x.len) x.value += f; return x; }
inline F composition(F f, F g) { return f + g; }
inline F id() { return 0; }
using Seg = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
inline std::vector<S> make_data(const std::vector<long long>& a) {
	std::vector<S> v; v.reserve(a.size());
	for (auto x : a) v.push_back({x, 1});
	return v;
}
inline std::vector<S> zeros(int n) { assert(n >= 0); return std::vector<S>(n, {0, 1}); }
// Seg seg(make_data(values)); seg.apply(l,r,delta); auto minimum = seg.prod(l,r).value;
}

namespace acl_lazy_add_max {
// Seg seg(make_data(values)); または Seg seg(zeros(n)); Seg(n)は実要素0配列ではない。
// composition(f,g)はgを先、fを後に適用。区間[l,r)、0-indexed。
struct S { long long value; int len; };
using F = long long;
inline S op(S a, S b) {
	if (!a.len) return b;
	if (!b.len) return a;
	return {std::max(a.value, b.value), a.len + b.len};
}
inline S e() { return {std::numeric_limits<long long>::lowest(), 0}; }
inline S mapping(F f, S x) { if (x.len) x.value += f; return x; }
inline F composition(F f, F g) { return f + g; }
inline F id() { return 0; }
using Seg = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
inline std::vector<S> make_data(const std::vector<long long>& a) {
	std::vector<S> v; v.reserve(a.size());
	for (auto x : a) v.push_back({x, 1});
	return v;
}
inline std::vector<S> zeros(int n) { assert(n >= 0); return std::vector<S>(n, {0, 1}); }
// Seg seg(zeros(n)); seg.apply(l,r,delta); auto maximum = seg.prod(l,r).value;
}

namespace acl_lazy_assign_sum {
// Seg seg(make_data(values)); または Seg seg(zeros(n)); Seg(n)は実要素0配列ではない。
// composition(f,g)はgを先、fを後に適用。区間[l,r)、0-indexed。
struct S { long long sum; int len; };
using F = std::optional<long long>;
inline S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
inline S e() { return {0, 0}; }
inline S mapping(F f, S x) { return f ? S{*f * x.len, x.len} : x; }
inline F composition(F f, F g) { return f ? f : g; }
inline F id() { return std::nullopt; }
using Seg = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
inline std::vector<S> make_data(const std::vector<long long>& a) {
	std::vector<S> v; v.reserve(a.size());
	for (auto x : a) v.push_back({x, 1});
	return v;
}
inline std::vector<S> zeros(int n) { assert(n >= 0); return std::vector<S>(n, {0, 1}); }
// seg.apply(l,r,F{value}); 0や負数も代入可。nulloptは「何もしない」。
}

namespace acl_lazy_assign_min {
// Seg seg(make_data(values)); または Seg seg(zeros(n)); Seg(n)は実要素0配列ではない。
// composition(f,g)はgを先、fを後に適用。区間[l,r)、0-indexed。
struct S { long long value; int len; };
using F = std::optional<long long>;
inline S op(S a, S b) {
	if (!a.len) return b;
	if (!b.len) return a;
	return {std::min(a.value, b.value), a.len + b.len};
}
inline S e() { return {std::numeric_limits<long long>::max(), 0}; }
inline S mapping(F f, S x) { if (f && x.len) x.value = *f; return x; }
inline F composition(F f, F g) { return f ? f : g; }
inline F id() { return std::nullopt; }
using Seg = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
inline std::vector<S> make_data(const std::vector<long long>& a) {
	std::vector<S> v; v.reserve(a.size());
	for (auto x : a) v.push_back({x, 1});
	return v;
}
inline std::vector<S> zeros(int n) { assert(n >= 0); return std::vector<S>(n, {0, 1}); }
// seg.apply(l,r,F{value}); auto minimum = seg.prod(l,r).value;
}

namespace acl_lazy_affine_sum {
// Seg seg(make_data(values)); または Seg seg(zeros(n)); Seg(n)は実要素0配列ではない。
// composition(f,g)はgを先、fを後に適用。区間[l,r)、0-indexed。
using Mint = atcoder::modint998244353;
struct S { Mint sum; int len; };
struct F { Mint a, b; };
inline S op(S x, S y) { return {x.sum + y.sum, x.len + y.len}; }
inline S e() { return {0, 0}; }
inline S mapping(F f, S x) { return {f.a * x.sum + f.b * x.len, x.len}; }
inline F composition(F f, F g) { return {f.a * g.a, f.a * g.b + f.b}; }
inline F id() { return {1, 0}; }
using Seg = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
inline std::vector<S> make_data(const std::vector<Mint>& a) {
	std::vector<S> v; v.reserve(a.size());
	for (auto x : a) v.push_back({x, 1});
	return v;
}
inline std::vector<S> zeros(int n) { assert(n >= 0); return std::vector<S>(n, {0, 1}); }
// seg.apply(l,r,F{a,b}); 各値xをa*x+bへ変更。法はMintの別名で選ぶ。
}

namespace acl_lazy_assign_add_sum {
// Seg seg(make_data(values)); または Seg seg(zeros(n)); Seg(n)は実要素0配列ではない。
// composition(f,g)はgを先、fを後に適用。区間[l,r)、0-indexed。
struct S { long long sum; int len; };
struct F { std::optional<long long> assign; long long add; };
inline S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
inline S e() { return {0, 0}; }
inline S mapping(F f, S x) {
	if (f.assign) x.sum = *f.assign * x.len;
	x.sum += f.add * x.len;
	return x;
}
inline F composition(F f, F g) {
	if (f.assign) return f;
	g.add += f.add;
	return g;
}
inline F id() { return {std::nullopt, 0}; }
using Seg = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
inline std::vector<S> make_data(const std::vector<long long>& a) {
	std::vector<S> v; v.reserve(a.size());
	for (auto x : a) v.push_back({x, 1});
	return v;
}
inline std::vector<S> zeros(int n) { assert(n >= 0); return std::vector<S>(n, {0, 1}); }
// 加算: F{nullopt,delta}、代入: F{value,0}。代入後にaddを加える。
}
