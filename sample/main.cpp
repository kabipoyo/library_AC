
#define mp make_pair
#define mt make_tuple
using pint = pair<lint, lint>;
using vp = vector<pint>;
using tint = tuple<lint, lint, lint>;
using vt = vector<tint>;

using mint = modint1000000007;
using mint = modint998244353;
using vm = vector<mint>;

constexpr int INF = INT_MAX/2;
constexpr lint LINF = LLONG_MAX/2;

template<class T> inline void vvout(vector<T> v) {
	rep(i, v.size()) { rep(j, v[i].size()) { cout << v.at(i).at(j) << ' '; } cout << endl; }
}

// sqrt(lint)の精度は足りなくなるのでこれを使う
a = sqrtl(x);

// 小さい順の優先度付きキュー
priority_queue<lint, vector<lint>, greater<lint>> q;

// 二分探索 O(logN)
// v.begin() を引くと index
auto l = lower_bound(all(v), key);
auto u = upper_bound(all(v), key);
// set型二分探索 O(logN)
// prevとか使える
auto l = s.lower_bound(key);
auto u = s.upper_bound(key);

// multiset １個だけ消去
s.erase(s.find(x));
// multiset 所属判定（countは x の要素数に対して線形時間かかる）
if (s.find(x) != s.end())

// 1の数を数えるっぽい（符号なし整数型じゃないと合わない）
__builtin_popcount(bit);
// C++20以降は昇格
popcount(x);

// 2秒未満でやめる
int TIME=clock();
if (clock()-TIME > 1.98 * CLOCKS_PER_SEC) break;

// インデックスを取得 O(N)
int idx_l = distance(v.begin(), iter_l);
int idx_u = distance(v.begin(), iter_u);

// double 出力
cout << fixed << setprecision(10) << N << endl;

// ラジアンー度　変換
constexpr double PI=3.14159265358979323846;
#define deg_to_rad(deg) (((deg)/360)*2*PI)
#define rad_to_deg(rad) (((rad)/2/PI)*360)

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
	cin >> N;
	int a=0, b=0, c=0, x, y, z;
}
