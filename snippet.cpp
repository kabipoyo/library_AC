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
template<class T> inline int binary_search_min(vector<T> *v, int key) {
	int ng = -1, mid, ok = v->size();
	while (abs(ok - ng) > 1) {
		mid = (ok + ng) / 2;
		if (v->at(mid) >= key) ok = mid;
		else ng = mid;
	}
	return ok;
}

// key 以下の最大の値がある要素番号を返す
template<class T> inline int binary_search_max(vector<T> *v, int key) {
	int ok = -1, mid, ng = v->size();
	while (abs(ok - ng) > 1) {
		mid = (ok + ng) / 2;
		if (v->at(mid) <= key) ok = mid;
		else ng = mid;
	}
	return ok;
}
