// 配るbitDP(ウォーク向け)
vvi dist(20, vi(20, LINF));  // 事前に準備しておく
lint bitDP(lint N, lint s) {
	assert(1 <= N && N <= 20);
	vector<vector<lint>> dp(1<<N, vector<lint>(N, LINF));
	rep(i, N) dp[1<<i][i] = s;
	repx(bit, 1, 1<<N) {
		rep(i, N) {
			if (~bit >> i & 1) continue;
			if (dp[bit][i] == LINF) continue;
			rep(j, N) {
				if (bit >> j & 1) continue;
				if (dist[i][j] == LINF) continue;
				chmin(dp[bit|1<<j][j], dp[bit][i] + dist[i][j]);
			}
		}
	}
	lint res = LINF;
	rep(i, N) chmin(res, dp[(1<<N)-1][i]);
	return res;
}
