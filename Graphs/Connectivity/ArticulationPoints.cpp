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
#define ordered_set tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update>

// AtCoder library. (Comment out these two lines if you're not submitting in AtCoder.) (Or if you want to use it in other judges, run expander.py first.)
//#include <atcoder/all>
//using namespace atcoder;

//Pragmas (Comment out these three lines if you're submitting in szkopul.)
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

//File I/O.
#define FILE_IN "snowfall.inp"
#define FILE_OUT "snowfall.out"
#define ofile freopen(FILE_IN,"r",stdin);freopen(FILE_OUT,"w",stdout)

//Fast I/O.
#define fio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define nfio cin.tie(0);cout.tie(0)
#define endl "\n"

//Order checking.
#define ord(a,b,c) ((a>=b)and(b>=c))

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
#define For(i,__,___) for(int i=__;i<=___;i++)
#define Rep(i,__,___) for(int i=__;i>=___;i--)

//Typedefs.
#define bi BigInt
typedef long long ll;
int n,m,i,j,k,t,u,v,a,b,lim,resv,ec,uu,vv,ww;
int used[100001],eu[100001],ev[100001],ew[100001],tin[100001],low[100001];
vector<pii(int)> gt[100001]; 
vector<int> arti;
unordered_map<int,int> mp[100001];
//---------END-------//
// dfs to find articulation point.
void dfs2(int x, int p)
{
//	cout<<"dfs2 "<<x<<' '<<p<<' '<<lim<<endl;
	u++;
	tin[x]=u;
	low[x]=u;
	int added=0,children=0;
	for (pii(int) g : gt[x]) if ((g.fi!=p))
	{
		if (tin[g.fi])
		{
//			cout<<"mining low "<<x<<" with tin "<<g.fi<<endl;
			low[x]=min(low[x],tin[g.fi]);
		}
		else
		{
			dfs2(g.fi,x,lim);
			low[x]=min(low[x],low[g.fi]);
			if ((tin[x]<=low[g.fi])) 
			{
//				cout<<"add "<<x<<endl;
				if ((!added)and(p))
				{
				added=1;
				arti.push_back(x);
				}
				children++;
			}
		}
	}
	if ((!p)and(children>1)) arti.push_back(x);
}
/*
8 13 3
1 2 19
1 3 13
2 3 5
4 2 9
2 5 7
3 5 17
6 3 8
3 8 12
4 7 11
5 7 5
7 2 10
7 6 13 
8 5 16

*/
