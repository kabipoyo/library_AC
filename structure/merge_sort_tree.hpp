// https://github.com/kabipoyo/library_AC/blob/master/structure/merge_sort_tree.hpp
// 構築・問い合わせとも[l,r)。queryはk以下の個数を返す。空区間は0。
#pragma once
#include "base.hpp"
const int MAX = 262144;
void buildTree(int idx, int ss, int se, vi a[], vi sTree[]) {
	assert(0 <= ss && ss <= se);
	sTree[idx].clear();
	if (ss == se) return;
	/*leaf node*/
	if (se - ss == 1) {
		sTree[idx] = a[ss];
		return;
	}

	int mid = (ss + se) / 2;

	/* building left subtree */
	buildTree(2 * idx + 1, ss, mid, a, sTree);

	/* building right subtree */
	buildTree(2 * idx + 2, mid, se, a, sTree);

	/* merging left and right child in sorted order */
	merge(sTree[2 * idx + 1].begin(),
		  sTree[2 * idx + 1].end(),
		  sTree[2 * idx + 2].begin(),
		  sTree[2 * idx + 2].end(),
		  back_inserter(sTree[idx]));
}

lint queryRec(int node, int start, int end, int ss, int se, int k, vi a[], vi sTree[]) {
	/* If out of range return 0 */
	if (ss >= end || start >= se || ss == se)
		return 0;

	/* if inside the range return count */
	if (ss <= start && se >= end) {
		/* binary search over the sorted vector
		to return count <= k */
		return upper_bound(sTree[node].begin(), sTree[node].end(), k) - sTree[node].begin();
	}

	int mid = (start + end) / 2;

	/*searching in left subtree*/
	lint p1 = queryRec(2 * node + 1, start, mid, ss, se, k, a, sTree);

	/*searching in right subtree*/
	lint p2 = queryRec(2 * node + 2, mid, end, ss, se, k, a, sTree);

	/*adding both the result*/
	return p1 + p2;
}

lint query(int start, int end, int k, vi a[], int n, vi sTree[]) {
	assert(0 <= start && start <= end && end <= n);
	if (start == end) return 0;
	return queryRec(0, 0, n, start, end, k, a, sTree);
}
