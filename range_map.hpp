class SegmentMap : public map<lint, lint> {
private:
	bool flagToMergeAdjacentSegment;
public:
	// if merge [l, c] and [c+1, r], set flagToMergeAdjacentSegment to true
	SegmentMap(bool flagToMergeAdjacentSegment) :
		flagToMergeAdjacentSegment(flagToMergeAdjacentSegment) {}
	// __exist -> iterator pair(l, r) (contain p)
	// noexist -> map.end()
	auto get(lint p) const {
		auto it = upper_bound(p);
		if (it == begin() || (--it)->second < p) return end();
		return it;
	}
	// insert segment [l, r]
	void insert(lint l, lint r) {
		auto itl = upper_bound(l), itr = upper_bound(r + flagToMergeAdjacentSegment);
		if (itl != begin()) {
			if ((--itl)->second < l - flagToMergeAdjacentSegment) ++itl;
		}
		if (itl != itr) {
			l = min(l, itl->first);
			r = max(r, prev(itr)->second);
			erase(itl, itr);
		}
		(*this)[l] = r;
	}
	// remove segment [l, r]
	void remove(lint l, lint r) {
		auto itl = upper_bound(l), itr = upper_bound(r);
		if (itl != begin()) {
			if ((--itl)->second < l) ++itl;
		}
		if (itl == itr) return;
		int tl = min(l, itl->first), tr = max(r, prev(itr)->second);
		erase(itl, itr);
		if (tl < l) (*this)[tl] = l - 1;
		if (r < tr) (*this)[r + 1] = tr;
	}
	// Is p and q in same segment?
	bool same(lint p, lint q) const {
		const auto&& it = get(p);
		return it != end() && it->first <= q && q <= it->second;
	}
};


// コンストラクタ．隣接区間をマージする
SegmentMap map(true);

// iを含む区間[l, r]のstd::map<int,int>::const_iteratorを返す, iを含む区間が無ければmap.end()を返す
// it->first, it->second でアクセス
auto it = map.get(i);

// 区間[l, r]を挿入する
map.insert(l, r);

// 全区間で[l, r]に重なる部分を全て消す
map.remove(l, r);

// iとjが同じ区間に属しているかのbool値を返す
bool f = map.same(i, j);
