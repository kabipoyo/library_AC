/**
 * @brief スライド最小値：長さNの数列 a[i] に対して、長さkの連続部分列 {a[i], a[i + 1],... , a[i + k - 1]} の最小値 b[i] を 0 <= i <= n-k を満たすすべての i についてO(N)で計算
 *
 * @tparam T 配列の型
 * @param v 配列
 * @param k 長さ
 * @return vector<T> 最小値のリスト
 * @details
 * 使い方：
 * vi m = slide_min(v, K);
 *
 * 計算量：
 * O(N)
 */
#pragma once
#include "base.hpp"
template< typename T > vector<T> slide_min(const vector<T> &v, int k) {
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
