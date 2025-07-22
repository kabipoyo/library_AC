
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
		dist[x][y] = z;
		dist[y][x] = z;
	}
	rep(k, N) {
		rep(i, N) {
			rep(j, N) {
				chmin(dist[i][j], dist[i][k]+dist[k][j]);
			}
		}
	}
}
