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
