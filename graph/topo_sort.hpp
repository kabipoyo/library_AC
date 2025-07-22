/* topo_sort(G): グラフG をトポロジカルソート
	返り値: トポロジカルソートされた頂点番号
	計算量: O(|E|+|V|)
*/
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
