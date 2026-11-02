// https://github.com/kabipoyo/library_AC/blob/master/structure/imos_2d.hpp
#pragma once
#include <cassert>
#include <vector>
namespace cp_imos_2d {
// 両軸とも0-indexed・半開区間。中間の差分・和もT内。
// buildは差分を変更しない。再build・build後の追加も可。
template<class T> class Imos2D {
	int h_, w_;
	std::vector<std::vector<T>> diff;
public:
	Imos2D(int h, int w) : h_(h), w_(w) {
		assert(h>=0 && w>=0); diff.assign(h+1, std::vector<T>(w+1, T{}));
	}
	void add(int top, int left, int bottom, int right, T value) {
		assert(0<=top && top<=bottom && bottom<=h_);
		assert(0<=left && left<=right && right<=w_);
		if (top==bottom || left==right) return;
		diff[top][left]+=value; diff[top][right]-=value;
		diff[bottom][left]-=value; diff[bottom][right]+=value;
	}
	std::vector<std::vector<T>> build() const {
		auto result=diff;
		for (int i=0; i<h_; ++i) for (int j=0; j<w_; ++j) {
			if (i) result[i][j]+=result[i-1][j];
			if (j) result[i][j]+=result[i][j-1];
			if (i && j) result[i][j]-=result[i-1][j-1];
		}
		result.resize(h_);
		for (auto& row: result) row.resize(w_);
		return result;
	}
	int height() const { return h_; }
	int width() const { return w_; }
};
}
