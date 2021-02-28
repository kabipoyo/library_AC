// 10進法での各桁の和を求める
int sum_digits(lint N) {
	string s = to_string(N);
	int x = 0;
	rep(i, s.size()) x += s[i]-'0';
	return x;
}
