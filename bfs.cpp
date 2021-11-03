// グラフ作成
vector<vector<int>> G;
void make_graph(int N, int M) {
	G.resize(N);
	int x, y;
	rep(i, M) {
		cin >> x >> y;
		x--, y--;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}

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

// 重みつきグラフ作成
vector<vector<pair<lint, lint>>> G;
void make_dist_graph(int N, int M) {
	G.resize(N);
	lint x, y, z;
	rep(i, M) {
		cin >> x >> y >> z;
		x--, y--;
		G[x].push_back(make_pair(y, z));
		G[y].push_back(make_pair(x, z));
	}
}

// root からの距離算出
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

/* topo_sort(G): グラフG をトポロジカルソート
	返り値: トポロジカルソートされた頂点番号
	計算量: O(|E|+|V|)
 */
vi topo_sort() {
	vi res;
	lint N = G.size();
	vi v(N);
	rep(i, N) { for (auto e : G[i]) v[e]++; }
	queue<int> Q;
	rep(i, N) { if (!v[i]) Q.push(i); }
	while (!Q.empty()) {
		int x = Q.front(); Q.pop();
		res.push_back(x);
		for (auto e : G[x]) {
			v[e]--;
			if (!v[e]) Q.push(e);
		}
	}
	return res;
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

// 強連結成分分解（SCC）
// 有向グラフをループ毎に分解する
// O(N+M)
vi used, route;
void rec(int x) {
	used[x]++;
	for (auto t : G[x]) {
		if (used[t] == -1) rec(t);
	}
	route.pb(x);
}
vi dfs(int x) {
	used[x]++;
	stack<lint> s;
	s.push(x);
	vi v;
	while (!s.empty()) {
		int z = s.top();
		v.pb(z); s.pop();
		for (auto t : R[z]) {
			if (used[t] == 0) {
				s.push(t);
				used[t]++;
			}
		}
	}
	return v;
}
vvi scc() {
	int N = G.size();
	used.resize(N, -1);
	rep(i, N) {
		if (used[i] == -1) rec(i);
	}
	reverse(all(route));
	vvi res;
	rep(i, N) {
		if (used[route[i]] == 0) res.pb(dfs(route[i]));
	}
	return res;
}
