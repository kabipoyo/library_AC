// https://github.com/kabipoyo/library_AC/blob/master/structure/lis.hpp
#pragma once
#include <algorithm>
#include <vector>

namespace cp_lis {
struct Result {
	int length;
	std::vector<int> indices, ending_length;
};
// strict=true: 狭義増加、false: 非減少。復元は元配列の0-indexed添字。
// 入力は変更しない。最適解の辞書順などは保証しない。O(N log N)、空入力可。
template<class T> Result solve(const std::vector<T>& a, bool strict = true) {
	std::vector<T> tails;
	std::vector<int> last, previous(a.size(), -1), lengths(a.size());
	for (int i = 0; i < (int)a.size(); ++i) {
		int k = strict ? std::lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin()
					   : std::upper_bound(tails.begin(), tails.end(), a[i]) - tails.begin();
		if (k) previous[i] = last[k-1];
		if (k == (int)tails.size()) { tails.push_back(a[i]); last.push_back(i); }
		else { tails[k] = a[i]; last[k] = i; }
		lengths[i] = k+1;
	}
	std::vector<int> indices;
	for (int i = last.empty() ? -1 : last.back(); i != -1; i = previous[i]) indices.push_back(i);
	std::reverse(indices.begin(), indices.end());
	return {(int)tails.size(), indices, lengths};
}
}
