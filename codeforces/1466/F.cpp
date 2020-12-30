/*
	Normie's Template v2.0
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
#define ff(i,__,___) for(int i=__;i<=___;i++)
#define rr(i,__,___) for(int i=__;i>=___;i--)
 
//Typedefs.
#define bi BigInt
typedef long long ll;
typedef long double ld;
typedef short sh;
//---------END-------//
vector<int> buc[500001];
int par[500001];
int n,m,i,j,k,t,t1,u,v,a,b;
vector<pii(int)> edge;
vector<int> lis;
int pw[500011];
ll res=1;
int main()
{
	cin>>n>>m;
	for (i=1;i<=n;i++)
	{
		cin>>j;
		if (j==1)
		{
			cin>>u;
			edge.push_back({0,u});
		}
		else
		{
			cin>>u>>v;
			edge.push_back({v,u});
		}
	}
	pw[0]=1;
	for (i=0;i<=m;i++)
	{
		pw[i+1]=pw[i]*2;
		pw[i+1]%=MOD;
		par[i]=i;
		buc[i]={i};
	}
	for (i=1;i<=n;i++)
	{
		u=par[edge[i-1].fi];
		v=par[edge[i-1].se];
		if (u!=v)
		{
			lis.push_back(i);
			if (buc[u].size()>buc[v].size())
			{
				for (int g : buc[v])
				{
					par[g]=u;
					buc[u].push_back(g);
				}
				buc[v].clear();
			}
			else
			{
				for (int g : buc[u])
				{
					par[g]=v;
					buc[v].push_back(g);
				}
				buc[u].clear();
			}
		}
	}
	for (i=0;i<=m;i++) if (par[i]==i) 
	{
		res*=pw[buc[i].size()-1];
		res%=MOD;
	}
	cout<<res<<' '<<lis.size()<<endl;
	for (int g : lis) cout<<g<<' ';
}