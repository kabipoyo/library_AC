// 木専用の距離計算。一般の重み付きグラフの最短路には使わない。
// G[src][i] = {重み, 行き先};
vector<lint> dist;
void bfs_dist(int root) {
	lint x, y, z, N = G.size();
	vector<bool> seen(N); seen[root] = true;
	queue<int> Q;
	dist.assign(N, -1);
	Q.push(root), dist[root] = 0;
	while (!Q.empty()) {
		x = Q.front(); Q.pop();
		rep(i, G[x].size()) {
			tie(z, y) = G[x][i];
			if (!seen[y]) { seen[y] = true; Q.push(y); dist[y] = dist[x]+z; }
		}
	}
}

