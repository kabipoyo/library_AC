#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef int64_t lint;
#define rep(i, n) for(lint i=0; i<n; i++)
#define repx(i, l, n) for(lint i=l; i<n; i++)
#define all(v) v.begin(), v.end()
#define show(x) cout << #x << ": " << x << endl;
#define list(x) cout << #x << ": " << x << "  ";
#define pb push_back
using vi = vector<lint>;
using vvi = vector<vector<lint>>;
template<class T> inline void vin(vector<T>& v) { rep(i, v.size()) cin >> v.at(i); }
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
template<class T> inline void drop(T x) { cout << x << endl; exit(0); }
template<class T> void vout(vector<T> v) { rep(i, v.size()) { cout << v.at(i) << ' '; } cout << endl; }
constexpr lint LINF = LLONG_MAX/2;

int main() {
	lint N;
	cin >> N;
	vi v(N);
	vin(v);

	lint a=0, b=0, c=0, x, y, z;
}
