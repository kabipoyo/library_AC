// https://github.com/kabipoyo/library_AC/blob/master/graph/lowlink.hpp
#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
// アルゴリズム参考: アルゴリズムロジック https://algo-logic.info/bridge-lowlink/
// 辺IDで多重辺を扱う反復DFSとして実装し直したもの。
namespace cp_lowlink {
struct Result {
	std::vector<int> articulation_points, bridge_ids, ord, low;
};
// 無向辺{u,v}を入力順の辺IDとして扱う。0-indexed。入力非破壊、O(V+E)。
// 非連結・多重辺・自己ループ可。出力は頂点番号/辺IDの昇順。再帰なし。
inline Result analyze(int n, const std::vector<std::pair<int,int>>& edges) {
	assert(n>=0);
	std::vector<std::vector<std::pair<int,int>>> adj(n);
	for (int id=0; id<(int)edges.size(); ++id) {
		auto [u,v]=edges[id]; assert(0<=u && u<n && 0<=v && v<n);
		adj[u].push_back({v,id}); adj[v].push_back({u,id});
	}
	Result result{{},{},std::vector<int>(n,-1),std::vector<int>(n)};
	std::vector<int> parent(n,-1), parent_edge(n,-1), children(n), position(n), stack;
	std::vector<bool> articulation(n), bridge(edges.size());
	int timer=0;
	for (int root=0; root<n; ++root) if (result.ord[root]==-1) {
		result.ord[root]=result.low[root]=timer++;
		stack.push_back(root);
		while (!stack.empty()) {
			int v=stack.back();
			if (position[v]<(int)adj[v].size()) {
				auto [to,id]=adj[v][position[v]++];
				if (id==parent_edge[v]) continue;
				if (result.ord[to]==-1) {
					parent[to]=v; parent_edge[to]=id; ++children[v];
					result.ord[to]=result.low[to]=timer++;
					stack.push_back(to);
				} else result.low[v]=std::min(result.low[v],result.ord[to]);
			} else {
				stack.pop_back(); int p=parent[v];
				if (p==-1) articulation[v]=children[v]>1;
				else {
					result.low[p]=std::min(result.low[p],result.low[v]);
					if (result.ord[p]<result.low[v]) bridge[parent_edge[v]]=true;
					if (parent[p]!=-1 && result.ord[p]<=result.low[v]) articulation[p]=true;
				}
			}
		}
	}
	for (int v=0; v<n; ++v) if (articulation[v]) result.articulation_points.push_back(v);
	for (int id=0; id<(int)edges.size(); ++id) if (bridge[id]) result.bridge_ids.push_back(id);
	return result;
}
}
