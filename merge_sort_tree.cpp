const int MAX = 262144;

// Constructs a segment tree and stores sTree[]
void buildTree(int idx, int ss, int se, vi a[], vi sTree[]) {
	/*leaf node*/
	if (ss == se) {
		sTree[idx] = a[ss];
		return;
	}

	int mid = (ss + se) / 2;

	/* building left subtree */
	buildTree(2 * idx + 1, ss, mid, a, sTree);

	/* building right subtree */
	buildTree(2 * idx + 2, mid + 1, se, a, sTree);

	/* merging left and right child in sorted order */
	merge(sTree[2 * idx + 1].begin(),
		  sTree[2 * idx + 1].end(),
		  sTree[2 * idx + 2].begin(),
		  sTree[2 * idx + 2].end(),
		  back_inserter(sTree[idx]));
}

// Recursive function to count smaller elements from row
// a[ss] to a[se] and value smaller than or equal to k.
lint queryRec(int node, int start, int end, int ss, int se, int k, vi a[], vi sTree[]) {
	/* If out of range return 0 */
	if (ss > end || start > se)
		return 0;

	/* if inside the range return count */
	if (ss <= start && se >= end) {
		/* binary search over the sorted vector
		to return count >= X */
		return upper_bound(sTree[node].begin(), sTree[node].end(), k) - sTree[node].begin();
	}

	int mid = (start + end) / 2;

	/*searching in left subtree*/
	lint p1 = queryRec(2 * node + 1, start, mid, ss, se, k, a, sTree);

	/*searching in right subtree*/
	lint p2 = queryRec(2 * node + 2, mid + 1, end, ss, se, k, a, sTree);

	/*adding both the result*/
	return p1 + p2;
}

// A wrapper over query().
lint query(int start, int end, int k, vi a[], int n, vi sTree[]) {
	return queryRec(0, 0, n - 1, start, end, k, a, sTree);
}

vi v(N);
vin(v);
vi A[N];
rep(i, N) A[i].pb(v[i]);
vi T[MAX];
buildTree(0, 0, N-1, A, T);
