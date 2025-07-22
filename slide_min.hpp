template< typename T > vector<T> slide_min(const vector<T> &v, int k) {
	deque<int> q;
	vector<T> ret;
	rep(i, v.size()) {
		while (!q.empty() && v[q.back()] >= v[i]) {
			q.pop_back();
		}
		q.push_back(i);
		if (i-k+1 >= 0) {
			ret.emplace_back(v[q.front()]);
			if (q.front() == i-k+1) q.pop_front();
		}
	}
	return ret;
}
