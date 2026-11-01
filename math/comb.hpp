// https://github.com/kabipoyo/library_AC/blob/master/math/comb.hpp
// ACL mint 対応版
struct combination {
	vector<mint> fact, ifact;
	combination(int n):fact(n+1),ifact(n+1) {
		assert(0 <= n && n < mint::mod());
		fact[0] = 1;
		for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
		ifact[n] = fact[n].inv();
		for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
	}
	mint operator()(int n, int k) {
		if (k < 0 || k > n) return 0;
		assert(n < (int)fact.size());
		return fact[n]*ifact[k]*ifact[n-k];
	}
};

struct permutation {
	vector<mint> fact, ifact;
	permutation(int n):fact(n+1),ifact(n+1) {
		assert(0 <= n && n < mint::mod());
		fact[0] = 1;
		for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
		ifact[n] = fact[n].inv();
		for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
	}
	mint operator()(int n, int k) {
		if (k < 0 || k > n) return 0;
		assert(n < (int)fact.size());
		return fact[n]*ifact[n-k];
	}
};

// NをK個の正整数の和に分ける順序付き分割数。
combination C(200002);
mint divide_comb(int N, int K) {
	if (N == 0 && K == 0) return 1;
	if (N < 1 || K < 1 || K > N) return 0;
	return C(N-1, K-1);
}

