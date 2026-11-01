// https://github.com/kabipoyo/library_AC/blob/master/sample/wall.hpp
#define mp make_pair
using pint = pair<int, int>;
using vp = vector<pint>;
vector<string> wall(int H, int W, char c) {
	assert(H >= 0 && W >= 0);
	string a, b(W + 2, c);
	vector<string> v;
	v.push_back(b);
	rep(i, H) { a.clear(); if (W > 0) cin >> a; assert(a.size() == W); v.push_back(c + a + c); }
	v.push_back(b);
	return v;
}

// 利用者の座標は0-indexed。壁付き配列への+1変換は内部で行う。
// 既定は(0,0)から(H-1,W-1)。到達不能はLINF。
lint bfs(const vector<string> &v, int H, int W, pint start = {0, 0}, optional<pint> goal = nullopt) {
	assert(H >= 0 && W >= 0 && v.size() == H+2);
	for (const auto &row : v) assert(row.size() == W+2);
	if (H == 0 || W == 0) return LINF;
	pint finish = goal.value_or(pint{H-1, W-1});
	assert(0 <= start.first && start.first < H && 0 <= start.second && start.second < W);
	assert(0 <= finish.first && finish.first < H && 0 <= finish.second && finish.second < W);
	if (v[start.first+1][start.second+1] != '.' || v[finish.first+1][finish.second+1] != '.') return LINF;
	int dx[4] = {-1, 0, 1, 0};
	int dy[4] = {0, -1, 0, 1};
	lint x, y;
	queue<pint> Q;
	vector<vector<lint>> m(H+2, vi(W+2, LINF));
	Q.push({start.first+1, start.second+1}); m[start.first+1][start.second+1] = 0;
	while (!Q.empty()) {
		tie(x, y) = Q.front(); Q.pop();
		if (x == finish.first+1 && y == finish.second+1) return m[x][y];
		rep(i, 4) {
			lint nx = x+dx[i], ny = y+dy[i];
			if (1 <= nx && nx <= H && 1 <= ny && ny <= W && v[nx][ny] == '.' && m[nx][ny] == LINF) {
				Q.push({nx, ny}); m[nx][ny] = m[x][y]+1;
			}
		}
	}
	return LINF;
}

int main() {
	lint H, W;
	cin >> H >> W;
	vector<string> v = wall(H, W, '#');
	lint h = H+2, w = W+2;

	lint a=0, b=0, c=0, x, y, z;
	lint distance = bfs(v, H, W);
	cout << (distance == LINF ? -1 : distance) << '\n';
}
