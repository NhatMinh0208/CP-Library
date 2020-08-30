
// Problem : Stoned Game
// Contest : Codeforces
// URL : https://m1.codeforces.com/contest/1396/problem/B
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

/*
 A Submission by $%U%$
 at time: $%Y%$-$%M%$-$%D%$ $%h%$:$%m%$:$%s%$
*/
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define fef(i,a,b) for(ll i=a;i<=b;i++)
#define rer(i,a,b) for(ll i=b;i>=a;i--)
#define wew while(true)
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FILE_IN "cseq.inp"
#define FILE_OUT "cseq.out"
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
#define pow2(x) (ll(1)<<x)
#define pii pair<int,int>
#define piii pair<int,pii>
#define For(i,__,___) for(int i=__;i<=___;i++)
#define Rep(i,__,___) for(int i=__;i>=___;i--)
#define ordered_set tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update>
#define endl "\n"
#define bi BigInt
typedef long long ll;
//---------END-------//
int n,m,k,c[501],h[100001],t,t1,i,j,l0,l1;
struct cmp
{
	int operator() (int a, int b)
	{
		if (h[a]-h[b]) return (h[a]>h[b]);
		return (a>b);
	}
};
set<int,cmp> se;
int main()
{
//  ofile;
    fio;
    cin>>t;
    for (t1=0;t1<t;t1++)
    {
    	cin>>n;
    	se.clear(); l1=0;l0=0;
    	for (i=1;i<=n;i++) cin>>h[i];
    	for (i=1;i<=n;i++) se.insert(i);
    	while(true)
    	{
    		auto it=se.begin();
    		int pick=(*it);
    		if (((pick)!=l1)and(h[pick]))
    		{
    			l0=pick;
    			se.erase(pick);
    			h[pick]--;
    			se.insert(pick);
    		}
    		else
    		{
    			it++;
    			if (it==se.end())
    			{
    				cout<<"HL\n"; break;
    			}
    			else
    			{
    				pick=(*it);
    		if (((pick)!=l1)and(h[pick]))
    		{
    			l0=pick;
    			se.erase(pick);
    			h[pick]--;
    			se.insert(pick);
    		}
    		else
    		{
    				cout<<"HL\n"; break;
    		}
    			}
    		}
    		it=se.begin();
    		pick=(*it);
    		if (((pick)!=l0)and(h[pick]))
    		{
    			l1=pick;
    			se.erase(pick);
    			h[pick]--;
    			se.insert(pick);
    		}
    		else
    		{
    			it++;
    			if (it==se.end())
    			{
    				cout<<"T\n"; break;
    			}
    			else
    			{
    				pick=(*it);
    		if (((pick)!=l0)and(h[pick]))
    		{
    			l1=pick;
    			se.erase(pick);
    			h[pick]--;
    			se.insert(pick);
    		}
    		else
    		{
    				cout<<"T\n"; break;
    		}
    			}
    		}
    	}
    }
}
