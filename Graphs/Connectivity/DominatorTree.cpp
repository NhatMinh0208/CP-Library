/*
	Dominator Tree v1.0
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
struct seg
{
	ll arr[1000001];
	void reset(ll c, ll l, ll r)
	{
		arr[c]=1e18;
		if (l<r)
		{
			ll mid=(l+r)/2;
			reset((c<<1),l,mid);
			reset((c<<1)+1,mid+1,r);
		}
	}
	ll get(ll c, ll l, ll r, ll t)
	{
		if ((l<=t)and(t<=r))
		{
			ll a=arr[c];
			if (l<r)
			{
				ll mid=(l+r)/2;
				ll aa=get((c<<1),l,mid,t);
				ll bb=get((c<<1)+1,mid+1,r,t);
				return min(a,min(aa,bb)); 
			}
			else return a;
		}
		else return 1e18;
	}
	void upd(ll c, ll l, ll r, ll tl, ll tr, ll x)
	{
		if ((l>tr)or(r<tl)) return;
		else if ((l>=tl)and(r<=tr)) arr[c]=min(arr[c],x);
		else
		{
			ll mid=(l+r)/2;
			upd((c<<1),l,mid,tl,tr,x);
			upd((c<<1)+1,mid+1,r,tl,tr,x);
		//	return min(a,b);
		}
	}
	////////////////////////////////
	ll get(ll c, ll l, ll r, ll tl, ll tr)
	{
	//	cout<<"st get "<<c<<' '<<l<<' '<<r<<' '<<tl<<' '<<tr<<endl;
		if ((l>tr)or(tl>r)) return 1e18;
		if ((tl<=l)and(tr>=r)) return arr[c];
		else
		{
			ll mid=(l+r)/2;
			ll aa=get((c<<1),l,mid,tl,tr);
			ll bb=get((c<<1)+1,mid+1,r,tl,tr);
			return min(aa,bb); 
		}
		//else return 1e18;
	}
	void upd(ll c, ll l, ll r, ll t, ll x)
	{
	//	cout<<"st upd "<<c<<' '<<l<<' '<<r<<' '<<t<<' '<<x<<endl;
		if ((l<=t)and(t<=r))
		{
			if (l==r) arr[c]=x;
			else
			{
				ll mid=(l+r)/2;
				upd((c<<1),l,mid,t,x);
				upd((c<<1)+1,mid+1,r,t,x);
				arr[c]=min(arr[(c<<1)],arr[(c<<1)+1]);
			}
		}
	}
};
#define dec decc
seg st;
vector<ll> gt[200001],gtr[200001],vec;
ll tl[200001],tr[200001],par[200001];
ll dec[200001];
ll sdom[200001],idom[200001];
ll n,m,s,i,j,k,t,t1,u,v,a,b;
void ini(ll x, ll p)
{
	t++;
	tl[x]=t;
	dec[t]=x;
	par[x]=p;
	for (auto g : gt[x]) if (!tl[g]) ini(g,x);
	tr[x]=t;
}
int main()
{
	fio;
	cin>>n;
	cin>>m;
	cin>>s;
	s++;
	for (i=1;i<=n;i++) idom[i]=0;
	for (i=1;i<=m;i++)
	{
		cin>>u>>v;
		u++;
		v++;
		gt[u].push_back(v);
		gtr[v].push_back(u);
	}
	ini(s,s);
	for (i=1;i<=n;i++) if (tl[i])
	{
		for (auto g : gtr[i])
		{
	//		cout<<g<<' '<<i<<endl;
		 if ((tl[g])and(tl[g]<tl[i])and((sdom[i]==0)or(tl[sdom[i]]>tl[g]))) sdom[i]=g;
		}
	}
	st.reset(1,1,n);
	
//	for (i=1;i<=n;i++) cout<<tl[i]<<' '; cout<<endl;
//	for (i=1;i<=n;i++) cout<<tr[i]<<' '; cout<<endl;
	//for (i=1;i<=n;i++) cout<<sdom[i]<<' '; cout<<endl;
	
		

	for (i=t;i>=1;i--)
	{
		i=dec[i];
	//		cout<<i<<' ';
		
		for (auto g : gtr[i]) 
		{
			u=st.get(1,1,n,tl[g]);
		//	cout<<u<<' ';
			if ((u<1e18)and((sdom[i]==0)or(tl[sdom[i]]>u))) sdom[i]=dec[u];
		}
		st.upd(1,1,n,tl[i],tr[i],tl[sdom[i]]);
		
		i=tl[i];

	}
	
	//for (i=1;i<=n;i++) cout<<tl[i]<<' '; cout<<endl;
//	for (i=1;i<=n;i++) cout<<tr[i]<<' '; cout<<endl;
	//for (i=1;i<=n;i++) cout<<sdom[i]<<' '; cout<<endl;

	st.reset(1,1,n);
	for (i=1;i<=t;i++)
	{
		i=dec[i];
			/////////////
		while ((vec.size())and(vec[vec.size()-1]!=par[i]))
		{
			st.upd(1,1,n,tl[vec[vec.size()-1]],1e18);
			vec.pop_back();
		}
			vec.push_back(i);
			st.upd(1,1,n,tl[vec[vec.size()-1]],tl[sdom[i]]*1e9+i);
		//		cout<<"upd "<<tl[vec[vec.size()-1]]<<' '<<tl[sdom[i]]*1e9+i<<endl;
			/////////////
			if (i==s) idom[i]=s;
			else
			{
		//		cout<<"get "<<tl[sdom[i]]+1<<' '<<tl[i]<<endl;
			u=st.get(1,1,n,tl[sdom[i]]+1,tl[i]);
		//	for (auto g : vec) cout<<g<<' '; cout<<endl;
		//	cout<<i<<' '<<u<<endl;
			u%=1000000000;
			if (sdom[u]==sdom[i]) idom[i]=sdom[i];
			else idom[i]=idom[u];
			}
			/////////////
		i=tl[i];
	}

	
//	for (i=1;i<=n;i++) cout<<sdom[i]-1<<' ';
	for (i=1;i<=n;i++) cout<<idom[i]-1<<' ';
}

