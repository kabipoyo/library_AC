// https://github.com/kabipoyo/library_AC/blob/master/graph/functional_graph.hpp
#pragma once
#include <cassert>
#include <vector>
#include <type_traits>

namespace cp_functional_graph {
struct Result {
	std::vector<std::vector<int>> cycles;
	std::vector<int> cycle_id, distance_to_cycle, entry;
	std::vector<long long> reachable_count;
};
// next[v]は0-indexedの遷移先。全頂点の出次数が1。入力非破壊、O(N)、再帰なし。
// cycles[id]はnextの向き。cycle_idは木部分も含む到達先閉路のID。
// entryは最初に到達する閉路頂点、reachable_countは自身を含む異なる到達頂点数。
template<class Int> Result analyze(const std::vector<Int>& next) {
	static_assert(std::is_integral_v<Int>);
	int n=(int)next.size();
	std::vector<int> indegree(n), order;
	for (auto to:next) { assert(0<=to && to<n); ++indegree[to]; }
	for (int v=0; v<n; ++v) if (indegree[v]==0) order.push_back(v);
	for (int i=0; i<(int)order.size(); ++i) {
		int to=next[order[i]];
		if (--indegree[to]==0) order.push_back(to);
	}
	Result result{{},std::vector<int>(n,-1),std::vector<int>(n),std::vector<int>(n,-1),std::vector<long long>(n)};
	for (int v=0; v<n; ++v) if (indegree[v]>0 && result.cycle_id[v]==-1) {
		int id=(int)result.cycles.size(), u=v;
		std::vector<int> cycle;
		do {
			result.cycle_id[u]=id; result.entry[u]=u;
			cycle.push_back(u); u=next[u];
		} while (u!=v);
		for (int x:cycle) result.reachable_count[x]=(long long)cycle.size();
		result.cycles.push_back(cycle);
	}
	for (int i=(int)order.size()-1; i>=0; --i) {
		int v=order[i], to=next[v];
		result.cycle_id[v]=result.cycle_id[to];
		result.entry[v]=result.entry[to];
		result.distance_to_cycle[v]=result.distance_to_cycle[to]+1;
		result.reachable_count[v]=result.reachable_count[to]+1;
	}
	return result;
}
}
