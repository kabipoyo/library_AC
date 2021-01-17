// 根付き木生成のための深さ探索

vi rooted_tree(vvi v) {
	queue<int> q;
	vi d(v.size()), u(v.size());
	q.push(0), u[0]++;
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
