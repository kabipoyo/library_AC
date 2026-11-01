/* tree_diameter : bfs を用いて木の直径を求める
	計算量: O(N)
*/
#define mp make_pair
using pint = pair<int, int>;
vector<int> dist;
int bfs(int root) {
	int a=root, b=0, x, y, N = G.size();
	dist.clear();
	dist.resize(N, -1);
	queue<int> Q;
	Q.push(root), dist[root] = 0;
	while (!Q.empty()) {
		x = Q.front(); Q.pop();
		rep(i, G[x].size()) {
			y = G[x][i];
			if (dist[y] == -1) { Q.push(y); dist[y] = dist[x]+1; }
		}
		if (chmax(b, dist[x])) a = x;
	}
	return a;
}
pair<int, int> tree_diameter() {
	if (G.empty()) return {-1, -1};
	int p = bfs(0);
	int q = bfs(p);
	return make_pair(p, q);
}
// 以前の呼び出し名との互換用。新規コードではtree_diameterを使用。
pair<int, int> tree_diamiter() { return tree_diameter(); }
