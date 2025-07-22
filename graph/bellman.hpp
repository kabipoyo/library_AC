/* bellman_ford(V, s, dis)
	単一始点最短経路問題（全ての頂点に対して）を解く
	入力: 全ての辺Es, 頂点数V, 開始点 s, 最短経路を記録するdis
	出力: 負の閉路が存在するなら ture
	計算量：O(|E||V|)
	副作用：dis が書き換えられる
	● 負の辺が含まれていても良い
	● 負の閉路を検出可能
*/
// 牛ゲーを解く際にも使う
// https://tjkendev.github.io/procon-library/python/graph/difference-constraints-ushi.html
// https://ei1333.github.io/luzhiled/snippets/memo/ushi-game.html

using pint = pair<lint, lint>;

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

bool bellman_ford(int N, int s, vector<lint> &dis) {
	dis.resize(N, LINF);
	dis[s] = 0;
	lint c, x, z;
	for (c = 0; c < N; c++) {
		bool end = true;
		rep(i, N) {
			if (dis[i] == LINF) continue;
			for (auto e : G[i]) {
				tie(z, x) = e;
				if (chmin(dis[x], dis[i]+z)) end = false;
			}
		}
		if (end) break;
	}
	return (c == N);
}

// ベルマンフォード後、ゴールまでの経路に負の閉路が存在するか判定
bool check_close(int N, int g, vector<lint> &dis) {
	vector<bool> v(N);
	lint x, z;
	rep(t, N) {
		rep(i, N) {
			if (dis[i] == LINF) continue;
			for (auto e : G[i]) {
				tie(z, x) = e;
				if (chmin(dis[x], dis[i]+z)) v[x] = true;
				if (v[i]) v[x] = true;
			}
		}
	}
	return v[g];
}
