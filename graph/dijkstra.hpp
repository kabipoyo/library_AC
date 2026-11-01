// https://github.com/kabipoyo/library_AC/blob/master/graph/dijkstra.hpp
// 単一始点最短経路問題
// 計算量：O(ElogV), E: 辺の数, V: 頂点の数
// 負の辺があると使用不可
// make はいずれか片方
// Gの辺は {行き先, 重み}。

#define mp make_pair
using pint = pair<lint, lint>;

void dijkstra(lint start, vector<lint> &dist) {
	lint a=0, b=0, x, y, N = G.size();
	assert(0 <= start && start < N);
	dist.assign(N, LINF); dist[start] = 0;
	priority_queue<pint, vector<pint>, greater<pint>> PQ;
	PQ.push(make_pair(0, start));
	while (!PQ.empty()) {
		tie(x, a) = PQ.top(); PQ.pop();
		if (dist[a] < x) continue;
		for (auto p : G[a]) {
			tie(b, y) = p;
			if (chmin(dist[b], x+y)) PQ.push(make_pair(x+y, b));
		}
	}
}

// startに戻る非空の最短閉路。Gの逆向きグラフRが必要。重みは非負。
// 存在しなければLINF。自己ループと重み0の辺も対象。
lint come_back(lint start) {
	vector<lint> re;
	lint x = LINF;
	swap(G, R);
	dijkstra(start, re); swap(G, R);
	for (auto [to, cost] : G[start]) {
		if (re[to] != LINF && cost < LINF - re[to]) chmin(x, cost + re[to]);
	}
	return x;
}

// start から goal までの最短距離
lint go_to(lint start, lint goal) {
	vector<lint> v;
	dijkstra(start, v);
	return v[goal];
}

/* 経路復元 dijkstra(G,s,dis,prev)
	入力：グラフ G, 開始点 s, 距離を格納する dis, 最短経路の前の点を記録するprev
	計算量：O(|E|log|V|)
	副作用：dis, prevが書き換えられる
*/
void dijkstra_list(lint start, vector<lint> &dist, vector<lint> &prev) {
	lint a=0, b=0, x, y, N = G.size();
	assert(0 <= start && start < N);
	dist.assign(N, LINF); dist[start] = 0;
	prev.assign(N, -1);
	priority_queue<pint, vector<pint>, greater<pint>> PQ;
	PQ.push(make_pair(0, start));
	while (!PQ.empty()) {
		tie(x, a) = PQ.top(); PQ.pop();
		if (dist[a] < x) continue;
		for (auto p : G[a]) {
			tie(b, y) = p;
			if (chmin(dist[b], x+y)) {
				prev[b] = a;
				PQ.push(make_pair(x+y, b));
			}
		}
	}
}
/* get_path(prev, start, t)
	入力：dijkstra で得た prev, ゴール t
	出力： t への最短路のパス
	到達不能は空配列。始点自身への経路は{start}。
*/
vector<lint> get_path(const vector<lint> &prev, lint start, lint t) {
	assert(0 <= start && start < prev.size() && 0 <= t && t < prev.size());
	vector<lint> path;
	for (lint cur = t; cur != -1; cur = prev[cur]) {
		assert(0 <= cur && cur < prev.size());
		path.push_back(cur);
		if (cur == start) {
			reverse(path.begin(), path.end());
			return path;
		}
	}
	return {};
}

