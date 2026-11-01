// オイラーツアー
// 各ノードについて部分木を抽出する
vector<int> in;
vector<int> out;
int tour = 0;
set<lint> passed;
// 入・出の両方で時刻を進める方式。頂点だけの部分木配列とは区別する。
void rec(int root) {
    vector<pair<int, int>> stack = {{root, 0}};
    passed.insert(root); in[root] = tour++;
    while (!stack.empty()) {
        int v = stack.back().first;
        int &i = stack.back().second;
        if (i == (int)G[v].size()) { out[v] = tour++; stack.pop_back(); continue; }
        int to = G[v][i++];
        if (passed.insert(to).second) { in[to] = tour++; stack.push_back({to, 0}); }
    }
}
void euler_tour(int root) {
	int N = G.size();
	tour = 0; passed.clear();
	in.assign(N, -1);
	out.assign(N, -1);
	return rec(root);
}
