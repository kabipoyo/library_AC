// 強連結成分分解（SCC）
// 有向グラフをループ毎に分解する
// O(N+M)
vi used, route;
void rec(int x) {
	used[x]++;
	for (auto t : G[x]) {
		if (used[t] == -1) rec(t);
	}
	route.pb(x);
}
vi dfs(int x) {
	used[x]++;
	stack<lint> s;
	s.push(x);
	vi v;
	while (!s.empty()) {
		int z = s.top();
		v.pb(z); s.pop();
		for (auto t : R[z]) {
			if (used[t] == 0) {
				s.push(t);
				used[t]++;
			}
		}
	}
	return v;
}
vvi scc() {
	int N = G.size();
	used.resize(N, -1);
	rep(i, N) {
		if (used[i] == -1) rec(i);
	}
	reverse(all(route));
	vvi res;
	rep(i, N) {
		if (used[route[i]] == 0) res.pb(dfs(route[i]));
	}
	return res;
}
