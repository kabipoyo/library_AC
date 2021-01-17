using pint = pair<int, int>;
using vp = vector<pint>;
vector<string> wall(int H, int W, char c) {
	string a, b(W + 2, c);
	vector<string> v;
	v.push_back(b);
	rep(i, H) { cin >> a; v.push_back(c + a + c); }
	v.push_back(b);
	return v;
}

int bfs(vector<string> &v, int H, int W) {
	int dx[4] = {-1, 0, 1, 0};
	int dy[4] = {0, -1, 0, 1};
	int a=0, x, y, z;
	queue<pint> Q;
	vvi m(H+2, vi(W+2));
	Q.push(make_pair(1, 1)), m[1][1] = 1;
	while (!Q.empty()) {
		tie(x, y) = Q.front();
		z = m[x][y];
		if (x == H && y == W) { a = z; break; }
		Q.pop();
		rep(i, 4) {
			if (v[x+dx[i]][y+dy[i]] == '.' && m[x+dx[i]][y+dy[i]] == 0) {
				Q.push(make_pair(x+dx[i], y+dy[i]));
				m[x+dx[i]][y+dy[i]] = z+1;
			}
		}
	}
	return a-1;
}

int main() {
	int H, W;
	cin >> H >> W;
	vector<string> v = wall(H, W, '#');
	int h = H+2, w = W+2;

	int a=0, b=0, c=0, x, y, z;
	cout << bfs(v, H, W) << '\n';
}
