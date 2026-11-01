lint gcd(lint a, lint b) { return b?gcd(b,a%b):a; }  // 最大公約数
lint lcm(lint a, lint b) { return a == 0 || b == 0 ? 0 : a/gcd(a,b)*b; } // 最小公倍数（結果はlint内）

// 拡張ユークリッドの互除法
// 返り値：gcd(a,b)
// x, y値：ax+by = gcd(a,b) の解のひとつ
lint extgcd(lint a, lint b, lint &x, lint &y) {
	if (b == 0) { x = 1, y = 0; return a; }
	lint d = extgcd(b, a%b, y, x);
	y -= a/b * x;
	return d;
}

// a mod m での逆元
lint modinv(lint a, lint m) {
	assert(m >= 1);
	lint x, y;
	a %= m; if (a < 0) a += m;
	assert(std::gcd(a, m) == 1);
	extgcd(a, m, x, y);
	x %= m; if (x < 0) x += m;
	return x;
}

// a/b % m
lint moddiv(lint a, lint b, lint m) {
	return (__int128(a % m) * modinv(b, m) % m + m) % m;
}

// 逆元の前計算例（関数内にコピーする）：
// vi inverse(200200);
// repx(i, 1, 200200) inverse[i] = modinv(i, 998244353);

// a^b % m  O(logb)
lint modpow(lint a, lint b, lint M) {
	assert(M >= 1 && b >= 0);
	lint x = 1 % M;
	a %= M; if (a < 0) a += M;
	while (b) {
		if (b & 1) x = __int128(x) * a % M;
		a = __int128(a) * a % M;
		b >>= 1;
	}
	return x;
}

// 離散対数問題
// X^a = Y mod M を満たす最小の a を O(√M) で求める
lint baby_step_giant_step(lint X, lint Y, lint M) {
	assert(M >= 1);
	X %= M; if (X < 0) X += M;
	Y %= M; if (Y < 0) Y += M;
	if (Y == 1 % M) return 0;
	// 互いに素でない場合は非対応（-1）。
	if (std::gcd(X, M) != 1) return -1;
	lint m = sqrtl(M);
	if (__int128(m) * m < M) ++m;
	// baby-step
	lint a = 1;
	unordered_map<lint, lint> p;
	p[1] = 0;
	rep(i, m) {
		a = __int128(a) * X % M;
		if (!p.count(a)) p[a] = i+1;
	}
	// giant_step
	lint b = modpow(modinv(X, M), m, M);
	lint c = Y;
	rep(i, m) {
		if (p.count(c)) return m*i+p[c];
		c = __int128(c) * b % M;
	}
	return -1;
}
