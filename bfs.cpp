// グラフ作成
vector<vector<int>> G(300000);
void make_graph(int M) {
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
vector<int> dist(300000);
void bfs(int root) {
	int x, y;
	queue<int> Q;
	fill(dist.begin(), dist.end(), -1);
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
vector<vector<pair<int, lint>>> G(300000);
void make_dist_graph(int M) {
	int x, y, z;
	rep(i, M) {
		cin >> x >> y >> z;
		x--, y--;
		G[x].push_back(make_pair(y, z));
		G[y].push_back(make_pair(x, z));
	}
}

// root からの距離算出
vector<lint> dist(300000);
void bfs_dist(int root) {
	int x, y, z;
	queue<int> Q;
	fill(dist.begin(), dist.end(), -1);
	Q.push(root), dist[root] = 0;
	while (!Q.empty()) {
		x = Q.front(); Q.pop();
		rep(i, G[x].size()) {
			tie(y, z) = G[x][i];
			if (dist[y] == -1) { Q.push(y); dist[y] = dist[x]+z; }
		}
	}
}
