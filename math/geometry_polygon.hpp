#pragma once

// geometry_basic.hpp を先に読み込むこと

// 凸包
// 一直線上の途中の点は除外する
// 結果は反時計回り
vector<Point> get_convex_hull(vector<Point> v) {
	sort(all(v));
	v.erase(unique(all(v)), v.end());

	int n=v.size();
	if (n <= 1) return v;

	vector<Point> lower, upper;

	rep(i, n) {
		while (lower.size() >= 2) {
			int m=lower.size();

			if (crs(
				lower[m-1]-lower[m-2],
				v[i]-lower[m-1]
			) > 0) break;

			lower.pop_back();
		}

		lower.pb(v[i]);
	}

	for (int i=n-1; i>=0; i--) {
		while (upper.size() >= 2) {
			int m=upper.size();

			if (crs(
				upper[m-1]-upper[m-2],
				v[i]-upper[m-1]
			) > 0) break;

			upper.pop_back();
		}

		upper.pb(v[i]);
	}

	lower.pop_back();
	upper.pop_back();

	for (Point p : upper) lower.pb(p);

	return lower;
}

// 多角形の符号付き面積の2倍
// 反時計回りなら正
lint polygon_area2_signed(const vector<Point>& polygon) {
	lint res=0;
	int n=polygon.size();

	rep(i, n) {
		res+=crs(polygon[i], polygon[(i+1)%n]);
	}

	return res;
}

// 多角形の面積の2倍
lint polygon_area2(const vector<Point>& polygon) {
	return abs(polygon_area2_signed(polygon));
}

// 多角形が反時計回りか
bool is_counterclockwise(const vector<Point>& polygon) {
	return polygon_area2_signed(polygon) > 0;
}

// 単純多角形と点の包含関係
// 0: 外部
// 1: 境界上
// 2: 内部
int point_in_polygon(const vector<Point>& polygon, Point p) {
	bool inside=false;
	int n=polygon.size();

	rep(i, n) {
		Point a=polygon[i]-p;
		Point b=polygon[(i+1)%n]-p;

		if (crs(a, b) == 0 && dot(a, b) <= 0) {
			return 1;
		}

		if (a.py > b.py) swap(a, b);

		if (a.py <= 0 && 0 < b.py && crs(a, b) > 0) {
			inside=!inside;
		}
	}

	return inside ? 2 : 0;
}

// 反時計回りの凸多角形と点の包含関係
// O(log N)
// 0: 外部
// 1: 境界上
// 2: 内部
int point_in_convex_polygon(const vector<Point>& polygon, Point p) {
	int n=polygon.size();

	if (n == 0) return 0;
	if (n == 1) return polygon[0] == p ? 1 : 0;
	if (n == 2) {
		return on_segment(polygon[0], polygon[1], p) ? 1 : 0;
	}

	Point origin=polygon[0];

	lint left=crs(polygon[1]-origin, p-origin);
	lint right=crs(polygon[n-1]-origin, p-origin);

	if (left < 0 || right > 0) return 0;

	if (left == 0) {
		return on_segment(origin, polygon[1], p) ? 1 : 0;
	}

	if (right == 0) {
		return on_segment(origin, polygon[n-1], p) ? 1 : 0;
	}

	int low=1;
	int high=n-1;

	while (high-low > 1) {
		int mid=(low+high)/2;

		if (crs(polygon[mid]-origin, p-origin) >= 0) {
			low=mid;
		} else {
			high=mid;
		}
	}

	lint cross=crs(
		polygon[high]-polygon[low],
		p-polygon[low]
	);

	if (cross < 0) return 0;
	if (cross == 0) return 1;
	return 2;
}

struct CircleD {
	PointD center;
	long double radius;
};

// 点 p が円周上にあるか
bool on_circle(Point p, Point center, lint radius2) {
	return dist2(p, center) == radius2;
}

// 点と円の位置関係
// -1: 円の内部
// 0: 円周上
// 1: 円の外部
int point_circle_relation(Point p, Point center, lint radius2) {
	return sgn(dist2(p, center)-radius2);
}

// 4点が同一円周上にあるか
// a, b, c が一直線なら false
bool concyclic(Point a, Point b, Point c, Point d) {
	if (collinear(a, b, c)) return false;

	lint ax=a.px-d.px;
	lint ay=a.py-d.py;
	lint bx=b.px-d.px;
	lint by=b.py-d.py;
	lint cx=c.px-d.px;
	lint cy=c.py-d.py;

	lint a2=ax*ax+ay*ay;
	lint b2=bx*bx+by*by;
	lint c2=cx*cx+cy*cy;

	lint det=
		ax*(by*c2-b2*cy)
		-ay*(bx*c2-b2*cx)
		+a2*(bx*cy-by*cx);

	return det == 0;
}

// 3点を通る円
// 3点が一直線上なら nullopt
optional<CircleD> circumcircle(Point a, Point b, Point c) {
	long double ax=a.px;
	long double ay=a.py;
	long double bx=b.px;
	long double by=b.py;
	long double cx=c.px;
	long double cy=c.py;

	long double d=2.0L*(
		ax*(by-cy)
		+bx*(cy-ay)
		+cx*(ay-by)
	);

	if (d == 0.0L) return nullopt;

	long double a2=ax*ax+ay*ay;
	long double b2=bx*bx+by*by;
	long double c2=cx*cx+cy*cy;

	long double ux=(
		a2*(by-cy)
		+b2*(cy-ay)
		+c2*(ay-by)
	)/d;

	long double uy=(
		a2*(cx-bx)
		+b2*(ax-cx)
		+c2*(bx-ax)
	)/d;

	long double radius=hypotl(ux-ax, uy-ay);

	return CircleD{
		{ux, uy},
		radius
	};
}
