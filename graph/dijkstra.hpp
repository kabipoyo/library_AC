// 単一始点最短経路問題
// 計算量：O(ElogV), E: 辺の数, V: 頂点の数
// 負の辺があると使用不可
// make はいずれか片方

constexpr lint LINF = LLONG_MAX/2;
#define mp make_pair
using pint = pair<lint, lint>;

void dijkstra(lint start, vector<lint> &dist) {
	lint a=0, b=0, x, y, N = G.size();
	dist.resize(N, LINF); dist[start] = 0;
	priority_queue<pint, vector<pint>, greater<pint>> PQ;
	PQ.push(make_pair(0, start));
	while (!PQ.empty()) {
		tie(x, a) = PQ.top(); PQ.pop();
		if (dist[a] < x) continue;
		for (auto p : G[a]) {
			tie(y, b) = p;
			if (chmin(dist[b], x+y)) PQ.push(make_pair(x+y, b));
		}
	}
}

// start から start までの最短距離
lint come_back(lint start) {
	vector<lint> go, re;
	lint x = LINF;
	dijkstra(start, go); swap(G, R);
	dijkstra(start, re); swap(G, R);
	rep(i, go.size()) if (go[i] && re[i]) chmin(x, go[i]+re[i]);
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
	dist.resize(N, LINF); dist[start] = 0;
	prev.resize(N, -1);
	priority_queue<pint, vector<pint>, greater<pint>> PQ;
	PQ.push(make_pair(0, start));
	while (!PQ.empty()) {
		tie(x, a) = PQ.top(); PQ.pop();
		if (dist[a] < x) continue;
		for (auto p : G[a]) {
			tie(y, b) = p;
			if (chmin(dist[b], x+y)) {
				prev[b] = a;
				PQ.push(make_pair(x+y, b));
			}
		}
	}
}
/* get_path(prev, t)
	入力：dijkstra で得た prev, ゴール t
	出力： t への最短路のパス
	最短経路がない場合は事前に場合分けをすること
*/
vector<lint> get_path(vector<lint> &prev, lint t) {
	vector<lint> path;
	for (lint cur = t; cur != -1; cur = prev[cur]) {
		path.push_back(cur);
	}
	reverse(path.begin(), path.end()); // 逆順なのでひっくり返す
	return path;
}

// 拡張ダイクストラ（状態１：最短経路、状態２：最大化したい変数）
using pint = pair<lint, lint>;
using ppint = pair<pint, lint>;
using vp = vector<pint>;
vector<vector<pair<lint, lint>>> G;

void dijkstra(lint start, vector<pint> &dist) {
	lint N = G.size();
	lint a=0, b=0, c=0, x, y, z;
	pint p;
	dist.resize(N, {LINF, 0}); dist[start] = {0, 0};
	priority_queue<ppint, vector<ppint>, greater<ppint>> PQ;
	PQ.push(make_pair(make_pair(0, 0), start));
	while (!PQ.empty()) {
		tie(p, a) = PQ.top(); PQ.pop();
		tie(x, z) = p;
		if (dist[a].first < x) continue;
		if (dist[a].first == x && dist[a].second > z) continue;
		for (auto p : G[a]) {
			tie(y, b) = p;
			if (chmin(dist[b].first, x+1)) dist[b].second = z+y, PQ.push(make_pair(make_pair(x+1, z+y), b));
			else if (dist[b].first == x+1 && chmax(dist[b].second, z+y)) PQ.push(make_pair(make_pair(x+1, z+y), b));
		}
	}
}
