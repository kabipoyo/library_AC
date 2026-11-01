// https://github.com/kabipoyo/library_AC/blob/master/graph/Warshall_Floyd.hpp

// 無向・非負重み。update_distも同じ前提。有限距離はLINF未満。
vvi dist;
// 入力は既定で0-indexed。1-indexed入力なら第3引数に1。
void Floyd_Warshall(lint N, lint M, int input_base = 0) {
	assert(N >= 0 && M >= 0 && (input_base == 0 || input_base == 1));
	dist.assign(N, vi(N, LINF));
	lint x, y, z;
	rep(i, N) {
		rep(j, N) {
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = LINF;
		}
	}
	rep(i, M) {
		cin >> x >> y >> z;
		x -= input_base; y -= input_base;
		assert(0 <= x && x < N && 0 <= y && y < N);
		chmin(dist[x][y], z);
		chmin(dist[y][x], z);
	}
	rep(k, N) {
		rep(i, N) {
			rep(j, N) {
				if (dist[i][k] != LINF && dist[k][j] != LINF && dist[i][k] < LINF - dist[k][j])
					chmin(dist[i][j], dist[i][k]+dist[k][j]);
			}
		}
	}
}

void update_dist(lint N, int s, int t, lint C) {
	bool f = false;
	if (chmin(dist[s][t], C)) f = true;
	if (chmin(dist[t][s], C)) f = true;
	if (f) {
		for (int k : {s, t}) {
			rep(i, N) {
				rep(j, N) {
					if (dist[i][k] != LINF && dist[k][j] != LINF && dist[i][k] < LINF - dist[k][j])
						chmin(dist[i][j], dist[i][k]+dist[k][j]);
				}
			}
		}
	}
}
