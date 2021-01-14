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
struct cmp
{
	int operator()(pii(ll) a, pii(ll) b) const
	{
		return (a.se>b.se);
	}
};
priority_queue<pii(ll),vector<pii(ll)>,cmp> pq;
ll n,m,i,j,k,t,t1,u,v,a,b,dis[800001];
vector<pii(ll)> gt[800001];
int main()
{
	fio;
	cin>>n>>m;
	for (i=1;i<=m;i++)
	{
		cin>>u>>v>>a;
		u--;
		v--;
		gt[4*u].push_back({4*v,a});
		gt[4*u].push_back({4*v+1,0});
		gt[4*u].push_back({4*v+2,2*a});
		gt[4*u].push_back({4*v+3,a});
		gt[4*u+1].push_back({4*v+1,a});
		gt[4*u+1].push_back({4*v+3,2*a});
		gt[4*u+2].push_back({4*v+2,a});
		gt[4*u+2].push_back({4*v+3,0});
		gt[4*u+3].push_back({4*v+3,a});
		
		
		gt[4*v].push_back({4*u,a});
		gt[4*v].push_back({4*u+1,0});
		gt[4*v].push_back({4*u+2,2*a});
		gt[4*v].push_back({4*u+3,a});
		gt[4*v+1].push_back({4*u+1,a});
		gt[4*v+1].push_back({4*u+3,2*a});
		gt[4*v+2].push_back({4*u+2,a});
		gt[4*v+2].push_back({4*u+3,0});
		gt[4*v+3].push_back({4*u+3,a});
	}
	for (i=0;i<4*n;i++) dis[i]=1e18;
	dis[0]=0;
	pq.push({0,0});
	while(pq.size())
	{
		auto g=pq.top();
		pq.pop();
		if (g.se==dis[g.fi])
		{
			for (auto pp : gt[g.fi])
			{
				if (g.se+pp.se<dis[pp.fi])
				{
					dis[pp.fi]=g.se+pp.se;
					pq.push({pp.fi,dis[pp.fi]});
				}
			}
		}
	}
	for (i=1;i<n;i++) cout<<dis[4*i+3]<<' ';
} 