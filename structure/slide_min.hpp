// https://github.com/kabipoyo/library_AC/blob/master/structure/slide_min.hpp
// 各長さkの窓の最小値。添字は0-indexed、1 <= k <= N。
#pragma once
#include "base.hpp"
template< typename T > vector<T> slide_min(const vector<T> &v, int k) {
	// 最小値に単位元を仮定しないため、空ウィンドウは許可しない。
	assert(1 <= k && k <= v.size());
	deque<int> q;
	vector<T> ret;
	rep(i, v.size()) {
		while (!q.empty() && v[q.back()] >= v[i]) {
			q.pop_back();
		}
		q.push_back(i);
		if (i-k+1 >= 0) {
			ret.emplace_back(v[q.front()]);
			if (q.front() == i-k+1) q.pop_front();
		}
	}
	return ret;
}
