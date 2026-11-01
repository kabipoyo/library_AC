/* Rerooting: 全方位木 DP
	dpall[i][j]：ノードiのjから先にあるノード数を数える
	計算量: O(N log N)
*/
vi dp;
vector<map<lint, lint>> dpall;
// Gは連結な無向木。mapへの格納を含め O(N log N)。
void Rerooting() {
    int N = G.size(); dp.assign(N, 0); dpall.assign(N, {});
    if (N == 0) return;
    vector<int> parent(N, -1), order = {0};
    for (size_t i = 0; i < order.size(); ++i) {
        int v = order[i];
        for (int to : G[v]) if (to != parent[v]) { parent[to] = v; order.push_back(to); }
    }
    for (int i = N-1; i > 0; --i) dp[parent[order[i]]] += dp[order[i]]+1;
    for (int v : order) for (int to : G[v])
        dpall[v][to] = to == parent[v] ? N-dp[v]-1 : dp[to]+1;
}
