// https://github.com/kabipoyo/library_AC/blob/master/structure/range_map.hpp
/**
 * @brief 区間を管理する
 * @details
 *
// コンストラクタ．隣接区間をマージする
SegmentMap map(true);

// iを含む区間[l, r)のiteratorを返す。区間が無ければmap.end()。
// it->first, it->second でアクセス
auto it = map.get(i);

// 区間[l, r)を挿入する。空区間は何もしない。
map.insert(l, r);

// 全区間で[l, r)に重なる部分を全て消す
map.remove(l, r);

// iとjが同じ区間に属しているかのbool値を返す
bool f = map.same(i, j);
 */
#pragma once
#include "base.hpp"
class SegmentMap : public map<lint, lint> {
private:
	bool flagToMergeAdjacentSegment;
public:
	// trueなら [l,c) と [c,r) もマージする。
	SegmentMap(bool flagToMergeAdjacentSegment) :
		flagToMergeAdjacentSegment(flagToMergeAdjacentSegment) {}
	// __exist -> iterator pair(l, r) (contain p)
	// noexist -> map.end()
	auto get(lint p) const {
		auto it = upper_bound(p);
		if (it == begin() || (--it)->second <= p) return end();
		return it;
	}
	// insert segment [l, r)
	void insert(lint l, lint r) {
		assert(l <= r);
		if (l == r) return;
		auto it = lower_bound(l);
		if (it != begin()) {
			auto previous = prev(it);
			if (flagToMergeAdjacentSegment ? previous->second >= l : previous->second > l) it = previous;
		}
		while (it != end() && (flagToMergeAdjacentSegment ? it->first <= r : it->first < r)) {
			l = min(l, it->first);
			r = max(r, it->second);
			it = erase(it);
		}
		(*this)[l] = r;
	}
	// remove segment [l, r)
	void remove(lint l, lint r) {
		assert(l <= r);
		if (l == r) return;
		auto it = lower_bound(l);
		if (it != begin() && prev(it)->second > l) --it;
		while (it != end() && it->first < r) {
			lint left = it->first, right = it->second;
			it = erase(it);
			if (left < l) (*this)[left] = l;
			if (r < right) { (*this)[r] = right; break; }
		}
	}
	// Is p and q in same segment?
	bool same(lint p, lint q) const {
		const auto&& it = get(p);
		return it != end() && it->first <= q && q < it->second;
	}
};
