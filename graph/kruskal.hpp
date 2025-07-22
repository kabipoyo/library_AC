/* Kruskal :クラスカル法で minimum spanning tree (最小全域木) を求める
	コストの和が最小になるように木を構築する
	入力: 辺のvector, 頂点数V
	最小全域木の重みの総和: res
	計算量: O(|E|log|E|)
*/

template<typename T> struct edge {
	int from, to;
	T cost;
};

template<typename T> T kruskal(vector<edge<T>> &edges, int V) {
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
