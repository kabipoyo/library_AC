// https://github.com/kabipoyo/library_AC/blob/master/graph/rerooting.hpp
#pragma once
#include <cassert>
#include <vector>
// アルゴリズム参考: アルゴリズムロジック https://algo-logic.info/tree-dp/
// 反復走査・非可換な結合順・頂点/辺の遷移を明示する構成として新規実装。
namespace cp_rerooting {
class Rerooting {
	struct Edge { int to, reverse, id; };
	int n_, edge_count_=0;
	std::vector<std::vector<Edge>> graph;
public:
	explicit Rerooting(int n) : n_(n) { assert(n>=0); graph.resize(n); }
	// 無向辺を1回だけ追加。返す辺IDを使ってliftから辺重み等を参照できる。
	int add_edge(int u, int v) {
		assert(0<=u && u<n_ && 0<=v && v<n_ && u!=v);
		int id=edge_count_++, a=(int)graph[u].size(), b=(int)graph[v].size();
		graph[u].push_back({v,b,id}); graph[v].push_back({u,a,id});
		return id;
	}
	// 連結な無向木。空木可。mergeは結合的、identityは両側単位元。
	// add_vertex(隣接側の集約,v)、lift(頂点込みDP,from,to,edge_id)。
	// 非可換でも隣接辺の追加順を維持する。再帰なし、solveはグラフを変更しない。
	template<class DP, class Merge, class AddVertex, class Lift>
	std::vector<DP> solve(DP identity, Merge merge, AddVertex add_vertex, Lift lift, int root=0) const {
		if (n_==0) { assert(edge_count_==0); return {}; }
		assert(0<=root && root<n_ && edge_count_==n_-1);
		std::vector<int> parent(n_,-1), parent_edge(n_,-1), order{root};
		parent[root]=root;
		for (int i=0; i<(int)order.size(); ++i) {
			int v=order[i];
			for (auto e:graph[v]) if (e.id!=parent_edge[v]) {
				assert(parent[e.to]==-1);
				parent[e.to]=v; parent_edge[e.to]=e.id; order.push_back(e.to);
			}
		}
		assert((int)order.size()==n_);
		std::vector<std::vector<DP>> incoming(n_);
		for (int v=0; v<n_; ++v) incoming[v].assign(graph[v].size(),identity);
		for (int j=n_-1; j>=0; --j) {
			int v=order[j], back=-1; DP aggregate=identity;
			for (int i=0; i<(int)graph[v].size(); ++i) {
				if (graph[v][i].id==parent_edge[v]) back=i;
				else aggregate=merge(aggregate,incoming[v][i]);
			}
			if (back!=-1) {
				auto e=graph[v][back];
				incoming[e.to][e.reverse]=lift(add_vertex(aggregate,v),v,e.to,e.id);
			}
		}
		std::vector<DP> answer(n_,identity);
		for (int v:order) {
			int degree=(int)graph[v].size();
			std::vector<DP> prefix(degree+1,identity), suffix(degree+1,identity);
			for (int i=0; i<degree; ++i) prefix[i+1]=merge(prefix[i],incoming[v][i]);
			for (int i=degree-1; i>=0; --i) suffix[i]=merge(incoming[v][i],suffix[i+1]);
			answer[v]=add_vertex(prefix[degree],v);
			for (int i=0; i<degree; ++i) {
				auto e=graph[v][i];
				if (e.id==parent_edge[v]) continue;
				DP without=merge(prefix[i],suffix[i+1]);
				incoming[e.to][e.reverse]=lift(add_vertex(without,v),v,e.to,e.id);
			}
		}
		return answer;
	}
	int size() const { return n_; }
};
}
