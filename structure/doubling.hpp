/**
 * @brief 各状態から指定回数だけ遷移した先を求める
 *
 * @tparam sz Nを入れる
 * @tparam lim_t 最大何状態先まで計算するかを入れる
 * @author ei1333
 * @details https://ei1333.github.io/luzhiled/snippets/memo/doubling.html
 *
 * 使い方：
 * Doubling doubling(sz, lim_t);
 *
 * query(k, t): k の t 状態先を求める
 *
 * 計算量：
 * build	O(N log(lim_t+1))
 * query	O(log(lim_t+1))
 */
#pragma once
#include "base.hpp"

struct Doubling {
	const int LOG;
	vector< vector< int > > table;

	Doubling(int sz, int64_t lim_t) : LOG(lim_t == 0 ? 1 : 64 - __builtin_clzll(lim_t))
	{
		assert(lim_t >= 0);
		table.assign(LOG, vector< int >(sz, -1));
	}

	void set_next(int k, int x)
	{
		table[0][k] = x;
	}

	void build()
	{
		for(int k = 0; k + 1 < LOG; k++) {
			for(int i = 0; i < table[k].size(); i++) {
				if(table[k][i] == -1) table[k + 1][i] = -1;
				else table[k + 1][i] = table[k][table[k][i]];
			}
		}
	}

	int query(int k, int64_t t)
	{
		assert(t >= 0 && (LOG == 64 || (uint64_t(t) >> LOG) == 0));
		for(int i = LOG - 1; i >= 0 && k != -1; i--) {
			if((t >> i) & 1) k = table[i][k];
		}
		return k;
	}
};
