// https://github.com/kabipoyo/library_AC/blob/master/graph/bitDP_count.hpp
// 制約付き数え上げ 貰うbitDP
// O(N2^N)
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
	assert(0 <= N && N <= 18);
	dp.assign(1<<N, 0);
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


