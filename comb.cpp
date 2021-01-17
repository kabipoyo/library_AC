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

// 階乗を計算する
vector<mint> _factionals = {0,1};
mint factional(long long n) {
	if(_factionals.size() <= n) {
		long long  i = _factionals.size();
		_factionals.resize(n + 1);
		for(; i <= n; i++) {
			_factionals[i] = _factionals[i - 1] * i;
		}
	}
	return _factionals[n];
}

// 組み合わせ数を計算する。nCr
unordered_map<long long, vector<mint>> _combinations;
mint combination(long long n, long long r) {
	if(n < 1 || r < 1 || n < r) return mint(0);
	if(n == r) return mint(1);

	// nが小さい場合は公式を使う
	if(n < 51000) return factional(n) / (factional(r) * factional(n - r));

	// nが大きい場合はnC(r) = nC(r - 1) * (n - r + 1) / r
	// nC0 = 0, nC1 = nで初期化
	if(r > n - r) r = n - r;
	if(!_combinations.count(n)) {
		_combinations[n] = {0, n};
	}
	auto&& vec = _combinations[n];
	if(vec.size() <= r) {
		long long i = vec.size();
		vec.resize(r + 1);
		for(; i <= r; i++) vec[i] = (vec[i - 1] * (n - i + 1)) / i;
	}

	return vec[r];
}

// 順序のパターン数を計算する。nPr
unordered_map<long long, vector<mint>> _permutations;
mint permutation(long long n, long long r) {
	if(n < 1 || r < 1 || n < r) return mint(0);

	// nが小さい場合は公式を使う
	if(n < 51000) return factional(n) / factional(n - r);

	// nが大きい場合はnP(r) = nP(r - 1) * (n - r + 1)
	// nC0 = 0, nC1 = nで初期化
	if(!_permutations.count(n)) _permutations[n] = {0, n};
	auto&& vec = _permutations[n];
	if(vec.size() <= r) {
		long long i = vec.size();
		vec.resize(r + 1);
		for(; i <= r; i++) vec[i] = vec[i - 1] * (n - i + 1);
	}

	return vec[r];
}
