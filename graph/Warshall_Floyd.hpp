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
		assert(0 <= x && x < N && 0 <= y && y < N && 0 <= z && z < LINF);
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

// 構築済みの無向・非負重みの距離表へ1辺を追加/短縮。Nは構築時と同じ。
// 更新前の2列を保存してO(N^2)で更新する。補助空間O(N)。削除・重み増加は不可。
void update_dist(lint N, int s, int t, lint C) {
	assert(N>=0 && N==(lint)dist.size());
	assert(0<=s && s<N && 0<=t && t<N && 0<=C && C<LINF);
	for (const auto& row:dist) { assert((lint)row.size()==N); }
	if (C>=dist[s][t]) return;
	vi to_s(N), to_t(N);
	rep(i,N) { to_s[i]=dist[i][s]; to_t[i]=dist[i][t]; }
	auto add=[](lint a, lint b) -> lint {
		return a>=LINF-b ? LINF : a+b;
	};
	rep(i,N) rep(j,N) {
		chmin(dist[i][j],add(add(to_s[i],C),to_t[j]));
		chmin(dist[i][j],add(add(to_t[i],C),to_s[j]));
	}
}
