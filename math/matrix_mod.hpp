// mod を指定するタイプ
vvi matrix_mul(vvi A, vvi B, lint M) {
	assert(M >= 1 && !A.empty() && !B.empty() && A[0].size() == B.size());
	vvi C(A.size(), vi(B[0].size()));
	rep(i, A.size()) {
		rep(k, B.size()) {
			rep(j, B[0].size()) {
				C[i][j] = (__int128(C[i][j]) + __int128(A[i][k]) * B[k][j]) % M;
				if (C[i][j] < 0) C[i][j] += M;
			}
		}
	}
	return C;
}
vvi matrix_pow(vvi A, lint k, lint M) {
	assert(M >= 1 && k >= 0 && !A.empty() && A.size() == A[0].size());
	vvi B(A.size(), vi(A.size()));
	rep(i, A.size()) B[i][i] = 1 % M;
	while (k > 0) {
		if (k & (lint)1) B = matrix_mul(B, A, M);
		A = matrix_mul(A, A, M);
		k >>= 1;
	}
	return B;
}
