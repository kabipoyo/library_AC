// 無向グラフ for bfs
vector<vector<lint>> G;
void make_graph(lint N, lint M) {
	G.resize(N);
	lint x, y;
	rep(i, M) {
		cin >> x >> y;
		x--, y--;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}
// グラフ作成 for tree
vector<vector<lint>> G;
void make_graph(lint N) {
	G.resize(N);
	lint x, y;
	rep(i, N-1) {
		cin >> x >> y;
		x--, y--;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}

// 無向グラフ for dijkstra
vector<vector<pair<lint, lint>>> G;
void make_graph(lint N, lint M) {
	lint x, y;
	G.resize(N);
	rep(i, M) {
		cin >> x >> y;
		x--, y--;
		G[x].push_back(make_pair(1, y));
		G[y].push_back(make_pair(1, x));
	}
}

// 重みつきグラフを生成 片道
vector<vector<pair<lint, lint>>> G;
void make_dist_graph(lint N, lint M) {
	lint x, y, z;
	G.resize(N);
	rep(i, M) {
		cin >> x >> y >> z;
		x--, y--;
		G[x].push_back(make_pair(z, y));
	}
}

// 重みつきグラフ作成 往復可能
vector<vector<pair<lint, lint>>> G;
void make_dist_graph(int N, int M) {
	G.resize(N);
	lint x, y, z;
	rep(i, M) {
		cin >> x >> y >> z;
		x--, y--;
		G[x].push_back(make_pair(z, y));
		G[y].push_back(make_pair(z, x));
	}
}

// 重みつきグラフを行き・帰りで生成
vector<vector<pair<lint, lint>>> G;
vector<vector<pair<lint, lint>>> R;
void make_round_graph(lint N, lint M) {
	lint x, y, z;
	G.resize(N), R.resize(N);
	rep(i, M) {
		cin >> x >> y >> z;
		x--, y--;
		G[x].push_back(make_pair(z, y));
		R[y].push_back(make_pair(z, x));
	}
}
