// https://github.com/kabipoyo/library_AC/blob/master/structure/range_map.hpp
// 整数の半開区間[l,r)を管理。空区間の更新は何もしない。
// getは不在時end()。コンストラクタのtrueは隣接区間も結合。
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
