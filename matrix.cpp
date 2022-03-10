// 行列累乗
// 行列 A^k を O(A^3logk) で求める
using mint = modint998244353;
using mint = modint1000000007;
using vm = vector<mint>;
using vvm = vector<vector<mint>>;
vvm matrix_mul(vvm A, vvm B) {
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
	vvm B(A.size(), vm(A.size()));
	rep(i, A.size()) B[i][i] = 1;
	while (k > 0) {
		if (k & (lint)1) B = matrix_mul(B, A);
		A = matrix_mul(A, A);
		k >>= 1;
	}
	return B;
}

// mod を指定するタイプ
vvi matrix_mul(vvi A, vvi B, lint M) {
	vvi C(A.size(), vi(B[0].size()));
	rep(i, A.size()) {
		rep(k, B.size()) {
			rep(j, B[0].size()) {
				C[i][j] += A[i][k] * B[k][j];
				C[i][j] %= M;
			}
		}
	}
	return C;
}
vvi matrix_pow(vvi A, lint k, lint M) {
	vvi B(A.size(), vi(A.size()));
	rep(i, A.size()) B[i][i] = 1;
	while (k > 0) {
		if (k & (lint)1) B = matrix_mul(B, A, M);
		A = matrix_mul(A, A, M);
		k >>= 1;
	}
	return B;
}
