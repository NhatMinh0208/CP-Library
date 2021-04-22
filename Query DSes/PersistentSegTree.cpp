/*
    Normie's (long overdue) persistent segtree template
    Version 1.0
    This segtree supports point update and range query.
    Tested with https://www.spoj.com/problems/KQUERY/
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
#define fio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define nfio cin.tie(0);cout.tie(0)
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
struct node
{
    ll l=0,r=0,val=0;
    node(int _l=0, int _r=0, int _val=0)
    {
        l=_l;
        r=_r;
        val=_val;
    }
};
struct seg
{
    vector<node> tre[1000001];
    void reset(int c, int l, int r)
    {
        tre[c].clear();
        tre[c].emplace_back(0,0,0);
        if (l<r)
        {
            int mid=(l+r)/2;
            reset((c<<1),l,mid);
            reset((c<<1)+1,mid+1,r);
        }
    }
    int upd(int c, int l, int r, int t, ll x)
    {
        if ((l<=t)and(t<=r))
        {
            node prv=tre[c][tre[c].size()-1];
            if (l==r)
            {
                prv.l=0;
                prv.r=0;
                prv.val=x;
            }
            else
            {
                int mid=(l+r)/2;
                prv.l=upd((c<<1),l,mid,t,x);
                prv.r=upd((c<<1)+1,mid+1,r,t,x);
                prv.val=tre[(c<<1)][prv.l].val+tre[(c<<1)+1][prv.r].val;
            }

                tre[c].push_back(prv);
        }
        return tre[c].size()-1;
    }
    ll get(int c, int ind, int l, int r, int tl, int tr)
    {
        if ((tl>r)or(tr<l)) return 0;
        if ((l>=tl)and(r<=tr))
        {
            return tre[c][ind].val;
        }
        else
        {
            int mid=(l+r)/2;
            ll a=get((c<<1),tre[c][ind].l,l,mid,tl,tr);
            ll b=get((c<<1)+1,tre[c][ind].r,mid+1,r,tl,tr);
            return (a+b);
        }
    }
};
//-------------------//
vector<ll> vec;
ll n,m,i,j,k,t,t1,u,v,a,b,c,d;
ll arr[30001];
int main()
{
	fio;

    cin>>n;

    for (i=1;i<=n;i++)
    {
        cin>>arr[i];
        vec.push_back(i);
    }
    sort(vec.begin(),vec.end(),[](int a, int b){
        return (arr[a]<arr[b]);
    });

    seg st;

    st.reset(1,1,n);

    for (i=n-1;i>=0;i--)
    {
        st.upd(1,1,n,vec[i],1);
    }
    vec.clear();
    for (i=1;i<=n;i++) vec.push_back(arr[i]);
    sort(vec.begin(),vec.end());
    cin>>m;
    for (i=1;i<=m;i++)
    {
        cin>>a>>b>>c;
        cout<<st.get(1,vec.end()-upper_bound(vec.begin(),vec.end(),c),1,n,a,b)<<endl;
    }

}
