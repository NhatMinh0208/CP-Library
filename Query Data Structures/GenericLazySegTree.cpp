#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
	Normie's generic lazy segment tree implementation, version 1.0.
    Supports range update and range query.
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

namespace CPL_GLST {
    template<typename N, typename U> struct seg {
        N val[1000001];
        U lz[1000001];
        N (*node_update)(N,U);
        U (*update_merge)(U,U);
        N (*node_merge)(N,N);
        N node_def;
        U update_def;
        vector<N> init;
        int n;
        void reset(int c, int l, int r) {
            lz[c]=update_def;
            if (l==r) val[c]=init[l-1];
            else {
                int mid=(l+r)/2;
                reset((c<<1),l,mid);
                reset((c<<1)+1,mid+1,r);
                val[c]=node_merge(val[(c<<1)],val[(c<<1)+1]);
            }
        }
        seg(int _n, N _nd, U _ud, N(*_nm)(N,N), N (*_nu)(N,U), U (*_um)(U,U), vector<N> _init) {
            n=_n;
            node_def = _nd;
            update_def = _ud;
            node_update = _nu;
            update_merge = _um;
            node_merge = _nm;
            init = _init;
            reset(1,1,n);
        }

        void flush(int c) {
            val[(c<<1)]=node_update(val[(c<<1)],lz[c]);
            val[(c<<1)+1]=node_update(val[(c<<1)+1],lz[c]);
            lz[(c<<1)]=update_merge(lz[(c<<1)],lz[c]);
            lz[(c<<1)+1]=update_merge(lz[(c<<1)+1],lz[c]);
            lz[c]=update_def;
        }

        void upd(int c, int l, int r, int tl, int tr, U x) {
            if (l>tr || r<tl) return;
            if (l>=tl && r<=tr) {
                val[c]=node_update(val[c],x);
                lz[c]=update_merge(lz[c],x);
            }
            else {
                int mid=(l+r)/2;
                flush(c);
                upd((c<<1),l,mid,tl,tr,x);
                upd((c<<1)+1,mid+1,r,tl,tr,x);
                val[c]=node_merge(val[(c<<1)],val[(c<<1)+1]);
            }
        } 
        N ge(int c, int l, int r, int tl, int tr) {
            if (l>tr || r<tl) return node_def;
            if (l>=tl && r<=tr) {
                return val[c];
            }
            else {
                int mid=(l+r)/2;
                flush(c);
                N a = ge((c<<1),l,mid,tl,tr);
                N b = ge((c<<1)+1,mid+1,r,tl,tr);
                return node_merge(a,b);
            }
        }

        void update(int l, int r, U payload) {
            if (l>r) return;
            upd(1,1,n,l,r,payload);
        }

        N get(int l, int r) {
            if (l>r) return node_def;
            return ge(1,1,n,l,r);
        }
    };
}
// Sample problem: https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/D
pii(ll) node_update(pii(ll) a, ll b) {
    return {a.fi,a.se+a.fi*b};
}

pii(ll) node_merge(pii(ll) a, pii(ll) b){
    return {a.fi+b.fi,a.se+b.se};
}

ll update_merge(ll a, ll b) {
    return a+b;
}

vector<pii(ll)> vec;
ll n,m,i,j,k,t,t1,u,v,a,b;
int main()
{
	fio;
	cin>>n>>m;
	for (i=1;i<=n;i++) vec.push_back({1,0});
    CPL_GLST::seg<pii(ll),ll> st(n, {0,0}, 0, node_merge, node_update, update_merge, vec);
    for (i=1;i<=m;i++) {
        cin>>t;
        if (t==1) {
            cin>>u>>v>>a; u++;
            st.update(u,v,a);
        }
        else {
            cin>>u>>v;
            u++;
            cout<<st.get(u,v).se<<endl;
        }
        
    }
}
