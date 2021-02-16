/*
khoi orz, go check out his algo
-normie-
Tested with library-checker.
*/
#include <bits/stdc++.h>
using namespace std;
#define FILE_IN "birds.inp"
#define FILE_OUT "birds.out"
#define prev prv
#define ofile freopen(FILE_IN,"r",stdin);freopen(FILE_OUT,"w",stdout)
#define fio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define nfio cin.tie(0);cout.tie(0)
#define max(x,y) (((x)>(y))?(x):(y))
#define min(x,y) (((x)<(y))?(x):(y))
#define ord(a,b,c) ((a>=b)and(b>=c))
#define MOD (ll(1000000007))
#define MAX 300001
#define mag 320
#define p1 first
#define p2 second.first
#define p3 second.second
#define fi first
#define se second
#define pow2(x) (ll(1)<<x)
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define For(i,__,___) for(int i=__;i<=___;i++)
#define Rep(i,__,___) for(int i=__;i>=___;i--)
#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>

#define bi BigInt
typedef long long ll;
#define pi 3.1415926535897
//------START-----------//
struct merg
{
    ll from,to,plus1;
    merg(ll _from, ll _to, ll _plus1)
    {
        from=_from;
        to=_to;
        plus1=_plus1;
    }
};
struct dsundo
{
	ll n,par[1000100],h[1000100],sz[1000100];
	vector<merg> bruh;
	dsundo (ll n)
	{
		for (ll i=1;i<=n;i++)
		{
			par[i]=i;
			sz[i]=1;
			h[i]=1;
		}
		this->n=n;
		bruh.clear();
	}
	void reset(ll n)
	{
		for (ll i=1;i<=n;i++)
		{
			par[i]=i;
			sz[i]=1;
			h[i]=1;
		}
		this->n=n;
		bruh.clear();
	}
	ll get_par(ll x)
	{
		if (par[par[x]]==par[x]) return par[x];
		else return par[x]=get_par(par[x]);
	}
	ll check_same(ll a, ll b)
	{
		return (get_par(a)==get_par(b));
	}
	ll add_edge(ll a, ll b)
	{
		ll ha=get_par(a),hb=get_par(b);
		if (ha!=hb)
		{
			if (h[ha]<h[hb])
			{
				par[ha]=hb;
				bruh.emplace_back(ha,hb,0);
			}
			else
			if (h[ha]>h[hb])
			{
				par[hb]=ha;
				bruh.emplace_back(hb,ha,0);
			}
			else
			{
				par[hb]=ha;
				h[ha]++;
				bruh.emplace_back(hb,ha,1);
			}
			return 1;
		}
		else return 0;
	}
	void undo()
	{
	    merg pp=bruh[bruh.size()-1];
	    par[pp.from]=pp.from;
	    if (pp.plus1) h[pp.to]--;
		bruh.pop_back();
	}
};