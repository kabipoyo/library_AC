// https://github.com/kabipoyo/library_AC/blob/master/graph/make_weighted_graph.hpp
// 重み付きグラフ。辺は {行き先, 重み}、入力は既定で0-indexed。
// make_graph.hpp、bellman.hppのグラフ宣言・生成とは同時にコピーしない。
vector<vector<pair<lint, lint>>> G, R;
// 有向が既定。無向なら make_dist_graph(N, M, true)。
void make_dist_graph(lint N, lint M, bool undirected = false, int input_base = 0) {
	assert(N >= 0 && M >= 0 && (input_base == 0 || input_base == 1));
	G.assign(N, {}); R.assign(N, {});
	rep(i, M) {
		lint x, y, z; cin >> x >> y >> z; x -= input_base; y -= input_base;
		assert(0 <= x && x < N && 0 <= y && y < N);
		G[x].push_back({y, z});
		if (undirected) G[y].push_back({x, z});
	}
}
// 有向のGと、その逆向きのRを同時に生成。
void make_round_graph(lint N, lint M, int input_base = 0) {
	make_dist_graph(N, M, false, input_base);
	rep(x, N) for (auto [to, cost] : G[x]) R[to].push_back({x, cost});
}
// 重みの入力がない無向グラフを、全辺の重み1として生成。
void make_unit_graph(lint N, lint M, int input_base = 0) {
	assert(N >= 0 && M >= 0 && (input_base == 0 || input_base == 1));
	G.assign(N, {}); R.assign(N, {});
	rep(i, M) {
		lint x, y; cin >> x >> y; x -= input_base; y -= input_base;
		assert(0 <= x && x < N && 0 <= y && y < N);
		G[x].push_back({y, 1}); G[y].push_back({x, 1});
	}
}
