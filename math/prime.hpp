// https://github.com/kabipoyo/library_AC/blob/master/math/prime.hpp
// エラトステネスの篩

// Sieve S(N);
struct Sieve {
	int n;
	vector<lint> p;
	Sieve(int n=1):n(n), p(max(n, 1)+1) {
		assert(n >= 0);
		p.at(0) = -1, p.at(1) = -1;
		for(lint i=2; i<=n; i++) {
			if(!p.at(i)) {
				p.at(i) = i;
				for(lint j=i*i; j<=n; j+=i) {
					if (!p.at(j)) p.at(j) = i;
				}
			}
		}
	}
	bool isPrime(int x) { assert(0 <= x && x <= n); return x >= 2 && p.at(x) == x;}
	vector<lint> factorList(int x) {
		assert(1 <= x && x <= n);
		vector<lint> v;
		while (x != 1) {
			v.push_back(p.at(x));
			x /= p.at(x);
		}
		return v;
	}
	vector<lint> factor(int x) {
		assert(1 <= x && x <= n);
		vector<lint> v;
		while (x != 1) {
			int t = p.at(x);
			v.push_back(t);
			while (x % t == 0) x /= t;
		}
		return v;
	}
};

// 約数
vector<lint> divisor(lint n) {
	assert(n >= 1);
	vector<lint> v;
	for (lint i = 1; i <= n/i; i++) {
		if (n % i == 0) {
			v.push_back(i);
			if (i*i != n) v.push_back(n/i);
		}
	}
	sort(v.begin(), v.end());
	return v;
}

// 64bit整数の試し割り。O(sqrt(n))時間、O(1)補助空間。
// 巨大な素数には時間がかかる（高速な64bit素数判定ではない）。
bool isPrime(lint n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (lint i = 3; i <= n / i; i += 2) if (n % i == 0) return false;
    return true;
}

// 重複なしの素因数。n >= 1。
vector<lint> factor(lint n) {
    assert(n >= 1);
    vector<lint> result;
    for (lint p = 2; p <= n / p; p += (p == 2 ? 1 : 2)) {
        if (n % p) continue;
        result.push_back(p);
        while (n % p == 0) n /= p;
    }
    if (n > 1) result.push_back(n);
    return result;
}

// 重複ありの素因数。n >= 1。
vector<lint> factorList(lint n) {
    assert(n >= 1);
    vector<lint> result;
    for (lint p = 2; p <= n / p; p += (p == 2 ? 1 : 2)) {
        while (n % p == 0) { result.push_back(p); n /= p; }
    }
    if (n > 1) result.push_back(n);
    return result;
}

