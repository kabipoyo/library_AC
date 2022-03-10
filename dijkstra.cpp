// 単一始点最短経路問題
// 計算量：O(ElogV), E: 辺の数, V: 頂点の数
// 負の辺があると使用不可
// make はいずれか片方

constexpr lint LINF = LLONG_MAX/2;
#define mp make_pair
using pint = pair<lint, lint>;

// 重みつきグラフを生成
vector<vector<pair<lint, lint>>> G;
void make_dist_graph(lint N, lint M) {
	lint x, y, z;
	G.resize(N);
	rep(i, M) {
		cin >> x >> y >> z;
		x--, y--;
		G[x].push_back(make_pair(z, y));
	}
}

// 重みつきグラフを行き・帰りで生成
vector<vector<pair<lint, lint>>> G;
vector<vector<pair<lint, lint>>> R;
void make_round_graph(lint N, lint M) {
	lint x, y, z;
	G.resize(N), R.resize(N);
	rep(i, M) {
		cin >> x >> y >> z;
		x--, y--;
		G[x].push_back(make_pair(z, y));
		R[y].push_back(make_pair(z, x));
	}
}

// 無向グラフ
vector<vector<pair<lint, lint>>> G;
void make_graph(lint N, lint M) {
	lint x, y;
	G.resize(N);
	rep(i, M) {
		cin >> x >> y;
		x--, y--;
		G[x].push_back(make_pair(1, y));
		G[y].push_back(make_pair(1, x));
	}
}

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
