/*
	Normie's Segtree Beats
	Version 0.1
	This is the first version, it supports only 3 operations:
	Add on a given range.
	Set ai=max(ai,x) on a given range.
	Get min on a given range.
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

//---------END-------//
struct stb
{
	ll min1[800001],min2[800001];
	ll lazy1[800001],lazy2[800001];
	void reset(ll c, ll l, ll r)
	{
		min1[c]=0;
		min2[c]=1e18;
		lazy1[c]=0;
		lazy2[c]=0;
		if (l<r)
		{
			ll mid=(l+r)/2;
			reset((c<<1),l,mid);
			reset((c<<1)+1,mid+1,r);
		}
		
	}
	void merg(ll x)
	{
		vector<ll> g;
		g.push_back(min1[(x<<1)]);
		g.push_back(min1[(x<<1)+1]);
		g.push_back(min2[(x<<1)]);
		g.push_back(min2[(x<<1)+1]);
		sort(g.begin(),g.end());
		auto it=unique(g.begin(),g.end());
		g.erase(it,g.end());
		min1[x]=g[0];
		min2[x]=g[1];
	}
	void flusha(ll x)
	{
		min1[(x<<1)]+=lazy1[x];
		min1[(x<<1)+1]+=lazy1[x];
		lazy1[(x<<1)]+=lazy1[x];
		lazy1[(x<<1)+1]+=lazy1[x];
		lazy1[x]=0;
		min2[(x<<1)]+=lazy2[x];
		min2[(x<<1)+1]+=lazy2[x];
		lazy2[(x<<1)]+=lazy2[x];
		lazy2[(x<<1)+1]+=lazy2[x];
		lazy2[x]=0;
	}
	void uadd(ll c, ll l, ll r, ll tl, ll tr, ll t)
	{
		if ((l>tr)or(r<tl)) return;
		if ((l>=tl)and(r<=tr))
		{
			min1[c]+=t;
			min2[c]+=t;
			lazy1[c]+=t;
			lazy2[c]+=t;
		}
		else
		{
			flusha(c);
			ll mid=(l+r)/2;
			uadd((c<<1),l,mid,tl,tr,t);
			uadd((c<<1)+1,mid+1,r,tl,tr,t);
			merg(c);
		}
	}
	void umax(ll c, ll l, ll r, ll tl, ll tr, ll t)
	{
		if ((l>tr)or(r<tl)or(min1[c]>=t)) return;
		if ((l>=tl)and(r<=tr)and(min2[c]>t))
		{
			lazy1[c]+=t-min1[c];
			min1[c]=t;
		}
		else
		{
			flusha(c);
			ll mid=(l+r)/2;
			umax((c<<1),l,mid,tl,tr,t);
			umax((c<<1)+1,mid+1,r,tl,tr,t);
			merg(c);
		}
	}
	ll gmin(ll c, ll l, ll r, ll tl, ll tr)
	{
		if ((l>tr)or(r<tl)) return 1e18;
		if ((l>=tl)and(r<=tr))
		{
			return min1[c];
		}
		else
		{
			flusha(c);
			ll mid=(l+r)/2;
			ll a=gmin((c<<1),l,mid,tl,tr);
			ll b=gmin((c<<1)+1,mid+1,r,tl,tr);
			return min(a,b);
		}
	}
};
stb why;
ll n,m,i,j,k,t,t1,u,v,a,b,c,d;
void solve4()
{
	why.reset(1,1,n);
	for (t1=0;t1<t;t1++)
	{
		cin>>u;
		if (u==1)
		{
			cin>>a>>b>>c>>d;
			why.uadd(1,1,n,a,b,d);
		}
		else if (u==2)
		{
			cin>>a>>b>>c;
			why.uadd(1,1,n,a,b,-c);
			why.umax(1,1,n,a,b,0);
		}
		else if (u==3)
		{
			cin>>a>>b;
			v=why.gmin(1,1,n,a,a);
			if (v>=b) cout<<1<<endl;
			else cout<<0<<endl;
		}
	}
}
int main()
{
	fio;
	cin>>n>>m>>t;
	if (m==1) solve4();
}