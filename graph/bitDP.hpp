// 巡回セールスマン問題 メモ化再帰bitDP
lint node, start;
vvi dist(18, vi(18));  // 事前に準備しておく
vector<vector<lint>> dp;
vector<vector<bool>> seen;

lint rec(lint bit, lint v) {
	if (seen[bit][v]) return dp[bit][v];
	seen[bit][v] = true;
	if (bit == (1<<v)) return dp[bit][v] = start;
	lint res = LINF,  prev_bit = bit & ~(1<<v);
	for (lint u = 0; u < node; ++u) {
		if (!(prev_bit & (1<<u))) continue;
		lint cost = rec(prev_bit, u);
		if (cost != LINF && dist[u][v] != LINF) chmin(res, cost + dist[u][v]);
	}
	return dp[bit][v] = res;
}

lint bitDP(lint N, lint s) {
	node = N, start = s;  // 初期コスト
	assert(1 <= N && N <= 18);
	dp.assign(1<<N, vector<lint>(N));
	seen.assign(1<<N, vector<bool>(N));
	lint res = LINF;
	rep(i, node) chmin(res, rec((1<<node)-1, i));
	return res;
}

lint get_dest(lint N, lint d) {
	return dp[(1<<N)-1][d];  // 終点が地点 d の最短経路
}


