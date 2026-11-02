// https://github.com/kabipoyo/library_AC/blob/master/acl/maxflow.hpp
#pragma once
#include <atcoder/maxflow>
#include <cassert>
#include <utility>
#include <vector>
// 参考: https://atcoder.github.io/ac-library/production/document_ja/maxflow.html
namespace acl_maxflow {
using Graph = atcoder::mf_graph<long long>;
// Graph g(n); int id=g.add_edge(u,v,capacity); auto f=g.flow(s,t);
// auto e=g.get_edge(id); e.flowは現在の流量。add_edgeは非負容量、s!=t。
// min_cut(s)で最小カットを得るには、流量上限なしで最大流まで流す。
// flowは残余状態を変更する。再呼出しの返値は追加で流れた量。
}

namespace acl_bipartite_matching {
struct Result { int size; std::vector<int> edge_indices; };
// 左右の頂点はそれぞれ0-indexed。返値は入力辺の添字で組を復元する。
inline Result solve(int left, int right, const std::vector<std::pair<int,int>>& edges) {
	assert(left>=0 && right>=0);
	int s=left+right, t=s+1;
	atcoder::mf_graph<int> g(t+1);
	for (int u=0; u<left; ++u) g.add_edge(s,u,1);
	for (int v=0; v<right; ++v) g.add_edge(left+v,t,1);
	std::vector<int> ids;
	for (auto [u,v]: edges) {
		assert(0<=u && u<left && 0<=v && v<right);
		ids.push_back(g.add_edge(u,left+v,1));
	}
	Result result{g.flow(s,t),{}};
	for (int i=0; i<(int)ids.size(); ++i) if (g.get_edge(ids[i]).flow) result.edge_indices.push_back(i);
	return result;
}
}

namespace acl_vertex_capacity {
// 頂点vをin(v)->out(v)へ分割し、その辺に頂点容量を設定する。
// 始点も含めて容量を課す場合はflow(in(s),out(t))。
// 始終点の容量を除外する場合はflow(out(s),in(t))（s!=t）。
struct Network {
	int n;
	atcoder::mf_graph<long long> graph;
	explicit Network(const std::vector<long long>& capacity)
		: n((int)capacity.size()), graph(2*n) {
		for (int v=0; v<n; ++v) { assert(capacity[v]>=0); graph.add_edge(in(v),out(v),capacity[v]); }
	}
	int in(int v) const { assert(0<=v && v<n); return 2*v; }
	int out(int v) const { assert(0<=v && v<n); return 2*v+1; }
	// 有向辺。無向辺は両方向に追加。返値の辺IDはgraph.get_edgeで参照可。
	int add_edge(int u, int v, long long capacity) { return graph.add_edge(out(u),in(v),capacity); }
};
}
