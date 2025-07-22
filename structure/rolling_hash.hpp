/**
 * @brief 文字列の一致判定を高速に行う
 *
 * @tparam mod 1000000007などを入れる
 * @author ei1333
 * @details https://ei1333.github.io/luzhiled/snippets/string/rolling-hash.html
 *
 * 使い方：
 * using RH = RollingHash< 1000000007 >;
 * RH rh(S);
 *
 * get：区間[l, r)のハッシュ値を得る
 * x = rh.get(l, r);
 *
 * connect：ハッシュ値 h1, 長さ h2len のハッシュ値 h2 を結合する
 * x = rh.connect(h1, h2, len);
 *
 * LCP：区間[l1, r1)とハッシュテーブルが b の区間[l2, r2)の最長共通接頭辞の長さを求める
 * x = rh.LCP(rhb, l1, r1, l2, r2);
 *
 * 計算量：
 * 構築		O(N)
 * get		O(1)
 * connect	O(1)
 * LCP		O(logN)
 */
template< unsigned mod >
struct RollingHash {
	vector< unsigned > hashed, power;

	inline unsigned mul(unsigned a, unsigned b) const {
		unsigned long long x = (unsigned long long) a * b;
		unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
		asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (mod));
		return m;
	}

	RollingHash(const string &s, unsigned base = 10007) {
		int sz = (int) s.size();
		hashed.assign(sz + 1, 0);
		power.assign(sz + 1, 0);
		power[0] = 1;
		for(int i = 0; i < sz; i++) {
			power[i + 1] = mul(power[i], base);
			hashed[i + 1] = mul(hashed[i], base) + s[i];
			if(hashed[i + 1] >= mod) hashed[i + 1] -= mod;
		}
	}

	unsigned get(int l, int r) const {
		unsigned ret = hashed[r] + mod - mul(hashed[l], power[r - l]);
		if(ret >= mod) ret -= mod;
		return ret;
	}

	unsigned connect(unsigned h1, int h2, int h2len) const {
		unsigned ret = mul(h1, power[h2len]) + h2;
		if(ret >= mod) ret -= mod;
		return ret;
	}

	int LCP(const RollingHash< mod > &b, int l1, int r1, int l2, int r2) {
		int len = min(r1 - l1, r2 - l2);
		int low = -1, high = len + 1;
		while(high - low > 1) {
			int mid = (low + high) / 2;
			if(get(l1, l1 + mid) == b.get(l2, l2 + mid)) low = mid;
			else high = mid;
		}
		return (low);
	}
};

using RH = RollingHash< 1000000007 >;
