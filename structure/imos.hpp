// https://github.com/kabipoyo/library_AC/blob/master/structure/imos.hpp
#pragma once
#include <cassert>
#include <vector>
namespace cp_imos {
// オフライン区間加算。[l,r)、0-indexed。中間の差分・和もT内。
// buildは差分を変更しない。再build・build後の追加も可。返値は独立した配列。
template<class T> class Imos {
	int n_;
	std::vector<T> diff;
public:
	explicit Imos(int n) : n_(n) {
		assert(n>=0); diff.assign(n+1, T{});
	}
	void add(int l, int r, T value) {
		assert(0<=l && l<=r && r<=n_);
		if (l==r) return;
		diff[l]+=value; diff[r]-=value;
	}
	std::vector<T> build() const {
		std::vector<T> result(n_); T value{};
		for (int i=0; i<n_; ++i) { value+=diff[i]; result[i]=value; }
		return result;
	}
	int size() const { return n_; }
};
}
