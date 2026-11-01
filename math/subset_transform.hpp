// https://github.com/kabipoyo/library_AC/blob/master/math/subset_transform.hpp
// ゼータ・メビウス変換。入力配列vを書き換えるin-place操作。
template<class T> void zeta_transform(vector<T> &v, int s) {
	assert(0 <= s && s < 31 && v.size() == (size_t(1) << s));
	rep(i, s) {
		rep(j, 1<<s) {
			if (((j >> i) & 1) == 0) {
				v[j | (1<<i)] += v[j];
			}
		}
	}
}

template<class T> void mobius_transform(vector<T> &v, int s) {
	assert(0 <= s && s < 31 && v.size() == (size_t(1) << s));
	rep(i, s) {
		rep(j, 1<<s) {
			if (((j >> i) & 1) == 0) {
				v[j | (1<<i)] -= v[j];
			}
		}
	}
}

