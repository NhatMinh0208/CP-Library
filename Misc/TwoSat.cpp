/*
    2-SAT solver, version 1.1.
    Given a 2-SAT problem in implication graph form, this algorithm solves it in O(N+M).
    Vertices x is inverse of vertex x^1.
    There should be an edge u->v if u<=v.
    Tested with https://judge.yosupo.jp/problem/two_sat
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
namespace CPL_2SAT {
    vector<int> gt[2000001],gtr[2000001],tout;
    int res[2000001];
    int reg[2000001];
    int n,m,i,j,k,t,t1,u,v,a,b;
    void dfs1(int x)
    {
        reg[x]=1;
        for (auto g : gt[x]) if (!reg[g]) dfs1(g);
        tout.push_back(x);
    }
    void dfs2(int x, int& t)
    {
        reg[x]=t;
        for (auto g : gtr[x]) if (!reg[g]) dfs2(g,t);
    }
    int solveSAT(int n)
    {
        int i;
        int t;
        for (i=0;i<2*n;i++) gtr[i].clear();
        for (i=0;i<2*n;i++) for (auto g : gt[i]) gtr[g].push_back(i);
        tout.clear();
        for (i=0;i<2*n;i++) reg[i]=0;
        for (i=0;i<2*n;i++) if (!reg[i]) dfs1(i);
        for (i=0;i<2*n;i++) reg[i]=0;
        t=0;
        for (i=2*n-1;i>=0;i--) if (!reg[tout[i]])
        {
            t++;
            dfs2(tout[i],t);
        }
        for (i=0;i<n;i++) if (reg[i*2]==reg[i*2+1]) return 0;
        for (i=0;i<2*n;i++) res[i]=-1;
        for (i=0;i<2*n;i++) if (res[tout[i]]==-1)
        {
            res[tout[i]]=1;
            res[tout[i]^1]=0;
        }
        return 1;
    }

    void add(int u, int v)
    {
        gt[u].push_back(v);
        gt[v^1].push_back(u^1);
    }
}
using namespace CPL_2SAT;
// Example problem follows.
// Problem source: https://judge.yosupo.jp/problem/two_sat
int main()
{
	fio;
    string s;
    cin>>s;
    cin>>s;
    cin>>n>>m;
    for (i=0;i<m;i++)
    {
        cin>>a>>b>>u;
        if ((a>0)and(b>0))
        {
            a--;
            b--;
            add(a*2+1,b*2);
        }
        else
        if ((a>0)and(b<0))
        {
            b=-b;
            a--;
            b--;
            add(a*2+1,b*2+1);
        }
        else
        if ((a<0)and(b>0))
        {
            a=-a;
            a--;
            b--;
            add(a*2,b*2);
        }
        else
        {
            a=-a;
            b=-b;
            a--;
            b--;
            add(a*2,b*2+1);
        }
    }
    if (solveSAT(n))
    {
        cout<<"s SATISFIABLE"<<endl;
        cout<<"v ";
        for (i=0;i<n;i++) if (res[i*2]) cout<<(i+1)<<' '; else cout<<-(i+1)<<' ';
        cout<<0;
    }
    else cout<<"s UNSATISFIABLE";
}
