#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
    Heavy-light decomposition, version 2.0.
    I have rewritten the code entirely, so that it is much cleaner.
    Tested with https://codeforces.com/gym/102059/problem/A
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

//Pragmas (Comment out these three lines if you're submitting in szkopul or USACO.)
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

struct CPL_HLD {
	int n, pathCnt;
	vector<int> gt[200001];
	vector<int> path[200001];
	int pathP[200001];
	int pathId[200001],pathPos[200001];
	int sz[200001];

	void setN(int x) {
		n=x;
	}
	void add_edge(int u, int v) {
		gt[u].push_back(v);
		gt[v].push_back(u);
	}

	void dfs(int x, int p) {
		sz[x]=1;
		for (auto g : gt[x]) if (g-p) {
			dfs(g,x);
			sz[x]+=sz[g];
		}
	}

	void getPath(int x, int p, int curId, int curPos) {
		pathId[x]=curId;
		pathPos[x]=curPos;
		path[curId].push_back(x);
		int u=-1;
		for (auto g : gt[x]) if (g-p) {
			if (u==-1) u=g;
			else if (sz[g]>sz[u]) u=g;
		}
		if (u==-1) return;
		getPath(u,x,curId,curPos+1);
		for (auto g : gt[x]) if (g-p && g-u) {
			pathCnt++;
			pathP[pathCnt-1]=x;
			getPath(g,x,pathCnt-1,0);
		}
	}

	void hld() {
		dfs(1,-1);
		pathCnt=1;
		getPath(1,-1,0,0);
		// for (int i=1;i<=n;i++) {
		// 	cout<<pathId[i]<<' '<<pathPos[i]<<endl;
		// }
	}
};
// Testing code follows.
CPL_HLD gr;

vector<pii(int)> pathCol[200001];
int colCnt[200001];
int cntCnt[200001];
int n,m,i,j,k,t,t1,u,v,a,b,c;
int main()
{
	fio;
	cin>>n>>k>>t;
	colCnt[0]=n;
	cntCnt[n]=1;
	cntCnt[0]=k;
	for (i=1;i<n;i++) {
		cin>>u>>v;
		gr.add_edge(u,v);
	}
	gr.setN(n);
	gr.hld();
	for (i=0;i<gr.pathCnt;i++) pathCol[i].push_back({gr.path[i].size(),0});
	for (t1=0;t1<t;t1++) {
		cin>>u>>a>>b;
		// int iter = 0;
		while(true) {
			// iter++;
			// assert(iter<=20);
			c=gr.pathId[u];
			v=gr.pathPos[u]+1;
			// cout<<c<<' '<<v<<' '<<a<<endl;
			while(v>0) {
				if (v>=pathCol[c].back().fi) {
					v-=pathCol[c].back().fi;
					cntCnt[colCnt[pathCol[c].back().se]]--;
					cntCnt[colCnt[pathCol[c].back().se]-pathCol[c].back().fi]++;
					colCnt[pathCol[c].back().se]-=pathCol[c].back().fi;
					pathCol[c].pop_back();
				}
				else {
					cntCnt[colCnt[pathCol[c].back().se]]--;
					cntCnt[colCnt[pathCol[c].back().se]-v]++;
					colCnt[pathCol[c].back().se]-=v;
					pathCol[c].back().fi-=v;
					v=0;
				}
			}
			v=gr.pathPos[u]+1;
			pathCol[c].push_back({v,a});
			cntCnt[colCnt[a]]--;
			cntCnt[colCnt[a]+v]++;
			colCnt[a]+=v;
			// for (auto g : pathCol[c]) cout<<'('<<g.fi<<' '<<g.se<<") "; cout<<endl;
			if (c==0) break;
			else u=gr.pathP[c];
		} 
		// for (i=0;i<=n;i++) cout<<colCnt[i]<<' '; cout<<endl;
		a = cntCnt[b];
		u = pathCol[0].back().se;
		if (colCnt[u] == b) a--;
		if (colCnt[u] == b+1) a++;
		if (colCnt[0] == b) a--;
		cout<<a<<endl;
	}
}
