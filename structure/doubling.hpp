/**
 * @brief 文字列の一致判定を高速に行う
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
 * build	O(NlogN)
 * query	O(logN)
 */
#pragma once
#include "base.hpp"

struct Doubling {
	const int LOG;
	vector< vector< int > > table;

	Doubling(int sz, int64_t lim_t) : LOG(64 - __builtin_clzll(lim_t))
	{
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
		for(int i = LOG - 1; i >= 0; i--) {
			if((t >> i) & 1) k = table[i][k];
		}
		return k;
	}
};
