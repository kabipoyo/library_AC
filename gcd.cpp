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
