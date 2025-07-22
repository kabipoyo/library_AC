/**
 * @brief Mo's Algorithm：Q個のクエリに対してO(N√Q)でソートする（ソート関数のルールに入れる）
 *
 * @details 以下の条件を満たすと適用できる
 * 1. 配列の要素が不変
 * 2. クエリを先読みできる
 * 3. 区間[l, r)の結果から、区間[l±1, r)や[l, r±1)の結果を容易に計算できる
 *
 * 区間状のクエリをソートできる
 * https://ei1333.hateblo.jp/entry/2017/09/11/211011
 *
 * 計算量：O(N√Q)
 *
 * 使い方：
M = max((lint)1, N/max((lint)sqrt(Q), (lint)1));
sort(all(p), func);
 */
#pragma once
#include "base.hpp"
int M;  //分割するひとつひとつの区間サイズ
bool func(const tuple<lint, lint, lint>& lhs, const tuple<lint, lint, lint>& rhs) {
	lint a, b, c, x, y, z;
	tie(a, b, c) = lhs;
	tie(x, y, z) = rhs;
	if (a / M < x / M) return true;
	if (a / M == x / M && b < y) return true;
	return false;
}

int M;  //分割するひとつひとつの区間サイズ
bool func(const pair<int, int>& lhs, const pair<int, int>& rhs) {
	if (lhs.first / M < rhs.first / M) return true;
	if (lhs.first / M == rhs.first / M && lhs.second < rhs.second) return true;
	return false;
}
