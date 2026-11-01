// https://github.com/kabipoyo/library_AC/blob/master/graph/dijkstra_extended.hpp
// 拡張ダイクストラ（状態１：最短経路、状態２：最大化したい変数）
using ppint = pair<pint, lint>;
// Gは {加算する値, 行き先}。距離は辺数、同距離なら加算値を最大化。

void dijkstra(lint start, vector<pint> &dist) {
	lint N = G.size();
	lint a=0, b=0, c=0, x, y, z;
	pint p;
	dist.assign(N, {LINF, 0}); dist[start] = {0, 0};
	priority_queue<ppint, vector<ppint>, greater<ppint>> PQ;
	PQ.push(make_pair(make_pair(0, 0), start));
	while (!PQ.empty()) {
		tie(p, a) = PQ.top(); PQ.pop();
		tie(x, z) = p;
		if (dist[a].first < x) continue;
		if (dist[a].first == x && dist[a].second > z) continue;
		for (auto p : G[a]) {
			tie(y, b) = p;
			if (chmin(dist[b].first, x+1)) dist[b].second = z+y, PQ.push(make_pair(make_pair(x+1, z+y), b));
			else if (dist[b].first == x+1 && chmax(dist[b].second, z+y)) PQ.push(make_pair(make_pair(x+1, z+y), b));
		}
	}
}
