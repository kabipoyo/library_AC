// https://github.com/kabipoyo/library_AC/blob/master/structure/prefix_sum.hpp
#pragma once
#include <cassert>
#include <vector>
namespace cp_prefix_sum {
// 静的な区間和。[l,r)、0-indexed。和・差の中間結果もT内。
template<class T> class PrefixSum {
	std::vector<T> prefix;
public:
	explicit PrefixSum(const std::vector<T>& a) : prefix(a.size()+1, T{}) {
		for (int i=0; i<(int)a.size(); ++i) prefix[i+1]=prefix[i]+a[i];
	}
	T sum(int l, int r) const {
		assert(0<=l && l<=r && r<(int)prefix.size());
		return prefix[r]-prefix[l];
	}
	int size() const { return (int)prefix.size()-1; }
};
}
