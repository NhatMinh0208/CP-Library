/*
 A Submission by $%U%$
 at time: $%Y%$-$%M%$-$%D%$ $%h%$:$%m%$:$%s%$
*/
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define rep(i,n) for(int64_t i=0;i < (int64_t)(n);i++)
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
#define fi first
#define se second
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
ll n,m,x,k,y,arr[200001],pos[200001],brr[200001],t,t1,i,j,res=0;
ll solve (ll l, ll r, ll lim)
{
	if (l>r) return 0;
	ll maxx=0;
	for (ll i=l;i<=r;i++) maxx=max(maxx,arr[i]);
	if (maxx<lim)
	{
		if (x<k*y) return (r-l+1)/k*x+(r-l+1)%k*y;
		else return (r-l+1)*y;
	}
	else
	{
		if (r-l+1<k) return 1e17;
		else  
		if (x<k*y) return (r-l+1)/k*x+(r-l+1)%k*y;
		else return (r-l+1-k)*y+x;
	}
}
int main()
{
//  ofile;
    fio;
    cin>>n>>m;
    cin>>x>>k>>y;
    for (i=1;i<=n;i++)
    {
    	cin>>arr[i];
    	pos[arr[i]]=i;
    }
    for (i=1;i<=m;i++)
    {
    	cin>>brr[i];
    	if ((i>1)and(pos[brr[i]]<pos[brr[i-1]])) return cout<<-1,0;
    }
    res+=solve(1,pos[brr[1]]-1,brr[1]);
    res=min(res,1e17);
    for (i=2;i<=m;i++) {res+=solve(pos[brr[i-1]]+1,pos[brr[i]]-1,max(brr[i-1],brr[i])); res=min(res,1e17); 
    }
    res+=solve(pos[brr[m]]+1,n,brr[m]);res=min(res,1e17); 
    if (res>=1e17) cout<<-1; else cout<<res;
}
