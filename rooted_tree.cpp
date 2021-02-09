// 根付き木生成のための深さ探索
// bfs に移植済み
vector<int> rooted_tree(vector<vector<int>> v, int root) {
	queue<int> q;
	vector<int> d(v.size()), u(v.size());
	q.push(root), u[root]++;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		rep(i, v[x].size()) {
			int y = v[x][i];
			if (!u[y]) { q.push(y); u[y]++; d[y] = d[x]+1; }
		}
	}
	return d;
}
