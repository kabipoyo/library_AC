// https://github.com/kabipoyo/library_AC/blob/master/acl/fenwick.hpp
// ACL Fenwick Treeの初期化。0-indexed、sum(l,r)は[l,r)。
// 参考: https://atcoder.github.io/ac-library/production/document_ja/fenwicktree.html
#pragma once
#include <atcoder/fenwicktree>
#include <vector>

namespace acl_fenwick {
using Tree = atcoder::fenwick_tree<long long>;
inline Tree make_tree(const std::vector<long long>& values) {
    Tree tree((int)values.size());
    for (int i = 0; i < (int)values.size(); ++i) tree.add(i, values[i]);
    return tree;
}
// Tree fw(n); は全要素0。fw.add(p,delta); auto sum = fw.sum(l,r);
// 代入はfw.add(p,new_value-fw.sum(p,p+1));（差もlong long内）。
}
