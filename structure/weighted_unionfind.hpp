// https://github.com/kabipoyo/library_AC/blob/master/structure/weighted_unionfind.hpp
// 重み付きUnionFind。merge(x, y, z): potential[y] - potential[x] = z。
// 矛盾する制約はfalse。sizeは連結成分の要素数。lintが必要。
// 経路圧縮 + union by size。各操作は償却 O(alpha(N))。
struct WeightedUnionFind {
	vector<int> d;
	vector<lint> w;
	WeightedUnionFind(int n=0): d(n, -1), w(n, 0) {}
	int find(int x) {
		if (d[x] < 0) return x;
		int p = d[x], r = find(p);
		w[x] += w[p];
		return d[x] = r;
	}
	bool merge(int x, int y, lint z) {
		int rx = find(x), ry = find(y);
		if (rx == ry) return w[y] - w[x] == z;
		z += w[x] - w[y];
		if (d[rx] > d[ry]) { swap(rx, ry); z = -z; }
		d[rx] += d[ry]; d[ry] = rx; w[ry] = z;
		return true;
	}
	bool same(int x, int y) { return find(x) == find(y); }
	int size(int x) { return -d[find(x)]; }
	lint diff(int x, int y) {
		assert(same(x, y));
		return w[y] - w[x];
	}
};
