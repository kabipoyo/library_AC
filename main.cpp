#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

typedef int64_t lint;

#define rep(i, n) for(int i=0; i<n; i++)

#define mp make_pair
using pint = pair<int, int>;
using vp = vector<pint>;
#define mt make_tuple
using tint = tuple<int, int, int>;
using vt = vector<tint>;

using mint = modint998244353;
using mint = modint1000000007;
using vm = vector<mint>;

constexpr double PI=3.14159265358979323846;
constexpr int INF = INT_MAX/2;
constexpr lint LINF = LLONG_MAX/2;

template<class T> inline void drop(T x) { cout << x << endl; exit(0); }

template<class T> inline void vecout(vector<T> v) {
	rep(i, v.size()) { cout << v.at(i) << ' '; } cout << endl;
}

template <typename T>
vector<T> make_v(size_t a) {
	return vector<T>(a);
}
template <typename T, typename... Ts>
auto make_v(size_t a, Ts... ts) {
	return vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}

int main() {
	int N;
	cout << fixed << setprecision(10) << N << endl;
	cin >> N;
	int a=0, b=0, c=0, x, y, z;
}
