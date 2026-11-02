// https://github.com/kabipoyo/library_AC/blob/master/graph/zero_one_bfs.hpp
#pragma once
#include <cassert>
#include <deque>
#include <limits>
#include <utility>
#include <vector>

namespace cp_zero_one_bfs {
inline constexpr long long unreachable = std::numeric_limits<long long>::max()/2;
// G[v]の辺は{行き先,重み}。頂点0-indexed、重みは0/1。到達不能はLINF相当。
// 空グラフには始点を指定できない。到達した頂点の辺を検査する。O(V+E)。
template<class Graph> std::vector<long long> shortest_paths(const Graph& g, int start) {
	int n = (int)g.size();
	assert(0 <= start && start < n);
	std::vector<long long> dist(n, unreachable);
	std::deque<std::pair<long long, int>> q;
	dist[start] = 0;
	q.push_front({0, start});
	while (!q.empty()) {
		auto [d, v] = q.front(); q.pop_front();
		if (dist[v] != d) continue;
		for (auto [to, cost] : g[v]) {
			assert(0 <= to && to < n && (cost == 0 || cost == 1));
			if (dist[to] <= d+cost) continue;
			dist[to] = d+cost;
			if (cost == 0) q.push_front({dist[to], (int)to});
			else q.push_back({dist[to], (int)to});
		}
	}
	return dist;
}
}
