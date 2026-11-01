// https://github.com/kabipoyo/library_AC/blob/master/sample/snippet.hpp
// コードの切れ端

// 座標圧縮。昇順に0から番号を付ける。
template<class T> map<T, int> coord_comp(set<T> s) {
	int a = 0;
	map<T, int> m;
	for (auto u : s) m[u] = a++;
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

// 偏角 [0, 2pi) の大きい順。順位は0から。原点は末尾。同じ方向は座標順。
// 座標の絶対値10^9以下。通常の反時計回りソートはmath/geometry.hppも参照。
map<pint, lint> polar_sort(vp v) {
    sort(all(v), [](const pint& a, const pint& b) {
        bool az = a.first == 0 && a.second == 0;
        bool bz = b.first == 0 && b.second == 0;
        if (az || bz) return !az && bz;
        auto half = [](const pint& p) { return p.second < 0 || (p.second == 0 && p.first < 0); };
        if (half(a) != half(b)) return half(a) > half(b);
        __int128 cross = __int128(a.first)*b.second - __int128(b.first)*a.second;
        if (cross != 0) return cross < 0;
        return a < b;
    });
    map<pint, lint> result;
    lint index = 0;
    for (auto p : v) if (!result.count(p)) result[p] = index++;
    return result;
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

// pair second sort
bool compare_second(pint a, pint b) {
	if (a.second != b.second) return a.second < b.second;
	return a.first < b.first;
}
