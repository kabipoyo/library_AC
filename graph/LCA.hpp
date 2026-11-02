// https://github.com/kabipoyo/library_AC/blob/master/graph/LCA.hpp
// 連結な無向木Gの最小共通祖先。頂点・rootは0-indexed。
struct LCA {
	vector<vector<int>> parent;  // parent[k][u]:= u の 2^k 先の親
	vector<int> dist;			// root からの距離
	LCA(int root = 0) { init(root); }
	// 初期化
	void init(int root = 0) {
		int V = G.size();
		assert(V > 0 && 0 <= root && root < V);
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
	// 無向木専用。明示スタックで深い木でも再帰を使わない。
	void dfs(int v, int p, int d) {
		vector<int> stack = {v}; parent[0][v] = p; dist[v] = d;
		while (!stack.empty()) {
			int x = stack.back(); stack.pop_back();
			for (int to : G[x]) if (to != parent[0][x]) {
				parent[0][to] = x; dist[to] = dist[x]+1; stack.push_back(to);
			}
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
