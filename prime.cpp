// エラトステネスの篩

// Sieve S(N);
struct Sieve {
	int n;
	vector<lint> p;
	Sieve(int n=1):n(n), p(n+1) {
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
	bool isPrime(int x) { return p.at(x) == x;}
	vector<lint> factorList(int x) {
		vector<lint> v;
		while (x != 1) {
			v.push_back(p.at(x));
			x /= p.at(x);
		}
		return v;
	}
	vector<lint> factor(int x) {
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
	vector<lint> v;
	for (lint i = 1; i*i <= n; i++) {
		if (n % i == 0) {
			v.push_back(i);
			if (i*i != n) v.push_back(n/i);
		}
	}
	sort(v.begin(), v.end());
	return v;
}

// longlong prime
bool isPrime(lint n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (!(n % 2)) return false;
	int rn = sqrt(n);
	vector<bool> v(rn+1);
	for(lint i = 3; i <= rn; i += 2) {
		if(!v.at(i)) {
			if (!(n % i)) return false;
			v.at(i) = 1;
			for(lint j = i*i; j <= rn; j += i) {
				v.at(j) = 1;
			}
		}
	}
	return true;
}

// 素因数を返す　返り値に１は入らない
vector<lint> factor(lint n) {
	vector<lint> V;
	if (!(n % 2)) {
		V.push_back(2);
		while (!(n % 2)) n /= 2;
	}
	int rn = sqrt(n);
	vector<bool> v(rn+1);
	for(lint i = 3; i <= rn && n > 1; i += 2) {
		if(!v.at(i)) {
			if (!(n % i)) {
				V.push_back(i);
				while (!(n % i)) n /= i;
			}
			v.at(i) = 1;
			for(lint j = i*i; j <= rn; j += i) {
				v.at(j) = 1;
			}
		}
	}
	if (n != 1) V.push_back(n);
	return V;
}

// 素因数分解する　返り値に１は入らない
vector<lint> factorList(lint n) {
	vector<lint> V;
	if (!(n % 2)) {
		while (!(n % 2)) {
			V.push_back(2);
			n /= 2;
		}
	}
	int rn = sqrt(n);
	vector<bool> v(rn+1);
	for(lint i = 3; i <= rn && n > 1; i += 2) {
		if(!v.at(i)) {
			if (!(n % i)) {
				while (!(n % i)) {
					V.push_back(i);
					n /= i;
				}
			}
			v.at(i) = 1;
			for(lint j = i*i; j <= rn; j += i) {
				v.at(j) = 1;
			}
		}
	}
	if (n != 1) V.push_back(n);
	return V;
}
