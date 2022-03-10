lint gcd(lint a, lint b) { return b?gcd(b,a%b):a; }  // 最大公約数
lint lcm(lint a, lint b) { return a/gcd(a,b)*b; }    // 最小公倍数

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
	lint x, y;
	extgcd(a, m, x, y);
	return (m + x % m) % m;
}

// a/b % m
lint moddiv(lint a, lint b, lint m) {
	return (a * modinv(b, m)) %m;
}

// 除算を掛け算に変換しておく
vi div(200200);
repx(i, 1, 200200) div[i] = modinv(i, 998244353);

// a^b % m  O(logb)
lint modpow(lint a, lint b, lint M) {
	lint x = 1;
	vi v(100);
	v[0] = a;
	rep(i, 100-1) {
		if ((1L<<i) > b) break;
		v[i+1] = (v[i]*v[i]) % M;
	}
	rep(i, 100-1) {
		if ((1L<<i) > b) break;
		if ((1L<<i) & b) x = (x*v[i]) % M;
	}
	return x;
}

// 離散対数問題
// X^a = Y mod M を満たす最小の a を O(√M) で求める
lint baby_step_giant_step(lint X, lint Y, lint M) {
	if (__gcd(X, M) != 1) return -1;
	lint m = ceil(sqrt(M));
	// baby-step
	lint a = 1;
	unordered_map<lint, lint> p;
	rep(i, m) {
		a = (a*X) % M;
		if (!p.count(a)) p[a] = i+1;
	}
	// giant_step
	lint b = 1;
	rep(i, m) b = moddiv(b, X, M);
	lint c = Y;
	rep(i, m) {
		if (p.count(c)) return m*i+p[c];
		c = (c*b) % M;
	}
	return -1;
}
