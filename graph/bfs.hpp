
// root からの距離算出
// 根付き木生成のための深さ探索など
vector<lint> dist;
void bfs(int root) {
	lint x, y, z, N = G.size();
	dist.resize(N, -1);
	queue<int> Q;
	Q.push(root), dist[root] = 0;
	while (!Q.empty()) {
		x = Q.front(); Q.pop();
		rep(i, G[x].size()) {
			y = G[x][i];
			if (dist[y] == -1) { Q.push(y); dist[y] = dist[x]+1; }
		}
	}
}

// root からの距離算出
// G[src][i] = {dst, dist};
vector<lint> dist;
void bfs_dist(int root) {
	lint x, y, z, N = G.size();
	queue<int> Q;
	dist.resize(N, -1);
	Q.push(root), dist[root] = 0;
	while (!Q.empty()) {
		x = Q.front(); Q.pop();
		rep(i, G[x].size()) {
			tie(y, z) = G[x][i];
			if (dist[y] == -1) { Q.push(y); dist[y] = dist[x]+z; }
		}
	}
}

// dist配列があるときに、root から node の最短経路を復元する
vi root_to_node(int root, int node) {
	vi v = {node};
	while (dist[node]) {
		int d = dist[node];
		rep(i, G[node].size()) {
			if (dist[G[node][i]] == d-1) {
				v.pb(G[node][i]);
				node = G[node][i];
				break;
			}
		}
	}
	reverse(all(v));
	return v;
}

// 二部グラフの頂点彩色
// ２点を別の色で塗る
void another_color(dsu &d, int N, int i, int j) {
	d.merge(i+N, j);
	d.merge(i, j+N);
}
// ２点を同じ色で塗る
void same_color(dsu &d, int N, int i, int j) {
	d.merge(i, j);
	d.merge(i+N, j+N);
}
// グラフの塗分けが可能か？
bool is_bipartite(dsu &d, int N) {
	rep(i, N) {
		if (d.same(i, i+N)) return false;
	}
	return true;
}
