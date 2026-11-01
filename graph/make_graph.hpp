// https://github.com/kabipoyo/library_AC/blob/master/graph/make_graph.hpp
// 無向グラフ for bfs。入力は既定で0-indexed。
// 1-indexed入力なら make_graph(N,M,1) と明示する。
vector<vector<lint>> G;
void make_graph(lint N, lint M, int input_base = 0) {
	assert(N >= 0 && M >= 0 && (input_base == 0 || input_base == 1));
	G.assign(N, {});
	lint x, y;
	rep(i, M) {
		cin >> x >> y;
		x -= input_base; y -= input_base;
		assert(0 <= x && x < N && 0 <= y && y < N);
		G[x].push_back(y);
		G[y].push_back(x);
	}
}
// グラフ作成 for tree
void make_graph(lint N) {
	assert(N >= 1);
	make_graph(N, N-1);
}

// 重み付きグラフの生成は make_weighted_graph.hpp。
