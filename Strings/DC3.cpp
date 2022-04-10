#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
    Normie's implementation of DC3 suffix array, version 1.0.
    This algorithm uses differnce cover samples to construct the suffix array of a string
    recursively in O(n) time.
    Tested with Library-Checker (https://judge.yosupo.jp/submission/85528).
*/
// Standard library in one include.
#include <bits/stdc++.h>
using namespace std;
 
// ordered_set library.
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set(el) tree<el,null_type,less<el>,rb_tree_tag,tree_order_statistics_node_update>
 
// AtCoder library. (Comment out these two lines if you're not submitting in AtCoder.) (Or if you want to use it in other judges, run expander.py first.)
//#include <atcoder/all>
//using namespace atcoder;
 
//Pragmas (Comment out these three lines if you're submitting in szkopul.)
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,unroll-loops,tree-vectorize")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
 
//File I/O.
#define FILE_IN "cseq.inp"
#define FILE_OUT "cseq.out"
#define ofile freopen(FILE_IN,"r",stdin);freopen(FILE_OUT,"w",stdout)
 
//Fast I/O.
#define fio ios::sync_with_stdio(0);cin.tie(0)
#define nfio cin.tie(0)
#define endl "\n"
 
//Order checking.
#define ord(a,b,c) ((a>=b)and(b>=c))
 
//min/max redefines, so i dont have to resolve annoying compile errors.
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

// Fast min/max assigns to use with AVX.
// Requires g++ 9.2.0.
template<typename T>
__attribute__((always_inline)) void chkmin(T& a, const T& b) {
    a=(a<b)?a:b;
}

template<typename T>
__attribute__((always_inline)) void chkmax(T& a, const T& b) {
    a=(a>b)?a:b;
}
 
//Constants.
#define MOD (ll(998244353))
#define MAX 300001
#define mag 320
const long double PI=3.14159265358979;
 
//Pairs and 3-pairs.
#define p1 first
#define p2 second.first
#define p3 second.second
#define fi first
#define se second
#define pii(element_type) pair<element_type,element_type>
#define piii(element_type) pair<element_type,pii(element_type)>
 
//Quick power of 2.
#define pow2(x) (ll(1)<<x)
 
//Short for-loops.
#define ff(i,__,___) for(int i=__;i<=___;i++)
#define rr(i,__,___) for(int i=__;i>=___;i--)
 
//Typedefs.
#define bi BigInt
typedef long long ll;
typedef long double ld;
typedef short sh;

// Binpow and stuff
ll BOW(ll a, ll x, ll p)
{
	if (!x) return 1;
	ll res=BOW(a,x/2,p);
	res*=res;
	res%=p;
	if (x%2) res*=a;
	return res%p;
}
ll INV(ll a, ll p)
{
	return BOW(a,p-2,p);
}
//---------END-------//
#endif
namespace CPL_DC3 {
	vector<int> buc[1200031];
	piii(int) pp1,pp2;
	int i,j,k,t,t1,u,v,a,b;
	int tmp[1200033];
	/*
		Given a string s with length n and an alphabet in [1,n], appened with one 0 at the end,
		build(s) returns the indices of suffixes of s
		in sorted order in O(n).
	*/
	vector<int> build(vector<int> s) {
		int n=s.size();
		// Base cases
		if (n==1) return {0};
		if (n==2) return {1,0};
		if (n==3) if (s[0]<s[1]) return {2,0,1}; else return {2,1,0};
		// Pad input with 0s.
		s.push_back(0);
		s.push_back(0);
		// Sort the difference cover sample (C).
		vector<int> dc3;
		for (i=0;i<n;i++) if (i%3) dc3.push_back(i);
			// Sort the length 3 chunks.
		for (j=2;j>=0;j--) {
			for (i=0;i<=n+30;i++) buc[i].clear();
			for (auto g : dc3) buc[s[g+j]].push_back(g);
			dc3.clear();
			for (i=0;i<=n+30;i++) for (auto g : buc[i]) dc3.push_back(g);
		}
			// Assign lexicographic names.
		t=1;
		for (i=0;i<dc3.size();i++) {
			if (i && 
			(s[dc3[i-1]]!=s[dc3[i]] || s[dc3[i-1]+1]!=s[dc3[i]+1] || s[dc3[i-1]+2]!=s[dc3[i]+2])) {
				t++;
			}
			tmp[dc3[i]]=t;
		}
			// Construct R.
			// R=chunk1chunk4chunk7...chunk2chunk5chunk8...
		vector<int> r;
		for (i=1;i<n;i+=3) r.push_back(tmp[i]);
		for (i=2;i<n;i+=3) r.push_back(tmp[i]);
		r.push_back(0);
			// Call build() recursively to get the suffix array of R.
		vector<int> sa=build(r);
			// Extract the sorted DC sample from the suffix array.
		for (i=0;i<n+2;i++) tmp[i]=0;
		t=0;
		dc3.clear();
		for (i=1;i<n;i+=3) t++;
		for (i=1;i<sa.size();i++) {
			if (sa[i]>=t) {
				u=(sa[i]-t)*3+2;
			} 
			else {
				u=(sa[i])*3+1;
			}
			dc3.push_back(u);
			tmp[u]=dc3.size();
		}
		// Sort the rest of the suffixes (rest).
		// Each suffix i is represeted as a pair (s[i],tmp[i+1]).
		vector<int> rest;
		for (i=0;i<n;i+=3) rest.push_back(i);

		for (i=0;i<=n;i++) buc[i].clear();
		for (auto g : rest) buc[tmp[g+1]].push_back(g);
		rest.clear();
		for (i=0;i<=n;i++) for (auto g : buc[i]) rest.push_back(g);

		for (i=0;i<=n+30;i++) buc[i].clear();
		for (auto g : rest) buc[s[g]].push_back(g);
		rest.clear();
		for (i=0;i<=n+30;i++) for (auto g : buc[i]) rest.push_back(g);
		// Merge rest and dc3 to obtain the final suffix array.
		vector<int> res;
		i=j=0;
		while(i<dc3.size() || j<rest.size()) {
			if (i==dc3.size()) {
				res.push_back(rest[j]); j++;
			}
			else if (j==rest.size()) {
				res.push_back(dc3[i]); i++;
			}
			else {
				if (dc3[i]%3==2) {
					pp1={s[dc3[i]],{s[dc3[i]+1],tmp[dc3[i]+2]}};
					pp2={s[rest[j]],{s[rest[j]+1],tmp[rest[j]+2]}};
				}
				else {
					pp1={0,{s[dc3[i]],tmp[dc3[i]+1]}};
					pp2={0,{s[rest[j]],tmp[rest[j]+1]}};
				}
				
				if (pp1<pp2) {
					res.push_back(dc3[i]); i++;
				}
				else {
					res.push_back(rest[j]); j++;
				}
			}
		}
		return res;
	}
	/*
		Given a string s with length n and an alphabet in [1,n], appened with one 0 at the end,
		and the suffix array sa constructed by build(),
		buildLCP() returns the LCP array in O(n).
	*/
	vector<int> buildLCP(vector<int> s, vector<int> sa) {
		int n=s.size();
		vector<int> od(n,0),lcp(n,0);
		for (i=0;i<n;i++) od[sa[i]]=i;
		
		k=0; // Current lower bound for lcp of next suffix.
		for (i=0;i<n;i++) // Iterate through suffixes from long to short.
		{
			u=od[i];
			if (u==n-1) lcp[u]=0,k=0; // If the current suffix is last in array, lcp is by default, 0.
			else
			{ 
				while(s[(i+k)%n]==s[(sa[u+1]+k)%n]) k++; // Increases k while possible.
				lcp[u]=k; 
				k=max(k-1,0); // Moves on to next suffix.
			}
		}
		return lcp;
	}
}