// https://github.com/kabipoyo/library_AC/blob/master/acl/basics.hpp
// ACL基本操作の参照用。必要なnamespaceだけコピー。0-indexed。
// 参考: https://atcoder.github.io/ac-library/production/document_ja/index.html
#pragma once
#include <atcoder/dsu>
#include <atcoder/modint>
#include <atcoder/string>
#include <atcoder/convolution>

namespace acl_dsu {
using DSU = atcoder::dsu;
// mergeの戻り値は代表頂点（成功boolではない）。併合の要否はsameで判定。
// DSU uf(n); uf.merge(u,v); bool connected=uf.same(u,v);
// int count=uf.size(u); int root=uf.leader(u); auto groups=uf.groups();
}

namespace acl_modint {
using Mint = atcoder::modint998244353;
using DynamicMint = atcoder::modint;
// pow(k)はk>=0、inv・除算は値と法が互いに素。
// set_mod(mod): 1<=mod<=2*10^9+1000。変更前の値は持ち越さない。
// Mint x=-3; auto value=x.val(); auto power=x.pow(k); auto inverse=x.inv();
// DynamicMint::set_mod(mod); DynamicMint y=5; set_modは値を作る前に行う。
}

namespace acl_string {
using atcoder::z_algorithm;
using atcoder::suffix_array;
using atcoder::lcp_array;
// lcp_arrayは空文字列不可。z_algorithmとsuffix_arrayは空でも可。
// auto z=z_algorithm(s); auto sa=suffix_array(s);
// auto lcp=lcp_array(s,sa); lcp[i]はs.substr(sa[i])とs.substr(sa[i+1])のLCP。
}

namespace acl_convolution {
using atcoder::convolution;
using atcoder::convolution_ll;
// 空入力の出力は空。非空時、既定法のconvolutionはn+m-1<=2^23、
// convolution_llはn+m-1<=2^24かつ各係数がlong long内。
// auto c=convolution(a,b); c[k]=sum(a[i]*b[j]) (i+j=k)。既定modは998244353。
// auto exact=convolution_ll(a,b); 整数の各係数がlong longに収まる入力で使う。
}
