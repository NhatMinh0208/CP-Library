#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
	Implicit treap, version 1.0.
    Acts as a split/mergable array with built-in segtree sum operations.
    Tested with https://codeforces.com/gym/102787/problem/A
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
typedef int ll;
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

#include "TreapCommon.hpp"
 
namespace CPL_ITreap
{
    using namespace CPL_TreapNode;
    void split(p_node p, ll key, p_node& l, p_node& r, int c=0)
    {
        if (!p)
        {
            l=r=NULL;
        }
        else if (key<c+get_sz(p->l)+1)
        {
            split(p->l,key,l,p->l,c), r=p;
        }
        else
        {
            split(p->r,key,p->r,r,c+get_sz(p->l)+1), l=p;
        }
        update_sz(l), update_sz(r);
        update_sum(l), update_sum(r);
    }
    void insert(p_node& p, p_node x, int c=0)
    {
        if (!p) p=x;
        else if (x->h>p->h) 
        {
            split(p,x->key,x->l,x->r,c), p=x;
        }
        else if (x->key<c+get_sz(p->l)+1)
        {
            insert(p->l,x,c);
        }
        else
        {
            insert(p->r,x,c+get_sz(p->l)+1);
        }
        update_sz(p);
        update_sum(p);
    }
    void merge(p_node& p, p_node l, p_node r)
    {
        if (!l) p=r;
        else 
        if (!r) p=l;
        else
        if (l->h<r->h)
        {
            merge(r->l,l,r->l);
            p=r;
        }
        else 
        {
            merge(l->r,l->r,r);
            p=l;
        }
        update_sz(p);
        update_sum(p);
    }
    void erase(p_node& p, ll key, int c=0)
    {
        if ((c+get_sz(p->l)+1)==key)
        {
            auto x=p;
            merge(p,p->l,p->r);
            x->l=NULL;
            x->r=NULL;
            if (x) delete x;
        }
        else if ((c+get_sz(p->l)+1)>key)
        {
            erase(p->l,key,c);
        }
        else erase(p->r,key,c+get_sz(p->l)+1);
        update_sz(p);
        update_sum(p);
    }
    ll sum_by_key(p_node root, ll l, ll r, ll tl, ll tr)
    {
        if (!root) return 0;
        if ((tl>r)or(tr<l)) return 0;
        if ((tl<=l)and(tr>=r)) return root->sum;
        else 
        {
            ll res=0,a;
            if ((tl<=l+get_sz(root->l))and(l+get_sz(root->l)<=tr)) res+=root->val;
            a=sum_by_key(root->l,l,l+get_sz(root->l)-1,tl,tr); res+=a;
            a=sum_by_key(root->r,l+get_sz(root->l)+1,r,tl,tr); res+=a;   
            return res;         
        }
    }
}
 
// Example problem follows. 
vector<int> vec;
int n,m,i,j,k,t,t1,u,v,a,b;
int main()
{
	fio;
	cin>>n;
	auto tr = new CPL_TreapNode::node(1,1);
	for (i=2;i<=n;i++) {
		auto nu = new CPL_TreapNode::node(i,i);
		CPL_ITreap::merge(tr,tr,nu);
	}
	for (i=1;i<=n;i++) {
		cin>>a>>b;
		u=min(b-a,n+1-b);
		CPL_TreapNode::p_node t1,t2,t3,t4,t5;
 
		CPL_ITreap::split(tr,a-1,t1,tr);
		CPL_ITreap::split(tr,u,t2,tr);
		CPL_ITreap::split(tr,b-1-(a-1)-u,t3,tr);
		CPL_ITreap::split(tr,u,t4,tr);
		CPL_ITreap::split(tr,n-(b-1)-u,t5,tr);
 
		CPL_ITreap::merge(tr,tr,t1);
		CPL_ITreap::merge(tr,tr,t4);
		CPL_ITreap::merge(tr,tr,t3);
		CPL_ITreap::merge(tr,tr,t2);
		CPL_ITreap::merge(tr,tr,t5);
	}
 
	cout<<tr;
}