// 10進法での各桁の和を求める
int sum_digits(lint N) {
	string s = to_string(N);
	int x = 0;
	rep(i, s.size()) x += s[i]-'0';
	return x;
}

// 16進数文字を10進数の数値で返す
int hex2dec(char c) {
	if (c >= '0' && c <= '9') return c-'0';
	else return 10+c-'A';
}
