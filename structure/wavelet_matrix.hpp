// https://github.com/kabipoyo/library_AC/blob/master/structure/wavelet_matrix.hpp
// 静的配列の区間[l,r)、順位kは0-indexed。prev/nextの不在はnullopt。
// 出典: ei1333 https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.hpp.html
#pragma once
#include "base.hpp"
// Wavelet Matrix内部のビット列。rank(k)は[0,k)の個数。
struct SuccinctIndexableDictionary {
	size_t length;
	size_t blocks;
	vector< unsigned > bit, sum;

	SuccinctIndexableDictionary() = default;

	SuccinctIndexableDictionary(size_t length) : length(length), blocks((length >> 5) + 1) {
		bit.assign(blocks, 0U);
		sum.assign(blocks, 0U);
	}

	void set(int k) {
		assert(0 <= k && k < length);
		bit[k >> 5] |= 1U << (k & 31);
	}

	void build() {
		sum[0] = 0U;
		for(int i = 1; i < blocks; i++) {
			sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]);
		}
	}

	bool operator[](int k) {
		assert(0 <= k && k < length);
		return (bool((bit[k >> 5] >> (k & 31)) & 1));
	}

	int rank(int k) {
		assert(0 <= k && k <= length);
		return (sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));
	}

	int rank(bool val, int k) {
		return (val ? rank(k) : k - rank(k));
	}
};

// 非圧縮版の値域は[0,2^MAXLOG)。
template< typename T, int MAXLOG >
struct WaveletMatrix {
	static_assert(0 < MAXLOG && MAXLOG <= numeric_limits<T>::digits);
	size_t length;
	SuccinctIndexableDictionary matrix[MAXLOG];
	int mid[MAXLOG];

	WaveletMatrix() = default;

	WaveletMatrix(vector< T > v) : length(v.size()) {
		for (T x : v) assert(x >= 0 && (__uint128_t)x < (__uint128_t(1) << MAXLOG));
		vector< T > l(length), r(length);
		for(int level = MAXLOG - 1; level >= 0; level--) {
			matrix[level] = SuccinctIndexableDictionary(length + 1);
			int left = 0, right = 0;
			for(int i = 0; i < length; i++) {
				if(((v[i] >> level) & 1)) {
					matrix[level].set(i);
					r[right++] = v[i];
				} else {
					l[left++] = v[i];
				}
			}
			mid[level] = left;
			matrix[level].build();
			v.swap(l);
			for(int i = 0; i < right; i++) {
				v[left + i] = r[i];
			}
		}
	}

	pair< int, int > succ(bool f, int l, int r, int level) {
		return {matrix[level].rank(f, l) + mid[level] * f, matrix[level].rank(f, r) + mid[level] * f};
	}

	// v[k]
	T access(int k) {
		assert(0 <= k && k < length);
		T ret = 0;
		for(int level = MAXLOG - 1; level >= 0; level--) {
			bool f = matrix[level][k];
			if(f) ret |= T(1) << level;
			k = matrix[level].rank(f, k) + mid[level] * f;
		}
		return ret;
	}

	T operator[](const int &k) {
		return access(k);
	}

	// count i s.t. (0 <= i < r) && v[i] == x
	int rank(const T &x, int r) {
		assert(0 <= r && r <= length);
		if (x < 0 || (__uint128_t)x >= (__uint128_t(1) << MAXLOG)) return 0;
		int l = 0;
		for(int level = MAXLOG - 1; level >= 0; level--) {
			tie(l, r) = succ((x >> level) & 1, l, r, level);
		}
		return r - l;
	}

	// k-th(0-indexed) smallest number in v[l,r)
	T kth_smallest(int l, int r, int k) {
		assert(0 <= l && l <= r && r <= length);
		assert(0 <= k && k < r - l);
		T ret = 0;
		for(int level = MAXLOG - 1; level >= 0; level--) {
			int cnt = matrix[level].rank(false, r) - matrix[level].rank(false, l);
			bool f = cnt <= k;
			if(f) {
				ret |= T(1) << level;
				k -= cnt;
			}
			tie(l, r) = succ(f, l, r, level);
		}
		return ret;
	}

	// k-th(0-indexed) largest number in v[l,r)
	T kth_largest(int l, int r, int k) {
		assert(0 <= k && k < r - l);
		return kth_smallest(l, r, r - l - k - 1);
	}

	// count i s.t. (l <= i < r) && (v[i] < upper)
	int range_freq(int l, int r, T upper) {
		assert(0 <= l && l <= r && r <= length);
		if (upper <= 0) return 0;
		if ((__uint128_t)upper >= (__uint128_t(1) << MAXLOG)) return r - l;
		int ret = 0;
		for(int level = MAXLOG - 1; level >= 0; level--) {
			bool f = ((upper >> level) & 1);
			if(f) ret += matrix[level].rank(false, r) - matrix[level].rank(false, l);
			tie(l, r) = succ(f, l, r, level);
		}
		return ret;
	}

	// count i s.t. (l <= i < r) && (lower <= v[i] < upper)
	int range_freq(int l, int r, T lower, T upper) {
		assert(lower <= upper);
		return range_freq(l, r, upper) - range_freq(l, r, lower);
	}

	// max v[i] s.t. (l <= i < r) && (v[i] < upper)
	optional<T> prev_value(int l, int r, T upper) {
		int cnt = range_freq(l, r, upper);
		if (cnt == 0) return nullopt;
		return kth_smallest(l, r, cnt - 1);
	}

	// min v[i] s.t. (l <= i < r) && (lower <= v[i])
	optional<T> next_value(int l, int r, T lower) {
		int cnt = range_freq(l, r, lower);
		if (cnt == r - l) return nullopt;
		return kth_smallest(l, r, cnt);
	}
};

// 圧縮版：異なる値の数 <= 2^MAXLOG。
template< typename T, int MAXLOG >
struct CompressedWaveletMatrix {
	WaveletMatrix< int, MAXLOG > mat;
	vector< T > ys;

	CompressedWaveletMatrix(const vector< T > &v) : ys(v) {
		sort(begin(ys), end(ys));
		ys.erase(unique(begin(ys), end(ys)), end(ys));
		vector< int > t(v.size());
		for(int i = 0; i < v.size(); i++) t[i] = get(v[i]);
		mat = WaveletMatrix< int, MAXLOG >(t);
	}

	inline int get(const T& x) {
		return lower_bound(begin(ys), end(ys), x) - begin(ys);
	}

	T access(int k) {
		return ys[mat.access(k)];
	}

	T operator[](const int &k) {
		return access(k);
	}

	int rank(const T &x, int r) {
		assert(0 <= r && r <= mat.length);
		auto pos = get(x);
		if(pos == ys.size() || ys[pos] != x) return 0;
		return mat.rank(pos, r);
	}

	T kth_smallest(int l, int r, int k) {
		return ys[mat.kth_smallest(l, r, k)];
	}

	T kth_largest(int l, int r, int k) {
		return ys[mat.kth_largest(l, r, k)];
	}

	int range_freq(int l, int r, T upper) {
		return mat.range_freq(l, r, get(upper));
	}

	int range_freq(int l, int r, T lower, T upper) {
		assert(lower <= upper);
		return mat.range_freq(l, r, get(lower), get(upper));
	}

	optional<T> prev_value(int l, int r, T upper) {
		auto ret = mat.prev_value(l, r, get(upper));
		if (!ret) return nullopt;
		return ys[*ret];
	}

	optional<T> next_value(int l, int r, T lower) {
		auto ret = mat.next_value(l, r, get(lower));
		if (!ret) return nullopt;
		return ys[*ret];
	}
};
