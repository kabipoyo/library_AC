// 強連結成分分解（SCC）
// 有向グラフをループ毎に分解する
// O(N+M)
vi used, route;
// 帰りがけ順を明示スタックで作る。再帰によるスタック枯渇を避ける。
void rec(int root) {
    vector<pair<int, int>> stack = {{root, 0}}; used[root] = 0;
    while (!stack.empty()) {
        int v = stack.back().first;
        int &i = stack.back().second;
        if (i == (int)G[v].size()) { route.push_back(v); stack.pop_back(); continue; }
        int to = G[v][i++];
        if (used[to] == -1) { used[to] = 0; stack.push_back({to, 0}); }
    }
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
	used.assign(N, -1);
	route.clear();
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
