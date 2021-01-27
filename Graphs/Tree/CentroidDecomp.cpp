/*
	Normie's implementation of centroid decomposition.
	This particular version solves a variant of 613D where you are asked to find the longest path crossing each node instead.
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
struct edge
{
	int v=0;
	int used=0;
	char c='0';
	operator<(const edge& oth)
	{
		return (v<oth.v);
	}
	edge(int vv=0, int cv='0')
	{
		v=vv;
		c=cv;
	}	
};
vector<edge> gt[100001];
vector<edge> down[100001];
int n,m,i,j,k,t,t1,u,v,a,b,res=0;
int dis[100001];
int mask[100001];
int subt[100001];
int maxx[4200000];
int fin[100001];
void get_info(int x, int d, int mk, int p)
{
//	cout<<"get_info "<<x<<' '<<d<< ' '<<mk<<' '<<p<<endl;
	dis[x]=d;
	mask[x]=mk;
	subt[x]=1;
	down[x].clear();
	for (edge g : gt[x]) if ((g.v!=p)and(g.used==0))
	{
		down[x].push_back(g);
		get_info(g.v,d+1,mk^(1<<(g.c-97)),x);
		subt[x]+=subt[g.v];
	}
}
int find_centroid(int x)
{
//	cout<<"find_centroid "<<x<<endl;
	get_info(x,0,0,-1);
	int i=x;
	int fail=0;
	int maxx=0;
	while(true)
	{
//		cout<<"procing "<<i<<" \n";
		fail=0;
		maxx=0;
		if (subt[i]*2<subt[x]) fail=1;
		for (auto g : down[i])
		{
	//		cout<<"childern:\n";
	//		cout<<g.v<<' '<<g.c<<endl; 
		if ((maxx==0)or(subt[maxx]<subt[g.v])) maxx=g.v; 
		if (subt[g.v]*2>subt[x]) fail=1;
		}
		if (!fail) return i;
		i=maxx;
	}
}


void calc(int x, int u)
{
	fin[x]=max(fin[x],maxx[mask[x]]+dis[x]);
	fin[u]=max(fin[u],maxx[mask[x]]+dis[x]);
	for (int i=0;i<22;i++)
	{	
	fin[x]=max(fin[x],maxx[mask[x]^(1<<i)]+dis[x]);
	fin[u]=max(fin[u],maxx[mask[x]^(1<<i)]+dis[x]);
}
	for (edge g : down[x]) 
	{
		calc(g.v,u);
		fin[x]=max(fin[x],fin[g.v]);
	}
}




void add(int x)
{
	maxx[mask[x]]=max(maxx[mask[x]],dis[x]);
	for (edge g : down[x])
	{
		add(g.v);
	}
}





void del(int x)
{
	maxx[mask[x]]=-1e9;
	for (edge g : down[x])
	{
		del(g.v);
	}
}


void solve(int x)
{
	int done=0;
	for (edge g : gt[x]) if (g.used==0) done=1;
	if (!done) return;
	int u=find_centroid(x);
//	cout<<"found centroid "<<u<<" in subtree of "<<x<<endl;
	
	
	// actual solving lmao
	get_info(u,0,0,-1);
	
	for (int i=0;i<down[u].size();i++)
	{
		del(down[u][i].v);
	}
	maxx[0]=0;
	for (int i=0;i<down[u].size();i++)
	{
		calc(down[u][i].v,u);
		add(down[u][i].v);
	}
	
	
	for (int i=down[u].size()-1;i>=0;i--)
	{
		del(down[u][i].v);
	}
	maxx[0]=0;
	for (int i=down[u].size()-1;i>=0;i--)
	{
		calc(down[u][i].v,u);
		add(down[u][i].v);
	}
	
	
	// Recurse
	for (auto g : gt[u]) if (!g.used)
	{
		g.used=1;
		auto it=lower_bound(gt[g.v].begin(),gt[g.v].end(),edge(u));
		it->used=1;
		solve(g.v);
	}
}
int main()
{
	cin>>n;
	for (i=0;i<(1<<22);i++) maxx[i]=-1e9;
	for (i=2;i<=n;i++)
	{
		char c;
		cin>>u>>c;
		gt[i].emplace_back(u,c);
		gt[u].emplace_back(i,c);
	}
	for (i=1;i<=n;i++) sort(gt[i].begin(),gt[i].end());
	solve(1);
	for (i=1;i<=n;i++) cout<<fin[i]<<' ';
}
