#pragma once
#include <bits/stdc++.h>
#include <atcoder/all>

// 競プロ用・簡易確率／期待値ユーティリティ集
// double でも atcoder::modint 系でも同じコードで使えるように
// テンプレート化してあります（T は +,-,*,/ が定義されている型）。
// 必要に応じて namespace prob 直下へ追加してください。

namespace prob {
using namespace std;
using namespace atcoder;

//----------------------------------------
// 内部ヘルパ―：1 と 0 の型依存定義
//----------------------------------------

template<class T> inline T _one() { return T(1); }
template<> inline double _one<double>() { return 1.0; }

template<class T> inline T _zero() { return T(0); }
template<> inline double _zero<double>() { return 0.0; }

//----------------------------------------
// 汎用累乗 (log exp)
//----------------------------------------

template<class T>
T ipow(T base, long long exp) {
	T res = _one<T>();
	while (exp) {
		if (exp & 1LL) res *= base;
		base *= base;
		exp >>= 1LL;
	}
	return res;
}

//----------------------------------------
// 幾何分布／負の二項分布
//----------------------------------------

// 期待試行回数：初成功まで (Geom, E[X] = 1/p)
template<class T>
T geom_exp(T p) {
	return _one<T>() / p;
}

// 分散：Geom, Var[X] = (1-p)/p^2
template<class T>
T geom_var(T p) {
	T q = _one<T>() - p;
	return q / (p * p);
}

// 期待試行回数：k 回成功まで (NegBin, E[X] = k/p)
template<class T>
T negbin_exp(long long k, T p) {
	return T(k) / p;
}

//----------------------------------------
// 組合せ (nCk) 前計算クラス
//----------------------------------------

template<class T>
struct Comb {
	std::vector<T> fact, ifact;
	Comb(int n = 0) { if (n) init(n); }
	void init(int n) {
		fact.resize(n + 1);
		ifact.resize(n + 1);
		fact[0] = _one<T>();
		for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * T(i);
		ifact[n] = _one<T>() / fact[n];
		for (int i = n; i >= 1; i--) ifact[i - 1] = ifact[i] * T(i);
	}
	T operator()(int n, int k) const {
		if (k < 0 || k > n) return _zero<T>();
		return fact[n] * ifact[k] * ifact[n - k];
	}
};

//----------------------------------------
// 分布関係関数
//----------------------------------------

// Binomial PMF: P(X=k)
template<class T>
T binom_pmf(int n, int k, T p, const Comb<T>& C) {
	if (k < 0 || k > n) return _zero<T>();
	return C(n, k) * ipow(p, k) * ipow(_one<T>() - p, n - k);
}

// Binomial CDF: P(X<=k)
template<class T>
T binom_cdf(int n, int k, T p, const Comb<T>& C) {
	T s = _zero<T>();
	for (int i = 0; i <= k; i++) s += binom_pmf(n, i, p, C);
	return s;
}

// Hypergeometric PMF: P(X=k)
template<class T>
T hypergeom_pmf(int N, int K, int n, int k, const Comb<T>& C) {
	if (k < 0 || k > n || k > K || n - k > N - K) return _zero<T>();
	return C(K, k) * C(N - K, n - k) / C(N, n);
}

//----------------------------------------
// クーポンコレクター期待値 (全部集めるまで)
//----------------------------------------

template<class T>
T coupon_exp(int n) {
	T res = _zero<T>();
	for (int i = 1; i <= n; i++) res += _one<T>() / T(i);
	return res * T(n);
}

//----------------------------------------
// 任意確率ベクトルで「初ヒット」期待回数  (多項幾何)
//----------------------------------------
// probs はヒット確率の配列（和は <=1）。残りは "ミス" として扱う。
// 戻り値: 期待手数 (失敗確率 <1 であることが前提)

template<class T>
T multi_geom_exp(const std::vector<T>& probs) {
	T ps = _zero<T>();
	for (auto p : probs) ps += p;
	return _one<T>() / ps;
}

} // namespace prob
