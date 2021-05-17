/*
	Simple Convex Hull template, version 1.0
    (for max queries)
    Supports line add and point max.
    For use in simple applications.
    Based on KACTL's LineContainer, with minor modifications.
    Tested on https://judge.yosupo.jp/problem/line_add_get_min
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
ll floor_div(ll a, ll b) //actually floored
{
    return (a/b)-(((a^b)<0)and(a%b));
}
struct Line{
    mutable ll a,b,p;
    int operator<(const Line& oth) const
    {
        return (a<oth.a);
    }
    int operator<(ll x) const
    {
        return (p<x);
    }
};

struct SimpleConvexHull: multiset<Line,less<>>
{
    static const ll INF=LLONG_MAX,FAILED=-696969696969696969;

    int isect(iterator x, iterator y)
    {
        if (y==end()) return x->p=INF,0;
        if (x->a==y->a) 
        {
            x->p=(x->b>y->b)?INF:-INF;
        }   
        else x->p=floor_div(y->b - x->b, x->a - y->a);
        return (x->p >= y->p);
    }

    void add(ll a, ll b)
    {
        auto z=insert({a,b,0}),y=z++,x=y;
        while(isect(y,z)) z=erase(z);
        if ((x!=begin())and(isect(--x,y))) isect(x,y=erase(y));
        while ( ((y=x)!=begin()) and ((--x)->p >= y->p) )
        {
            isect(x,erase(y));
        }
    }
    ll query(ll x)
    {
        if (empty()) return FAILED;
        auto l=(*(lower_bound(x)));
        return l.a*x+l.b;
    }
};

// Example follows.
// Problem source: https://judge.yosupo.jp/problem/line_add_get_min
ll n,m,i,j,k,t,t1,u,v,a,b;
int main()
{
    fio;
    cin>>n>>m;
    SimpleConvexHull ch;
    for (i=1;i<=n;i++)
    {
        cin>>a>>b;
        ch.add(-a,-b);
    }
    for (i=1;i<=m;i++)
    {
        cin>>u;
        if (u==0)
        {
            cin>>a>>b;
            ch.add(-a,-b);
        }
        else
        {
            cin>>a;
            b=ch.query(a);
            cout<<-b<<endl;
        }
    }
}