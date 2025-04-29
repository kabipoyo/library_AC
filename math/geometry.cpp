
struct Point {
	lint px, py;
};
Point operator+(const Point& a1, const Point& a2) {
	return Point{ a1.px + a2.px, a1.py + a2.py };
}
Point operator-(const Point& a1, const Point& a2) {
	return Point{ a1.px - a2.px, a1.py - a2.py };
}
bool operator<(const Point& a1, const Point& a2) {
	if (a1.px < a2.px) return true;
	if (a1.px > a2.px) return false;
	if (a1.py < a2.py) return true;
	return false;
}
bool operator==(const Point& a1, const Point& a2) {
	return (a1.px == a2.px && a1.py == a2.py);
}
// 点 p1 と p2 の外積を求める
lint crs(Point p1, Point p2) {
	return p1.px * p2.py - p1.py * p2.px;
}

// 三角形の面積の２倍を求める（実際の面積は半分にすること）
lint calc_triangle(Point p1, Point p2, Point p3) {
	return abs(crs(p3 - p1, p2 - p1));
}

// 凸包を得る
vector<Point> get_convex_hull(vector<Point> v) {
	v.pb({0, 0});
	sort(all(v));
	vector<Point> g1, g2, convex_hull;
	g1.pb(v[1]); g2.pb(v[1]);
	g1.pb(v[2]); g2.pb(v[2]);
	repx(i, 3, v.size()) {
		while (g1.size() >= 2 && crs(g1[g1.size()-1] - g1[g1.size()-2], v[i] - g1[g1.size()-1]) <= 0) g1.pop_back();
		while (g2.size() >= 2 && crs(g2[g2.size()-1] - g2[g2.size()-2], v[i] - g2[g2.size()-1]) >= 0) g2.pop_back();
		g1.pb(v[i]); g2.pb(v[i]);
	}
	for (auto p : g1) convex_hull.pb(p);
	g2.pop_back(); reverse(all(g2)); g2.pop_back();
	for (auto p : g2) convex_hull.pb(p);
	return convex_hull;
}

constexpr double PI=3.14159265358979323846;
#define deg_to_rad(deg) (((deg)/360)*2*PI)
#define rad_to_deg(rad) (((rad)/2/PI)*360)
double get_degree(Point p1, Point p2) {
	lint x = p2.px - p1.px;
	lint y = p2.py - p1.py;
	double d = atan2(y, x);
	if (d < 0) d += PI*2;
	return rad_to_deg(d);
}
