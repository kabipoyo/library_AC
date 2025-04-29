/* Rerooting: 全方位木 DP
	dpall[i][j]：ノードiのjから先にあるノード数を数える
	計算量: O(N)
*/
vi dp;
vector<map<lint, lint>> dpall;
lint dfs(int root, int from) {
	for (auto t : G[root]) {
		if (t == from) continue;
		dp[root] += dfs(t, root);
	}
	return dp[root]+1;
}
void bfs(int root, int from) {
	lint a = 0, N = G.size();
	for (auto t : G[root]) {
		if (t == from) continue;
		dpall[root][t] = dp[t]+1;
		a += dp[t]+1;
		bfs(t, root);
	}
	dpall[root][from] = N-a-1;
}

void Rerooting() {
	int N = G.size();
	dp.resize(N);
	dpall.resize(N);
	dfs(0, -1);
	bfs(0, -1);
	dpall[0].erase(-1);
}

// https://atcoder.jp/contests/abc160/tasks/abc160_f
vi dp;
vm dpall;
lint dfs(int root, int from) {
	dp[root] = 1;
	for (auto t : G[root]) {
		if (t == from) continue;
		dp[root] += dfs(t, root);
	}
	dpall[0] /= dp[root];
	return dp[root];
}
void bfs(int root, int from) {
	lint N = G.size();
	for (auto t : G[root]) {
		if (t == from) continue;
		dpall[t] = dpall[root] * dp[t] / (N-dp[t]);
		bfs(t, root);
	}
}

void Rerooting() {
	int N = G.size();
	dp.resize(N);
	dpall.resize(N);
	dpall[0] = fact[N];
	dfs(0, -1);
	bfs(0, -1);
}
