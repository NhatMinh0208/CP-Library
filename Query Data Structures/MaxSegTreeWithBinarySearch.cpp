/*
	Max segtree with binary search capabilities, version 1.1.
    Supports range add, range max, first/last element greater than a certain threshold in range all in O(nlogn).
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
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

//Constants.
#define MOD (ll(998244353))
#define MAX 300001
#define mag 320

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
ll star[1000001];
struct seg
{
	ll val[4000401],lazy[4000401];
	vector<piii(ll)> nodes;
	ll n;
	void resetK(ll l, ll r, ll cur)
	{
		if (l==r)
		{
			lazy[cur]=0;
			val[cur]=star[l];
		}
		else
		{
			lazy[cur]=0;
			ll mid=(l+r)/2;
			resetK(l,mid,(cur<<1));
			resetK(mid+1,r,(cur<<1)+1);
			val[cur]=max(val[(cur<<1)],val[(cur<<1)+1]);
		}
	}
	void reset(ll nn)
	{
		n=nn;
		resetK(1,n,1);
	}
	void flusha(ll cur)
	{
	//	cout<<"flusha "<<cur<<endl;
	//	cout<<"before: "<<lazy[(cur<<1)]<<' '<<val[(cur<<1)]<<' '<<lazy[(cur<<1)+1]<<' '<<val[(cur<<1)+1]<<endl;
		lazy[(cur<<1)]+=lazy[cur];
		val[(cur<<1)]+=lazy[cur];
		lazy[(cur<<1)+1]+=lazy[cur];
		val[(cur<<1)+1]+=lazy[cur];
	//	cout<<"after: "<<lazy[(cur<<1)]<<' '<<val[(cur<<1)]<<' '<<lazy[(cur<<1)+1]<<' '<<val[(cur<<1)+1]<<endl;
		lazy[cur]=0;
	}
	void updateK(ll l, ll r, ll cur, ll tl, ll tr, ll d)
	{
		if ((tl>r)or(tr<l)) return;
		if ((tl<=l)and(tr>=r)) 
		{
	//		cout<<"update directly "<<cur<<' '<<d<<endl;
	//		cout<<"before: "<<val[cur]<<' '<<lazy[cur]<<endl;
			val[cur]+=d;
			lazy[cur]+=d;
	//		cout<<"after: "<<val[cur]<<' '<<lazy[cur]<<endl;
		}
		else
		{
			ll mid=(l+r)/2;
			flusha(cur);
			updateK(l,mid,(cur<<1),tl,tr,d);
			updateK(mid+1,r,(cur<<1)+1,tl,tr,d);
			val[cur]=max(val[(cur<<1)],val[(cur<<1)+1]);
		}
	}
	void update(ll l, ll r, ll d)
	{
		if (l>r) return;
		updateK(1,n,1,l,r,d);
	//	debug();
	}
	void debugK(ll l, ll r, ll cur)
	{
		cout<<"---------------------------------\n";
		cout<<"Now crawling node: "<<cur<<endl;
		cout<<"Covering range: ("<<l<<","<<r<<")"<<endl;
		cout<<"It's values: "<<"val = "<<val[cur]<<" lazy = "<<lazy[cur]<<endl;
		cout<<"---------------------------------\n";
		ll mid=(l+r)/2;
		if (l<r)
		{
		debugK(l,mid,(cur<<1));
		debugK(mid+1,r,(cur<<1)+1);
		}
	}
	void debug()
	{
		debugK(1,n,1);
	}
	ll getK(ll l, ll r, ll cur, ll tl, ll tr)
	{
		if ((tl>r)or(tr<l)) return -1;
		if ((tl<=l)and(tr>=r)) 
		{
			return val[cur];
		}
		else
		{
			ll mid=(l+r)/2;
			flusha(cur);
			ll aa=getK(l,mid,(cur<<1),tl,tr);
			ll bb=getK(mid+1,r,(cur<<1)+1,tl,tr);
			return max(aa,bb);
		}
	}
	ll get(ll l, ll r)
	{
		if (l>r) return -1;
		return getK(1,n,1,l,r);
	}
	void get_nodes(ll l, ll r, ll cur, ll tl, ll tr)
	{
		if ((tl>r)or(tr<l)) return ;
		if ((tl<=l)and(tr>=r)) 
		{
			nodes.push_back({cur,{l,r}});
		}
		else
		{
			flusha(cur);
			ll mid=(l+r)/2;
			get_nodes(l,mid,(cur<<1),tl,tr);
			get_nodes(mid+1,r,(cur<<1)+1,tl,tr);
		}
	}
	ll bsK(ll l, ll r, ll cur, ll x)
	{
		if (l==r)
		{
			if (val[cur]<=x) return l+1;
			else return l;
		}
		else
		{
			ll mid=(l+r)/2;
			flusha(cur);
			if (val[(cur<<1)]>x) return bsK(l,mid,(cur<<1),x);
			else return bsK(mid+1,r,(cur<<1)+1,x);
		}
	}
	
	ll bs(ll l, ll r, ll x)
	{
	//	cout<<"bs "<<l<<' '<<r<<' '<<x<<endl;
		nodes.clear();
		get_nodes(1,n,1,l,r);
	//	cout<<"nodes:\n";
		for (int i=0;i<nodes.size();i++) if (val[nodes[i].fi]>x)
		{
		//	cout<<nodes[i].fi<<' '<<nodes[i].se.fi<<' '<<nodes[i].se.se<<endl;
			auto u=bsK(nodes[i].se.fi,nodes[i].se.se,nodes[i].fi,x);
			return u;
		}
		return r+1;
	}
	
	ll bsRevK(ll l, ll r, ll cur, ll x)
	{
		if (l==r)
		{
			if (val[cur]<=x) return l-1;
			else return l;
		}
		else
		{
			ll mid=(l+r)/2;
			flusha(cur);
			if (val[(cur<<1)+1]>x) return bsRevK(mid+1,r,(cur<<1)+1,x);
			else return bsRevK(l,mid,(cur<<1),x);
		}
	}
	ll bsRev(ll l, ll r, ll x)
	{
	//	cout<<"bsRev "<<l<<' '<<r<<' '<<x<<endl;
		nodes.clear();
		get_nodes(1,n,1,l,r);
	//	cout<<"nodes:\n";
		for (int i=nodes.size()-1;i>=0;i--) if (val[nodes[i].fi]>x)
		{
		//	cout<<nodes[i].fi<<' '<<nodes[i].se.fi<<' '<<nodes[i].se.se<<endl;
			auto u=bsRevK(nodes[i].se.fi,nodes[i].se.se,nodes[i].fi,x);
			return u;
		}
		return l-1;
	}
};
