#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
	Template for solving centroid decomp problems.
*/
// Standard library in one include.
#include <bits/stdc++.h>
using namespace std;
 
// ordered_set library.
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set(el) tree<el,null_type,less<el>,rb_tree_tag,tree_order_statistics_node_update>
 
// AtCoder library. (Comment out these two lines if you're not submitting in AtCoder.) (Or if you want to use it in other judges, run expander.py first.)
//#include <atcoder/all>
//using namespace atcoder;

//Pragmas (Comment out these three lines if you're submitting in szkopul or USACO.)
// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast,unroll-loops,tree-vectorize")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
 
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
// template<typename T>
// __attribute__((always_inline)) void chkmin(T& a, const T& b) {
//     a=(a<b)?a:b;
// }

// template<typename T>
// __attribute__((always_inline)) void chkmax(T& a, const T& b) {
//     a=(a>b)?a:b;
// }
 
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
set<pii(int)> gt[200001];
set<int> mrk[200001];
ll n,m,i,j,k,t,t1,u,v,a,b;
ll arr[200001];
ll eu[200001],ev[200001],ec[200001];
ll qu[200001],qv[200001],qr[200001];

ll sz[200001];
ll dep[200001];

vector<int> curq;
vector<int> curn;

void preJob(int x) {
    sz[x]=1;
    for (auto g : gt[x]) if (!sz[g.fi]) {
        preJob(g.fi);
        sz[x]+=sz[g.fi];
    }
}

void postJob(int x) {
    sz[x]=0;
    dep[x]=0;
    for (auto g : gt[x]) if (sz[g.fi]) {
        postJob(g.fi);
    }
}

int tmp;

void prep(int x, int p) {
}

void solve(int x) {
    preJob(x);
    
    int n = sz[x];

    int rt,v,p;
    rt=x;
    p=0;
    while(true) {
        v=0;
        for (auto g : gt[rt]) if (g.fi!=p && sz[g.fi]>sz[v]) v=g.fi;
        if (sz[v]*2<=n && sz[rt]*2>=n) break;
        else {
            p=rt;
            rt=v;
        }
    }


    // START SOLVING CODE

    tmp = rt;
    for (auto g : gt[rt]) {
        prep(g.fi,rt);
    }

    // END SOLVING CODE

    postJob(x);
    
    curq.clear();
    curn.clear();
    
    for (auto g : gt[rt]) {
        gt[g.fi].erase({rt,g.se});
        solve(g.se);
    }
}

int main()
{
	fio;
    cin>>n>>m;
    for (i=1;i<=n;i++) {
        cin>>arr[i];
    }
    for (i=1;i<n;i++) {
        cin>>eu[i]>>ev[i]>>ec[i];
        gt[eu[i]].insert({ev[i],ec[i]});
        gt[ev[i]].insert({eu[i],ec[i]});
    }
    for (i=1;i<=m;i++) {
        cin>>qu[i]>>qv[i];
        if (qu[i]==qv[i]) {
            if (arr[qu[i]]==0) qr[i]=0; else qr[i]=-1;
        }
        else {
            mrk[qu[i]].insert(i);
            mrk[qv[i]].insert(i);
        }
    }

    solve(1);
}
// a;