// https://github.com/kabipoyo/library_AC/blob/master/sample/subset_count.hpp
// ABC349 F向け応用。先にmath/subset_transform.hppをコピーする。
// https://atcoder.jp/contests/abc349/tasks/abc349_f
vm zeta_mobius(vi &v, int s) {
	zeta_transform(v, s);
	vm h(1<<s);
	rep(i, 1<<s) h[i] = ((mint)2).pow(v[i]);
	mobius_transform(h, s);
	return h;
}
