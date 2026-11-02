// https://github.com/kabipoyo/library_AC/blob/master/acl/mincostflow.hpp
#pragma once
#include <atcoder/mincostflow>
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
// 参考: https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html
namespace acl_mincostflow {
using Graph = atcoder::mcf_graph<int,long long>;
// Graph g(n); int id=g.add_edge(u,v,capacity,cost); costも非負。
// auto [flow,cost]=g.flow(s,t,required); flow<requiredなら必要量を流せない。
// auto points=g.slope(s,t); は流量と最小コストの折点（全整数流量ではない）。
// flow/slopeを同じグラフで複数回呼ばない。比較・再計算は新しく構築する。
// get_edge(id).flowで復元。合計費用・中間値とACL公式のn*最大cost制約に注意。
}

namespace acl_weighted_matching {
struct Edge { int left, right; long long gain; };
struct Result {
	std::vector<long long> best; // best[k]: ちょうどk組の最大利益。k=0..最大組数。
	std::vector<int> edge_indices; // 最大組数で利益最大となる入力辺添字。
};
// 利益は負も可。shift-gain、費用・補正・中間積はlong long内、ACLの費用制約も満たすこと。
// 最大組数の解と、組数自由で利益最大の解を混同しない（後者の値はmax(best)）。
inline Result solve(int left, int right, const std::vector<Edge>& edges) {
	assert(left>=0 && right>=0);
	int s=left+right, t=s+1;
	long long shift=0;
	for (auto e: edges) shift=std::max(shift,e.gain);
	atcoder::mcf_graph<int,long long> g(t+1);
	for (int u=0; u<left; ++u) g.add_edge(s,u,1,0);
	for (int v=0; v<right; ++v) g.add_edge(left+v,t,1,0);
	std::vector<int> ids;
	for (auto e: edges) {
		assert(0<=e.left && e.left<left && 0<=e.right && e.right<right);
		ids.push_back(g.add_edge(e.left,left+e.right,1,shift-e.gain));
	}
	auto points=g.slope(s,t);
	Result result{std::vector<long long>(points.back().first+1),{}};
	for (int i=1; i<(int)points.size(); ++i) {
		auto [a,ca]=points[i-1]; auto [b,cb]=points[i];
		long long marginal=(cb-ca)/(b-a);
		for (int k=a+1; k<=b; ++k) result.best[k]=shift*k-(ca+marginal*(k-a));
	}
	for (int i=0; i<(int)ids.size(); ++i) if (g.get_edge(ids[i]).flow) result.edge_indices.push_back(i);
	return result;
}
}
