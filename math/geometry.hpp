#pragma once

typedef int64_t lint;
using pint = pair<lint, lint>;

struct Point {
	lint px, py;
};

Point operator+(const Point& a, const Point& b) {
	return {a.px+b.px, a.py+b.py};
}
Point operator-(const Point& a, const Point& b) {
	return {a.px-b.px, a.py-b.py};
}
Point operator*(const Point& a, lint k) {
	return {a.px*k, a.py*k};
}
bool operator<(const Point& a, const Point& b) {
	if (a.px != b.px) return a.px < b.px;
	return a.py < b.py;
}
bool operator==(const Point& a, const Point& b) {
	return a.px == b.px && a.py == b.py;
}
bool operator!=(const Point& a, const Point& b) {
	return !(a == b);
}

// 内積
lint dot(Point a, Point b) {
	return a.px*b.px+a.py*b.py;
}

// 外積
lint crs(Point a, Point b) {
	return a.px*b.py-a.py*b.px;
}

// ベクトルの長さの2乗
lint norm2(Point a) {
	return dot(a, a);
}

// 2点間距離の2乗
lint dist2(Point a, Point b) {
	return norm2(a-b);
}

int sgn(lint x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

// a -> b -> c の向き
// 1: 反時計回り
// -1: 時計回り
// 0: 一直線
int orientation(Point a, Point b, Point c) {
	return sgn(crs(b-a, c-a));
}

// 三角形の面積の2倍
lint calc_triangle(Point a, Point b, Point c) {
	return abs(crs(b-a, c-a));
}

// 3点が一直線上か
bool collinear(Point a, Point b, Point c) {
	return crs(b-a, c-a) == 0;
}

// 4点が一直線上か
bool collinear(Point a, Point b, Point c, Point d) {
	return collinear(a, b, c) && collinear(a, b, d);
}

// 2ベクトルが平行か
bool parallel(Point a, Point b) {
	return crs(a, b) == 0;
}

// 2ベクトルが垂直か
bool perpendicular(Point a, Point b) {
	return dot(a, b) == 0;
}

// 点 p が線分 ab 上にあるか
bool on_segment(Point a, Point b, Point p) {
	if (orientation(a, b, p) != 0) return false;

	return min(a.px, b.px) <= p.px
		&& p.px <= max(a.px, b.px)
		&& min(a.py, b.py) <= p.py
		&& p.py <= max(a.py, b.py);
}

// 2本の線分が共有点を持つか
bool segments_intersect(Point a, Point b, Point c, Point d) {
	int ab_c=orientation(a, b, c);
	int ab_d=orientation(a, b, d);
	int cd_a=orientation(c, d, a);
	int cd_b=orientation(c, d, b);

	if (ab_c == 0 && on_segment(a, b, c)) return true;
	if (ab_d == 0 && on_segment(a, b, d)) return true;
	if (cd_a == 0 && on_segment(c, d, a)) return true;
	if (cd_b == 0 && on_segment(c, d, b)) return true;

	return ab_c*ab_d < 0 && cd_a*cd_b < 0;
}

// 2直線 ab, cd が平行か
bool lines_parallel(Point a, Point b, Point c, Point d) {
	return crs(b-a, d-c) == 0;
}

// 2直線 ab, cd が同一直線か
bool same_line(Point a, Point b, Point c, Point d) {
	return lines_parallel(a, b, c, d)
		&& crs(b-a, c-a) == 0;
}

// 中点の2倍
// 中点が半整数でも正確に扱える
Point midpoint_twice(Point a, Point b) {
	return a+b;
}

// 2線分の中点が同じか
bool same_midpoint(Point a, Point b, Point c, Point d) {
	return a+b == c+d;
}

// 角 abc が鋭角か
bool acute_angle(Point a, Point b, Point c) {
	return dot(a-b, c-b) > 0;
}

// 角 abc が直角か
bool right_angle(Point a, Point b, Point c) {
	return dot(a-b, c-b) == 0;
}

// 角 abc が鈍角か
bool obtuse_angle(Point a, Point b, Point c) {
	return dot(a-b, c-b) < 0;
}

struct Line {
	// ax+by=c
	lint a, b, c;
};

// 異なる2点 p, q を通る直線
Line line_through(Point p, Point q) {
	lint a=q.py-p.py;
	lint b=p.px-q.px;
	lint c=a*p.px+b*p.py;

	return {a, b, c};
}

// 点 p を通り、方向ベクトル dir を持つ直線
Line line_from_direction(Point p, Point dir) {
	lint a=-dir.py;
	lint b=dir.px;
	lint c=a*p.px+b*p.py;

	return {a, b, c};
}

// 点 p を通り、normal を法線ベクトルに持つ直線
Line line_from_normal(Point p, Point normal) {
	lint a=normal.px;
	lint b=normal.py;
	lint c=a*p.px+b*p.py;

	return {a, b, c};
}

// 線分 pq の垂直二等分線
// p != q が必要
Line perpendicular_bisector(Point p, Point q) {
	lint a=2*(q.px-p.px);
	lint b=2*(q.py-p.py);
	lint c=q.px*q.px+q.py*q.py-p.px*p.px-p.py*p.py;

	return {a, b, c};
}

// 点 p が直線 l 上にあるか
bool on_line(Line l, Point p) {
	return l.a*p.px+l.b*p.py == l.c;
}

// 2直線が平行か
bool lines_parallel(Line l1, Line l2) {
	return l1.a*l2.b == l1.b*l2.a;
}

// 2直線が同一直線か
bool same_line(Line l1, Line l2) {
	return l1.a*l2.b == l1.b*l2.a
		&& l1.a*l2.c == l1.c*l2.a
		&& l1.b*l2.c == l1.c*l2.b;
}

struct PointD {
	long double px, py;
};

// 2直線の交点
// 平行なら nullopt
optional<PointD> line_intersection(Line l1, Line l2) {
	lint det=l1.a*l2.b-l2.a*l1.b;
	if (det == 0) return nullopt;

	lint x_num=l1.c*l2.b-l2.c*l1.b;
	lint y_num=l1.a*l2.c-l2.a*l1.c;

	return PointD{
		(long double)x_num/det,
		(long double)y_num/det
	};
}

// 4点で指定された2直線の交点
optional<PointD> line_intersection(Point a, Point b, Point c, Point d) {
	return line_intersection(line_through(a, b), line_through(c, d));
}

// 線分同士が一点で交わる場合の交点
// 重なる場合は nullopt
optional<PointD> segment_intersection_point(Point a, Point b, Point c, Point d) {
	if (!segments_intersect(a, b, c, d)) return nullopt;

	Line l1=line_through(a, b);
	Line l2=line_through(c, d);

	if (lines_parallel(l1, l2)) return nullopt;

	return line_intersection(l1, l2);
}

long double distance(Point a, Point b) {
	return sqrtl((long double)dist2(a, b));
}

// 点 p と直線 ab の距離
long double distance_point_line(Point p, Point a, Point b) {
	long double numerator=abs((long double)crs(b-a, p-a));
	long double denominator=sqrtl((long double)norm2(b-a));

	return numerator/denominator;
}

// 点 p と線分 ab の距離
long double distance_point_segment(Point p, Point a, Point b) {
	Point ab=b-a;

	if (dot(ab, p-a) <= 0) return distance(p, a);
	if (dot(a-b, p-b) <= 0) return distance(p, b);

	return distance_point_line(p, a, b);
}

// 点 p の直線 ab への射影
PointD projection(Point p, Point a, Point b) {
	Point ab=b-a;
	long double t=(long double)dot(p-a, ab)/norm2(ab);

	return {
		a.px+t*ab.px,
		a.py+t*ab.py
	};
}

// 2点間のマンハッタン距離
lint manhattan_distance(Point a, Point b) {
	return abs(a.px-b.px)+abs(a.py-b.py);
}

// マンハッタン距離の45度回転
pint rotate_45_degree(lint x, lint y) {
	return {x-y, x+y};
}

pint rotate_45_degree(Point p) {
	return {p.px-p.py, p.px+p.py};
}

// 45度回転後のチェビシェフ距離
lint manhattan_distance_rotated(Point a, Point b) {
	auto [ax, ay]=rotate_45_degree(a);
	auto [bx, by]=rotate_45_degree(b);

	return max(abs(ax-bx), abs(ay-by));
}

constexpr long double PI=acosl(-1.0L);

long double deg_to_rad(long double degree) {
	return degree*PI/180.0L;
}

long double rad_to_deg(long double radian) {
	return radian*180.0L/PI;
}

long double get_radian(Point from, Point to) {
	long double x=to.px-from.px;
	long double y=to.py-from.py;
	long double rad=atan2l(y, x);

	if (rad < 0) rad+=2.0L*PI;

	return rad;
}

long double get_degree(Point from, Point to) {
	return rad_to_deg(get_radian(from, to));
}

// 正のx軸から反時計回りの偏角ソート
int argument_half(Point p) {
	if (p.py > 0) return 0;
	if (p.py == 0 && p.px >= 0) return 0;
	return 1;
}

bool argument_cmp(const Point& a, const Point& b) {
	int ah=argument_half(a);
	int bh=argument_half(b);

	if (ah != bh) return ah < bh;

	lint cross=crs(a, b);
	if (cross != 0) return cross > 0;

	return norm2(a) < norm2(b);
}

void argument_sort(vector<Point>& points) {
	sort(all(points), argument_cmp);
}
