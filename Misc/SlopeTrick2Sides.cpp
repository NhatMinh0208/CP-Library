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
struct slope_func_left 
{
	public:
	ll a,b,shft;
	priority_queue<ll> bp;
	slope_func_left(ll aa=0, ll bb=0, vector<ll> v={})
	{
		a=aa;
		b=bb;
		shft=0;
		for (ll g : v) bp.push(g);
	}
	void reset (ll aa, ll bb, vector<ll> v)
	{
	    a=aa;
	    b=bb;
	    shft=0;
		for (ll g : v) bp.push(g);
	}
	void slope_add (ll aa, ll bb, vector<ll> v)
	{
		a+=aa;
		b+=bb+aa*shft;
		for (ll g : v) bp.push(g-shft);
	}	
	void add_shift(ll a)
	{
	    shft+=a;
	}
	void slope_min()
	{
		while(a+bp.size()>0) bp.pop();
	}
};

struct slope_func_right
{
	public:
	ll a,b,shft;
	priority_queue<ll, vector<ll>,greater<ll>> bp;
	slope_func_right(ll aa=0, ll bb=0, vector<ll> v={})
	{
		a=aa;
		b=bb;
		shft=0;
		for (ll g : v) bp.push(g);
	}
	void reset (ll aa, ll bb, vector<ll> v)
	{
	    a=aa;
	    b=bb;
	    shft=0;
		for (ll g : v) bp.push(g);
	}
	void slope_add (ll aa, ll bb, vector<ll> v)
	{
		a+=aa;
		b+=bb-aa*shft;
		for (ll g : v) bp.push(g-shft);
	}	
	void add_shift(ll aa)
	{
	    shft+=aa;
	}
	void slope_min()
	{
		while(a+bp.size()>0) bp.pop();
	}
};
ll n,m,i,j,k,u,v,t,t1,a,b,l,r,ress=0;
ll al[100001],ar[100001];
slope_func_left le; slope_func_right ri;
//------END-----------//
int main()
{
//    ofile;
    fio;
    cin>>n;
    for (i=1;i<=n;i++) cin>>al[i]>>ar[i];
    le.reset(0,0,{});
    ri.reset(0,0,{});
    for (i=1;i<=n;i++)
    {
        if (i>1)
        {
        le.add_shift(-(ar[i]-al[i]));
        ri.add_shift((ar[i-1]-al[i-1]));
        }
    //    if (i>1) cout<<le.bp.top()<<endl;
        if ((le.bp.size()==0)or(al[i]<le.bp.top()+le.shft))
        {
        le.slope_add(-1,al[i],{al[i],al[i]});
        ll bruh=le.bp.top()+le.shft;
     //   cout<<"left to right "<<bruh<<endl;
        le.bp.pop();
        ri.slope_add(0,0,{bruh});
        }
        else
        {
            ri.slope_add(0,0,{al[i],al[i]});
            ll bruh=ri.bp.top()+ri.shft;
    //    cout<<"right to left "<<bruh<<endl;
            ri.bp.pop();
            le.slope_add(-1,al[i],{bruh});
        }
    }
   // cout<<le.a<<' '<<le.b<<endl;
    ll res=le.b;
    for (i=0;i<abs(le.a);i++)
    {
        ll x=le.bp.top()+le.shft;
        le.bp.pop();
        ll y;
        if (i==abs(le.a)-1) y=le.shft; else y=le.bp.top()+le.shft;
  //      cout<<i<<' '<<x<<' '<<y<<endl;
        res-=(i+1)*(x-y);
    }
    cout<<res;
}
// 2 5
// -2 2