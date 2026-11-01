// 重み付きグラフ。辺は {重み, 行き先}、入力は1-indexed。
// make_graph.hpp、bellman.hppのグラフ宣言・生成とは同時にコピーしない。
vector<vector<pair<lint, lint>>> G, R;
// 有向が既定。無向なら make_dist_graph(N, M, true)。
void make_dist_graph(lint N, lint M, bool undirected = false) {
    G.assign(N, {}); R.assign(N, {});
    rep(i, M) {
        lint x, y, z; cin >> x >> y >> z; --x; --y;
        G[x].push_back({z, y});
        if (undirected) G[y].push_back({z, x});
    }
}
// 有向のGと、その逆向きのRを同時に生成。
void make_round_graph(lint N, lint M) {
    make_dist_graph(N, M);
    rep(x, N) for (auto [cost, to] : G[x]) R[to].push_back({cost, x});
}
// 重みの入力がない無向グラフを、全辺の重み1として生成。
void make_unit_graph(lint N, lint M) {
    G.assign(N, {}); R.assign(N, {});
    rep(i, M) {
        lint x, y; cin >> x >> y; --x; --y;
        G[x].push_back({1, y}); G[y].push_back({1, x});
    }
}
