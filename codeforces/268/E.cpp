
// Problem : E. Playlist
// Contest : Codeforces - Codeforces Round #164 (Div. 2)
// URL : https://codeforces.com/problemset/problem/268/E
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
ll n,m,k,c[501],pos[100001],t,t1,i,j,l[100001],p[100001];
double res;
vector<ll> lis;
int main()
{
//  ofile;
    fio;
    cin>>n;
    for (i=0;i<n;i++)
    {
    	cin>>l[i]>>p[i];
    	lis.push_back(i);
    }
    sort(lis.begin(),lis.end(),[](int a, int b){return (l[a]*p[a]*(100-p[b])>l[b]*p[b]*(100-p[a]));});
    for (i=n-1;i>=0;i--)
    {
    	res+=double(l[lis[i]]*p[lis[i]]*t)/10000;
    	t+=100-p[lis[i]];
    }
    for (i=0;i<n;i++) res+=l[i];
    cout<<fixed<<setprecision(10)<<res;
}
