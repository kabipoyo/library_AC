// incluce "mint.cpp"
// combination x(int);
// x(n, r);
struct combination {
	vector<mint> fact, ifact;
	combination(int n):fact(n+1),ifact(n+1) {
		assert(n < mod);
		fact[0] = 1;
		for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
		ifact[n] = fact[n].inv();
		for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
	}
	mint operator()(int n, int k) {
		if (k < 0 || k > n) return 0;
		return fact[n]*ifact[k]*ifact[n-k];
	}
};

// ACL mint 対応版
struct combination {
	vector<mint> fact, ifact;
	combination(int n):fact(n+1),ifact(n+1) {
		assert(n < mint::mod());
		fact[0] = 1;
		for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
		ifact[n] = fact[n].inv();
		for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
	}
	mint operator()(int n, int k) {
		if (k < 0 || k > n) return 0;
		return fact[n]*ifact[k]*ifact[n-k];
	}
};

struct permutation {
	vector<mint> fact, ifact;
	permutation(int n):fact(n+1),ifact(n+1) {
		assert(n < mint::mod());
		fact[0] = 1;
		for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
		ifact[n] = fact[n].inv();
		for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
	}
	mint operator()(int n, int k) {
		if (k < 0 || k > n) return 0;
		return fact[n]*ifact[n-k];
	}
};

// N 個のものを K 組み（各組１つ以上）に分ける組み合わせの数
// 解説：○ が N個、| が K-1個あり、一列に並べることを考える
// 　　　K組に ○ を１つずつ割り当てておくので、残りの ○ は N-K個
// 　　　(N-K)+(K-1) = N-1個の ○| を一列に並べればよい
// 　　　N-1箇所から | を置く K-1箇所を選ぶので、C(N-1, K-1)
combination C(200002);
mint divide_comb(int N, int K) {
	return C(N-1, K-1);
}

// C(60, 30) ぐらいまでなら収まる
lint combination (int n, int k) {
	lint ans = 1;
	rep(i, k) {
		ans *= (n-i);
		ans /= (i+1);
	}
	return ans;
}

// 二項係数が奇数ならtrue
bool is_nCk_odd(int n, int k){
	return (n&k)==k;
}
