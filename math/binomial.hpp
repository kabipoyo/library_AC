// C(60, 30) ぐらいまでなら収まる
lint binomial(int n, int k) {
	if (k < 0 || k > n) return 0;
	k = min(k, n-k);
	__int128 ans = 1;
	rep(i, k) {
		ans *= (n-i);
		ans /= (i+1);
		assert(ans <= LLONG_MAX);
	}
	assert(ans <= LLONG_MAX);
	return (lint)ans;
}

// 二項係数が奇数ならtrue
bool is_nCk_odd(int n, int k){
	return (n&k)==k;
}
