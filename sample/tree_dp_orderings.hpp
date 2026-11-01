// https://atcoder.jp/contests/abc160/tasks/abc160_f
vi dp;
vm dpall;
// 頂点を根から順に並べる方法の数。Gは連結な無向木、mintの法はNより大きい素数。
void Rerooting() {
    int N = G.size(); dp.assign(N, 1); dpall.assign(N, 0);
    if (N == 0) return;
    vector<int> parent(N, -1), order = {0};
    for (size_t i = 0; i < order.size(); ++i) {
        int v = order[i];
        for (int to : G[v]) if (to != parent[v]) { parent[to] = v; order.push_back(to); }
    }
    for (int i = N-1; i > 0; --i) dp[parent[order[i]]] += dp[order[i]];
    dpall[0] = 1;
    for (int i = 1; i <= N; ++i) dpall[0] *= i;
    for (auto size : dp) dpall[0] /= size;
    for (int v : order) for (int to : G[v]) if (to != parent[v])
        dpall[to] = dpall[v] * dp[to] / (N-dp[to]);
}
