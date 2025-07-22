// コードの切れ端

// 座標圧縮
template<class T> map<T, int> coord_comp(set<T> s) {
	int a = 0;
	map<T, int> m;
	for (auto u : s) m[u] = ++a;
	return m;
}
set<lint> s;
rep(i, N) s.insert(v[i]);
s.insert(LINF);
map<lint, int> m = coord_comp(s);

// x = binary_search(&v, key);

// key 以上の最小の値がある要素番号を返す
template<class T> inline int binary_search_min(vector<T> &v, T key) {
	lint ng = -1, mid, ok = v.size();
	while (abs(ok - ng) > 1) {
		mid = (ok + ng) / 2;
		if (v.at(mid) >= key) ok = mid;
		else ng = mid;
	}
	return ok;
}

// key 以下の最大の値がある要素番号を返す
template<class T> inline int binary_search_max(vector<T> &v, T key) {
	lint ok = -1, mid, ng = v.size();
	while (abs(ok - ng) > 1) {
		mid = (ok + ng) / 2;
		if (v.at(mid) <= key) ok = mid;
		else ng = mid;
	}
	return ok;
}

// 原点からの極座標の角度の「大きい順」に番号を付ける（0<=Θ<=π/2）
// 2πまでいけるっぽい　https://yukicoder.me/submissions/881877 <- 嘘かも
using pint = pair<lint, lint>;
using vp = vector<pint>;
map<pint, lint> polar_sort(vp v) {
	sort(all(v), [](auto const& lhs, auto const& rhs) {
		return lhs.first*rhs.second < rhs.first*lhs.second;
	});
	map<pint, lint> m;
	lint a = 0;
	for (auto p : v) m[p] = ++a;
	return m;
}

// 単位円の[0～2π)までソートする
sort(all(p), [](auto const& lhs, auto const& rhs) {
	double d = atan2(lhs.second, lhs.first);
	if (d < 0) d += PI*2;
	double e = atan2(rhs.second, rhs.first);
	if (e < 0) e += PI*2;
	return d < e;
});

// 右90°回転
template<class T> vector<T> rotation_right(int N, vector<T> &v) {
	vector<T> w(N);
	rep(i, N) {
		rep(j, N) {
			w[i].pb(v[N-1-j][i]);
		}
	}
	return w;
}
