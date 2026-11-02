// https://github.com/kabipoyo/library_AC/blob/master/acl/inversion_count.hpp
#pragma once
#include <atcoder/fenwicktree>
#include <algorithm>
#include <vector>

namespace acl_inversion_count {
// i<j かつ a[i]>a[j] の組数。同値は数えない。入力非破壊、O(N log N)。
// 答えはlong long内。比較は全順序（NaNなどを含めない）。
template<class T> long long count(const std::vector<T>& a) {
	std::vector<T> values = a;
	std::sort(values.begin(), values.end());
	values.erase(std::unique(values.begin(), values.end()), values.end());
	atcoder::fenwick_tree<long long> fw((int)values.size());
	long long answer = 0;
	for (int i=0; i<(int)a.size(); ++i) {
		int rank = std::lower_bound(values.begin(), values.end(), a[i]) - values.begin();
		answer += i - fw.sum(0, rank+1);
		fw.add(rank, 1);
	}
	return answer;
}
}
