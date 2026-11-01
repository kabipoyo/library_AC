// https://github.com/kabipoyo/library_AC/blob/master/graph/make_graph.hpp
// 無向グラフ for bfs
vector<vector<lint>> G;
void make_graph(lint N, lint M) {
	G.assign(N, {});
	lint x, y;
	rep(i, M) {
		cin >> x >> y;
		x--, y--;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}
// グラフ作成 for tree
void make_graph(lint N) {
	G.assign(N, {});
	lint x, y;
	rep(i, N-1) {
		cin >> x >> y;
		x--, y--;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}

// 重み付きグラフの生成は make_weighted_graph.hpp。
