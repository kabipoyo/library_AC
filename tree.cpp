
/* tree_diamiter : bfs を用いて木の直径を求める
	計算量: O(N)
*/
#define mp make_pair
using pint = pair<int, int>;
vector<int> dist;
int bfs(int root) {
	int a=-1, b=0, x, y, N = G.size();
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
	return x;
}
pair<int, int> tree_diamiter() {
	int p = bfs(0);
	int q = bfs(p);
	return make_pair(p, q);
}

// オイラーツアー
// 各ノードについて部分木を抽出する
vector<int> in;
vector<int> out;
int tour = 0;
void rec(int root) {
	in[root] = tour;
	tour++;
	for (auto n : G[root]) rec(n);
	out[root] = tour;
	tour++;
	return;
}
void euler_tour(int root) {
	int N = G.size();
	in.resize(N, -1);
	out.resize(N, -1);
	return rec(root);
}
