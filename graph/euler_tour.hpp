// https://github.com/kabipoyo/library_AC/blob/master/graph/euler_tour.hpp
// オイラーツアー
// 各ノードについて部分木を抽出する
vector<int> in;
vector<int> out;
int tour = 0;
set<lint> passed;
// 訪問時だけ時刻を進める。部分木の頂点の入時刻は [in[v],out[v])。
void rec(int root) {
    vector<pair<int, int>> stack = {{root, 0}};
    passed.insert(root); in[root] = tour++;
    while (!stack.empty()) {
        int v = stack.back().first;
        int &i = stack.back().second;
        if (i == (int)G[v].size()) { out[v] = tour; stack.pop_back(); continue; }
        int to = G[v][i++];
        if (passed.insert(to).second) { in[to] = tour++; stack.push_back({to, 0}); }
    }
}
void euler_tour(int root) {
	int N = G.size();
	tour = 0; passed.clear();
	in.assign(N, -1);
	out.assign(N, -1);
	assert(0 <= root && root < N);
	return rec(root);
}
