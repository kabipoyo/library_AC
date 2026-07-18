
vvi dist(10000, vi(10000));
void Floyd_Warshall(lint N, lint M) {
	lint x, y, z;
	rep(i, N) {
		rep(j, N) {
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = LINF;
		}
	}
	rep(i, M) {
		cin >> x >> y >> z;
		x--, y--;
		chmin(dist[x][y], z);
		chmin(dist[y][x], z);
	}
	rep(k, N) {
		rep(i, N) {
			rep(j, N) {
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
					chmin(dist[i][j], dist[i][k]+dist[k][j]);
				}
			}
		}
	}
}
