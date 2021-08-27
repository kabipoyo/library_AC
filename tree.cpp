// グラフ作成
vector<vector<int>> G;
void make_graph(int N, int M) {
	G.resize(N);
	int x, y;
	rep(i, M) {
		cin >> x >> y;
		x--, y--;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}


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


/* LCA(root): 木 G に対する根を root として Lowest Common Ancestor を求める構造体
	query(u,v): u と v の LCA を求める。計算量 O(logn)
	前処理: O(nlogn)時間, O(nlogn)空間
*/
struct LCA {
	vector<vector<int>> parent;  // parent[k][u]:= u の 2^k 先の親
	vector<int> dist;			// root からの距離
	LCA(int root = 0) { init(root); }
	// 初期化
	void init(int root = 0) {
		int V = G.size();
		int K = 1;
		while ((1 << K) < V) K++;
		parent.assign(K, vector<int>(V, -1));
		dist.assign(V, -1);
		dfs(root, -1, 0);
		for (int k = 0; k + 1 < K; k++) {
			for (int v = 0; v < V; v++) {
				if (parent[k][v] < 0) {
					parent[k + 1][v] = -1;
				} else {
					parent[k + 1][v] = parent[k][parent[k][v]];
				}
			}
		}
	}
	// 根からの距離と1つ先の頂点を求める
	void dfs(int v, int p, int d) {
		parent[0][v] = p;
		dist[v] = d;
		for (auto e : G[v]) {
			if (e != p) dfs(e, v, d + 1);
		}
	}
	int query(int u, int v) {
		if (dist[u] < dist[v]) swap(u, v);  // u の方が深いとする
		int K = parent.size();
		// LCA までの距離を同じにする
		for (int k = 0; k < K; k++) {
			if ((dist[u] - dist[v]) >> k & 1) {
				u = parent[k][u];
			}
		}
		// 二分探索で LCA を求める
		if (u == v) return u;
		for (int k = K - 1; k >= 0; k--) {
			if (parent[k][u] != parent[k][v]) {
				u = parent[k][u];
				v = parent[k][v];
			}
		}
		return parent[0][u];
	}
};
