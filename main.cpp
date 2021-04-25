
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

template<class T> inline void vvout(vector<T> v) {
	rep(i, v.size()) { rep(j, v[i].size()) { cout << v.at(i).at(j) << ' '; } cout << endl; }
}

// 小さい順の優先度付きキュー
priority_queue<int, vector<int>, greater<int>> q;

// 二分探索 O(logN)
auto l = lower_bound(all(v), key);
auto u = upper_bound(all(v), key);
// set型二分探索 O(logN)
auto l = s.lower_bound(key);
auto u = s.upper_bound(key);

// multiset １個だけ消去
s.erase(s.find(x));
// multiset 所属判定（countは x の要素数に対して線形時間かかる）
if (s.find(x) != s.end())

// インデックスを取得 O(N)
int idx_l = distance(v.begin(), iter_l);
int idx_u = distance(v.begin(), iter_u);

int main() {
	int N;
	cout << fixed << setprecision(10) << N << endl;
	cin >> N;
	int a=0, b=0, c=0, x, y, z;
}

template <typename T>
vector<T> make_v(size_t a) {
	return vector<T>(a);
}
template <typename T, typename... Ts>
auto make_v(size_t a, Ts... ts) {
	return vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}
