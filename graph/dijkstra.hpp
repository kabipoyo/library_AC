// https://github.com/kabipoyo/library_AC/blob/master/graph/dijkstra.hpp
// 非負重み。Gの辺は{行き先,重み}、距離の到達不能はLINF。
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

// distとprevを上書き。prevは直前頂点、始点・到達不能では-1。
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
// 到達不能は空配列、始点自身へは{start}。
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

