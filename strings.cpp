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

// N進法展開
long long base_to_long(string N, int base) {
	long long res = 0;
	for (int i = 0; i < N.size(); ++i) {
		res = res * base + int(N[i] - '0');
	}
	return res;
}
string long_to_base(long long N, int base) {
	if (N == 0) {
		return "0";
	}
	string res;
	while (N > 0) {
		res = char(N % base + '0') + res;
		N /= base;
	}
	return res;
}
