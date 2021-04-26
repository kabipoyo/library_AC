// 巡回セールスマン問題 メモ化再帰bitDP
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

int bitDP(int N, int s) {
	node = N, start = s;  // 初期コスト
	int res = INF;
	rep(i, node) chmin(res, rec((1<<node)-1, i));
	return res;
}

int get_dest(int N, int d) {
	return dp[(1<<N)-1][d];  // 終点が地点 d の最短経路
}

// 制約付き数え上げ 貰うbitDP
// O(N2^N)
constexpr int INF = INT_MAX/2;
int node, start;
vector<lint> dp(1<<18);
vvi cons(18, vi(18, INF));  // 事前に準備しておく

bool legal(int bit) {
	bitset<18> bits = bit;
	int x = bits.count()-1, y = 0;
	rep(i, 18) {
		if (bits.test(i)) y++;
		if (cons[x][i] < y) return false;
	}
	return true;
}


lint bitDP(int N, lint s) {
	dp[0] = s;  // 初期コスト
	repx(bit, 1, (1<<N)) {
		if (legal(bit)) {
			rep(i, N) {
				if (bit & (1<<i)) dp[bit] += dp[bit^(1<<i)];
			}
		}
	}
	return dp[(1<<N)-1];
}
