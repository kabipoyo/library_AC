// https://github.com/kabipoyo/library_AC/blob/master/structure/fenwick_2d.hpp
#pragma once
#include <cassert>
#include <vector>
// アルゴリズム参考: アルゴリズムロジック https://algo-logic.info/binary-indexed-tree/
// 外部0-indexed・半開区間へ変更。内部のみ1-indexed。
namespace cp_fenwick_2d {
template<class T> class Fenwick2D {
	int h_, w_;
	std::vector<std::vector<T>> bit;
public:
	Fenwick2D(int h, int w) { init(h,w); }
	void init(int h, int w) {
		assert(h>=0 && w>=0); h_=h; w_=w;
		bit.assign(h+1,std::vector<T>(w+1,T{}));
	}
	void add(int row, int col, T delta) {
		assert(0<=row && row<h_ && 0<=col && col<w_);
		for (int i=row+1; i<=h_; i+=i&-i)
			for (int j=col+1; j<=w_; j+=j&-j) bit[i][j]+=delta;
	}
	// [0,h) x [0,w)。両端は0..height()/width()。
	T prefix_sum(int h, int w) const {
		assert(0<=h && h<=h_ && 0<=w && w<=w_);
		T result{};
		for (int i=h; i>0; i-=i&-i)
			for (int j=w; j>0; j-=j&-j) result+=bit[i][j];
		return result;
	}
	T sum(int top, int left, int bottom, int right) const {
		assert(0<=top && top<=bottom && bottom<=h_);
		assert(0<=left && left<=right && right<=w_);
		return prefix_sum(bottom,right)-prefix_sum(top,right)-prefix_sum(bottom,left)+prefix_sum(top,left);
	}
	int height() const { return h_; }
	int width() const { return w_; }
};
}
