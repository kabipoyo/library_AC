// https://github.com/kabipoyo/library_AC/blob/master/graph/topo_sort.hpp
// Gは有向・重みなし。閉路があると結果は全頂点を含まない。
vi topo_sort() {
	vi res;
	lint N = G.size();
	vi v(N);
	rep(i, N) { for (auto e : G[i]) v[e]++; }
	queue<int> Q;
	rep(i, N) { if (!v[i]) Q.push(i); }
	while (!Q.empty()) {
		int x = Q.front(); Q.pop();
		res.push_back(x);
		for (auto e : G[x]) {
			v[e]--;
			if (!v[e]) Q.push(e);
		}
	}
	return res;
}
