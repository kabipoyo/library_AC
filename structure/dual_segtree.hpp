// https://github.com/kabipoyo/library_AC/blob/master/structure/dual_segtree.hpp
/**
 * @brief 詳細に記載の問題用に改造された版、セグ木を改造して使いたいときに
 * @param N セグ木のサイズ
 * @return セグ木クラス
 * @details 例題：https://atcoder.jp/contests/abc342/tasks/abc342_g
 *
 * 使い方：
dual_segtree seg(N);
 */
#pragma once
#include "base.hpp"
class dual_segtree{
public:
	vector<set<pair<lint, lint>>> data;
	lint n;

	dual_segtree(lint _n){
		assert(_n >= 0);
		n=_n;
		data.resize(2*n);
	}

	void ins(lint p, lint time, lint val){
		if (time < 0) data[p].erase({val, -time});
		else data[p].insert({val, time});
	}

	void apply(lint l, lint r, lint time, lint val){
		assert(0 <= l && l <= r && r <= n);
		assert(time != numeric_limits<lint>::min());
		for (l += n, r += n; l != r; l = (l+1)>>1, r >>= 1){
			if (l&1) ins(l, time, val);
			if (r&1) ins(r-1, time, val);
		}
	}

	// 候補がないときnullopt。負の値も格納できる。
	optional<lint> get(lint i){
		assert(0 <= i && i < n);
		optional<lint> ans;
		for (i += n; i; i >>= 1){
			auto it = data[i].end();
			if (data[i].size()) {
				lint value = (--it)->first;
				if (!ans || *ans < value) ans = value;
			}
		}
		return ans;
	}
};
