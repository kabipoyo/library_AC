// 行列累乗
// 行列 A^k を O(A^3logk) で求める
// base.hppのmintとvmを使用（必要なら法を変更）。
using vvm = vector<vector<mint>>;
vvm matrix_mul(vvm A, vvm B) {
	assert(!A.empty() && !B.empty() && A[0].size() == B.size());
	vvm C(A.size(), vm(B[0].size()));
	rep(i, A.size()) {
		rep(k, B.size()) {
			rep(j, B[0].size()) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}
vvm matrix_pow(vvm A, lint k) {
	assert(k >= 0 && !A.empty() && A.size() == A[0].size());
	vvm B(A.size(), vm(A.size()));
	rep(i, A.size()) B[i][i] = 1;
	while (k > 0) {
		if (k & (lint)1) B = matrix_mul(B, A);
		A = matrix_mul(A, A);
		k >>= 1;
	}
	return B;
}

