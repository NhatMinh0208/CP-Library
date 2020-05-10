
// Problem : E. Camels
// Contest : Codeforces - Codeforces Beta Round #14 (Div. 2)
// URL : https://codeforces.com/problemset/problem/14/E
// Memory Limit : 64 MB
// Time Limit : 2000 ms
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
ll m,k,c[501],pos[100001],t,t1,i,j;
ll n,dp[31][31][31][5][5];
 
int main(){
	fio;
	cin>>n>>t;
	for (i=0;i<=4;i++) for (j=0;j<=4;j++) dp[0][0][0][i][j]=1;
	for (i=1;i<=n;i++) for (j=0;j<=t;j++) for (k=0;k<=t;k++) for (int pr1=0;pr1<=4;pr1++) for (int pr2=0;pr2<=4;pr2++)
	for (int cur=1;cur<=4;cur++)
	{
		if ((cur!=pr1))
		{
		if ((pr1*pr2)and(pr1>cur)and(pr1>pr2))
		{
			if (j) dp[i][j][k][pr1][pr2]+=dp[i-1][j-1][k][cur][pr1];
		}
		else if ((pr1*pr2)and(pr1<cur)and(pr1<pr2))
		{
			if (k) dp[i][j][k][pr1][pr2]+=dp[i-1][j][k-1][cur][pr1];
		}
		else
		{
			dp[i][j][k][pr1][pr2]+=dp[i-1][j][k][cur][pr1];
		}
		}
	}
	cout<<dp[n][t][t-1][0][0];
}

