constexpr int INF = INT_MAX/2;
int node, start;
vvi dist(18, vi(18));  // 事前に準備しておく
vector<vector<int>> dp((1<<18), vector<int>(18, -1));

int rec(int bit, int v) {
	if (dp[bit][v] != -1) return dp[bit][v];
	if (bit == (1<<v)) return dp[bit][v] = start;
	int res = INF,  prev_bit = bit & ~(1<<v);
	for (int u = 0; u < node; ++u) {
		if (!(prev_bit & (1<<u))) continue;
		chmin(res, rec(prev_bit, u) + dist[u][v]);
	}
	return dp[bit][v] = res;
}

int bitDP(int n, int s) {
	node = n, start = s;
	int res = INF;
	rep(i, node) chmin(res, rec((1<<node)-1, i));
	return res;
}

int get_dest(int N, int d) {
	return dp[(1<<N)-1][d]; // 終点が地点 d の最短経路
}
