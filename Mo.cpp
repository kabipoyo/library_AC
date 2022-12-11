
// Mo's Algorithm -- O(Nsqrt(Q))
// M = max((lint)1, N/max((lint)sqrt(Q), (lint)1));
// sort(all(p), func);
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
