// https://github.com/kabipoyo/library_AC/blob/master/graph/kruskal.hpp
// 最小全域木（非連結なら森）の重み。頂点は0-indexed。
template<typename T> struct edge {
	int from, to;
	T cost;
};

// 入力の辺配列は変更しない。非連結なら最小全域森の重みを返す。
template<typename T> T kruskal(const vector<edge<T>> &input, int V) {
	assert(V >= 0);
	auto edges = input;
	for (const auto &e : edges) assert(0 <= e.from && e.from < V && 0 <= e.to && e.to < V);
	sort(edges.begin(), edges.end(), [](const edge<T> &a, const edge<T> &b) {
		return a.cost < b.cost;
	});
	dsu d(V);
	T res = 0;
	for (edge<T> &e: edges) {
		if (!d.same(e.to, e.from)) {
			res += e.cost;
			d.merge(e.to, e.from);
		}
	}
	return res;
}
