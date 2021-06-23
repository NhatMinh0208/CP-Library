
#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
    Treap version 1.0
    Serves as a map with find-by-order operation, as well as sum of values of a key range. 
    Can be easily extended to support segtree operations (for example, the sz field and sum_by_key.)
    insert/erase/order_of_key tested with https://www.spoj.com/problems/ADACROP/.
    insert/erase/get_by_key/sum_by_key tested with https://judge.yosupo.jp/problem/point_add_range_sum.
    See TreapCommon.hpp for facilities used in this file.
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

#include "TreapCommon.hpp"


namespace CPL_Treap
{
    using namespace CPL_TreapNode;
    void split(p_node p, ll key, p_node& l, p_node& r)
    {
        if (!p)
        {
            l=r=NULL;
        }
        else if (key<p->key)
        {
            split(p->l,key,l,p->l), r=p;
        }
        else
        {
            split(p->r,key,p->r,r), l=p;
        }
        update_sz(l), update_sz(r);
        update_sum(l), update_sum(r);
    }
    void insert(p_node& p, p_node x)
    {
        if (!p) p=x;
        else if (x->h>p->h) 
        {
            split(p,x->key,x->l,x->r), p=x;
        }
        else if (x->key<p->key)
        {
            insert(p->l,x);
        }
        else
        {
            insert(p->r,x);
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
    void erase(p_node& p, ll key)
    {
        if (p->key==key)
        {
            auto x=p;
            merge(p,p->l,p->r);
            x->l=NULL;
            x->r=NULL;
            if (x) delete x;
        }
        else if (p->key>key)
        {
            erase(p->l,key);
        }
        else erase(p->r,key);
        update_sz(p);
        update_sum(p);
    }
    p_node get_by_key(p_node root, ll key)
    {
        if (root->key==key) return root;
        else if (root->key>key) return get_by_key(root->l,key);
        else return get_by_key(root->r,key);
    }
    ll order_of_key(p_node root, ll key)
    {
        if (root->key==key) return (get_sz(root->l));
        else if (root->key>key) return order_of_key(root->l,key);
        else 
        {
            ll a=0,b=0;
            a=order_of_key(root->r,key);
            b=get_sz(root->l);
            return (a+b+1);
        }
    }
    p_node get_by_order(p_node root, ll l, ll r, ll ord)
    {
        ll x=l+get_sz(root->l);
        if (x==ord) return root;
        else if (x>ord) return get_by_order(root->l,l,x-1,ord);
        else if (x<ord) return get_by_order(root->r,x+1,r,ord);
    }
    ll sum_by_key(p_node root, ll l, ll r, ll tl, ll tr)
    {
        if (!root) return 0;
        if ((tl>r)or(tr<l)) return 0;
        if ((tl<=l)and(tr>=r)) return root->sum;
        else 
        {
            ll res=0,a;
            if ((tl<=root->key)and(root->key<=tr)) res+=root->val;
            a=sum_by_key(root->l,l,root->key-1,tl,tr); res+=a;
            a=sum_by_key(root->r,root->key+1,r,tl,tr); res+=a;   
            return res;         
        }
    }
}

// Example problem follows.
// Source (insert/erase/order_of_key): https://www.spoj.com/problems/ADACROP/
// Source (insert/erase/get_by_key/sum_of_key): https://judge.yosupo.jp/problem/point_add_range_sum

ll n,m,i,j,k,t,t1,u,v,a,b,las;
map<int,CPL_TreapNode::p_node> lmao;
ll arr[200001];
int main()
{
    fio;
    cin>>n;
    cin>>m;
    for (i=1;i<=n;i++)
    {
        cin>>arr[i];
        CPL_Treap::insert(lmao[arr[i]],new CPL_TreapNode::node(i,0));
    //    cout<<"insert "<<i<<endl;
    //    cout<<lmao[arr[i]]<<endl;
    }
    for (i=1;i<=m;i++)
    {
        cin>>a>>b;
        a++;
        CPL_Treap::erase(lmao[arr[a]],a);
        arr[a]=b;
        CPL_Treap::insert(lmao[arr[a]],new CPL_TreapNode::node(a,0));
    //    cout<<lmao[arr[a]]<<endl;
        cout<<CPL_Treap::order_of_key(lmao[arr[a]],a)<<endl;
    }
}