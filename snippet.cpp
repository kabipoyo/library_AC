// コードの切れ端

// 座標圧縮
template<class T> map<T, int> coord_comp(set<T> s) {
	int a = 0;
	map<T, int> m;
	for (auto u : s) m[u] = ++a;
	return m;
}

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

// 原点からの極座標の角度の大きい順に番号を付ける（0<=Θ<=π/2）
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

// Mo's Algorithm -- O(Nsqrt(Q))
// M = max((lint)1, N/max((lint)sqrt(Q), (lint)1));
// sort(all(p), func);
int M;  //分割するひとつひとつの区間サイズ
bool func(const tuple<lint, lint, lint>& lhs, const tuple<lint, lint, lint>& rhs) {
	lint a, b, c, x, y, z;
	tie(a, b, c) = lhs;
	tie(x, y, z) = rhs;
	if (a / M < x / M) return true;
	if (a / M == x / M && b < y) return true;
	return false;
}

int M;  //分割するひとつひとつの区間サイズ
bool func(const pair<int, int>& lhs, const pair<int, int>& rhs) {
	if (lhs.first / M < rhs.first / M) return true;
	if (lhs.first / M == rhs.first / M && lhs.second < rhs.second) return true;
	return false;
}
