
#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
    Basic treap facilities version 1.0
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

namespace CPL_TreapUtil
{
    seed_seq seq{
        (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
        (uint64_t) __builtin_ia32_rdtsc(),
        (uint64_t) (uintptr_t) make_unique<char>().get()
    };
    mt19937 rng(seq);
    ll get_rand(ll l, ll r)
    {
	    return uniform_int_distribution<ll>(l,r)(rng);
    }

    set<ll> dict;
    ll generateNewHeight()
    {
        ll u;
        while(true)
        {
            u=get_rand(1,1e18);
            if ((dict.lower_bound(u)==dict.end())or(*(dict.lower_bound(u))>u))
            {
                dict.insert(u);
                return u;
            }
        }
    }
}


namespace CPL_TreapNode
{
    using namespace CPL_TreapUtil;
    struct node;
    typedef node* p_node;
    struct node
    {
        ll key, h, sz;
        ll val,sum;
        p_node l,r;
        node(ll _key=0, ll _val=0) : key(_key), l(NULL), r(NULL), val(_val), sum(_val)
        {
            h=generateNewHeight();
            sz=1;
        }
        ~node()
        {
            if (l) delete l;
            if (r) delete r;
            dict.erase(h);
        }
    };
    ll get_sz(p_node p) 
    {
        if (!p) return 0;
        else return p->sz;
    }
    ll get_sum(p_node p)
    {
        if (!p) return 0;
        else return p->sum;
    }
    void update_sz(p_node x)
    {
        if (x) x->sz=get_sz(x->l)+get_sz(x->r)+1;
    }
    void update_sum(p_node x)
    {
        if (x) x->sum=get_sum(x->l)+get_sum(x->r)+x->val;
    }
    ostream& operator<<(ostream& ou, p_node x)
    {
        if (x)
        {
            ou<<x->l;
            ou<<x->key<<' '<<x->val<<' '<<x->sz<<' '<<x->sum<<endl;
            ou<<x->r;
        }
        return ou;
    }
}