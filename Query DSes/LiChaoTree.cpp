/*
    Normie's template for dynamic Li Chao tree.
    Version 2: Now allows adding a function to a particular range.
    Works for x=integers from -2e12 to 2e12.
    Tested with library_checker and almost all problems in cp-algorithms.
    This specific version tested with VNOI Online 2016 - MARIO.
*/

// Standard library in one include.
#include <bits/stdc++.h>
using namespace std;

// ordered_set library.
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update>

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

//Constants.
#define MOD (ll(1000000007))
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
#define For(i,__,___) for(int i=__;i<=___;i++)
#define Rep(i,__,___) for(int i=__;i>=___;i--)

//Typedefs.
#define bi BigInt
typedef long long ll;

//---------END-------//
struct node
{
	node *nl=0, *nr=0;
	ll dom=0;
	~node()
	{
		if (nl) delete(nl);
		if (nr) delete(nr);
	}
};
struct dynamic_li_chao
{
	vector<pii(ll)> func={{0,-3e18-7}};
	ll calc (ll cur, ll x)
	{
		return (func[cur].fi)*x+(func[cur].se);
	}
	node start;
	void add_line(ll a, ll b, ll l, ll r)
	{
		func.emplace_back(a,b);
		update(-1e9,1e9+1,&start,func.size()-1,l,r);
	}
	void update(ll l, ll r, node* cur, ll diff , ll tl, ll tr)
	{
		if ((l>=tl)and(r-1<=tr))
		{
		if (cur->dom==0)
		{
			cur->dom=diff;
		}
		else if (l+1==r) 
		{
			if (calc(cur->dom,l)<calc(diff,l))
			cur->dom=diff;
		}
		else
		{
			ll mid=(l+r)/2;
			ll doml=(calc(cur->dom,l)<calc(diff,l));
			ll domm=(calc(cur->dom,mid)<calc(diff,mid));
			if (domm)
			{
				ll z=cur->dom;
				cur->dom=diff;
				diff=z;
			}
			if (doml==domm)
			{
				if (!cur->nr) cur->nr=new(node);
				update(mid,r,cur->nr,diff,tl,tr);
			}
			else
			{
				if (!cur->nl) cur->nl=new(node);
				update(l,mid,cur->nl,diff,tl,tr);
			}
		}
		}
		else if ((l>tr)or(r-1<tl)) return;
		else
		{
			ll mid=(l+r)/2;
			if (!cur->nr) cur->nr=new(node);
			update(mid,r,cur->nr,diff,tl,tr);
			if (!cur->nl) cur->nl=new(node);
			update(l,mid,cur->nl,diff,tl,tr);
		}
	}
	ll get(ll x)
	{
		return getK(-1e9,1e9+1,&start,x);
	}
	ll getK(ll l, ll r, node* cur, ll tar)
	{
		ll res1=calc(cur->dom,tar);
		if (l+1==r) return res1;
		ll res2=-3e18-7;
		ll mid=(l+r)/2;
		if ((tar<mid)and(cur->nl)) res2=getK(l,mid,cur->nl,tar); 
		else if ((tar>=mid)and(cur->nr)) res2=getK(mid,r,cur->nr,tar);
		return max(res1,res2);
	}
};
dynamic_li_chao bruh;
ll n,m,i,j,k,res;
ll u,a,b,x,w,e;
ll dp[100001];
int main()
{
	fio;
	cin>>n;
	dp[0]=0;
	bruh.add_line(0,0,-1e9,1e9);
	for (i=1;i<=n;i++)
	{
		cin>>x>>w>>e;
		a=bruh.get(x);
		dp[i]=a+e;
		bruh.add_line(-w,dp[i]-x*(-w),x,1e9);
		bruh.add_line(w,dp[i]-x*(w),-1e9,x);
		res=max(res,dp[i]);
	}
	cout<<res;
}


