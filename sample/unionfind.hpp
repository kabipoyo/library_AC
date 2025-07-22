struct UnionFind {
	vector<int> d;
	UnionFind(int n=0): d(n,-1) {}
	int find(int x) {
		if (d[x] < 0) return x;
		return d[x] = find(d[x]);
	}
	bool unite(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return false;
		if (d[x] > d[y]) swap(x,y);
		d[x] += d[y];
		d[y] = x;
		return true;
	}
	bool same(int x, int y) { return find(x) == find(y);}
	int size(int x) { return -d[find(x)];}
};

struct WeightedUnionFind {
	vector<int> d;
	vector<lint> w;
	WeightedUnionFind(int n=0): d(n, 0), w(n, 0) {
		rep(i, n) d[i] = i;
	}
	int find(int x) {
		if (d[x] == x) return x;
		int r = find(d[x]);
		w[x] += w[d[x]];
		return d[x] = r;
	}
	bool merge(int x, int y, lint z) {
		int rx = find(x), ry = find(y);
		if (rx == ry) return w[y]-w[x] == z;
		d[rx] = ry;
		w[rx] = w[y]-w[x]-z;
		return true;
	}
	bool same(int x, int y) { return find(x) == find(y);}
	int size(int x) { return -d[find(x)];}
};
