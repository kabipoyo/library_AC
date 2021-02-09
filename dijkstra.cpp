// 単一始点最短経路問題
// 計算量：O(ElogV), E: 辺の数, V: 頂点の数
// 負の辺があると使用不可
// make はいずれか片方

constexpr lint LINF = LLONG_MAX/2;
#define mp make_pair
using pint = pair<lint, lint>;

// 重みつきグラフを生成
vector<vector<pair<lint, lint>>> G;
void make_dist_graph(int N, int M) {
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
void make_round_graph(int N, int M) {
	lint x, y, z;
	G.resize(N), R.resize(N);
	rep(i, M) {
		cin >> x >> y >> z;
		x--, y--;
		G[x].push_back(make_pair(z, y));
		R[y].push_back(make_pair(z, x));
	}
}

void dijkstra(int start, vector<lint> &dist) {
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
lint come_back(int start) {
	vector<lint> go, re;
	lint x = LINF;
	dijkstra(start, go); swap(G, R);
	dijkstra(start, re); swap(G, R);
	rep(i, go.size()) if (go[i] && re[i]) chmin(x, go[i]+re[i]);
	return x;
}

// start から goal までの最短距離
lint go_to(int start, int goal) {
	vector<lint> v;
	dijkstra(start, v);
	return v[goal];
}
