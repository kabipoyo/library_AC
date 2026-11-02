// https://github.com/kabipoyo/library_AC/blob/master/structure/prefix_sum_2d.hpp
#pragma once
#include <cassert>
#include <vector>

namespace cp_prefix_sum_2d {
// 静的な矩形和。0-indexed、両軸とも半開区間。和・差はT内に収まること。
template<class T> class PrefixSum2D {
	int h_, w_;
	std::vector<std::vector<T>> prefix;
public:
	explicit PrefixSum2D(const std::vector<std::vector<T>>& a)
		: h_((int)a.size()), w_(a.empty() ? 0 : (int)a[0].size()),
		  prefix(h_+1, std::vector<T>(w_+1, T{})) {
		for (int i=0; i<h_; ++i) {
			assert((int)a[i].size() == w_);
			for (int j=0; j<w_; ++j)
				prefix[i+1][j+1] = prefix[i][j+1] + prefix[i+1][j] - prefix[i][j] + a[i][j];
		}
	}
	// [top,bottom) x [left,right)。空矩形は0。
	T sum(int top, int left, int bottom, int right) const {
		assert(0 <= top && top <= bottom && bottom <= h_);
		assert(0 <= left && left <= right && right <= w_);
		return prefix[bottom][right] - prefix[top][right] - prefix[bottom][left] + prefix[top][left];
	}
	int height() const { return h_; }
	int width() const { return w_; }
};
}
