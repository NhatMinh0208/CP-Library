
// Problem : E. Wrong Floyd
// Contest : Codeforces - Codeforces Round #203 (Div. 2)
// URL : https://codeforces.com/problemset/problem/350/E
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
/*
The whole thing literally dented the LCL's reputation, like seriously why the fuck were they 
allowed to compete in the first place, they were literally a bunch of diamonds, i remember when this roster was first announced, 
some people already predicted that its gonna flop, yet you had some morons arguing that people are being sexist lol
*/
int n,m,k,c[501],pos[100001],t,t1,i,j;
#define LL long long
#define INF 0x3f3f3f3f
#define db double
const int maxn = 2010;
const LL mod = 1000000007;
LL dp[maxn][maxn], sum[maxn];
string s;
int main() {
	fio;
	int n, k;
	cin>>n>>k;
	cin>>s;
	s=' '+s;
	dp[0][0] = 1;
	sum[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			for (int l = i - 1; l >= 0 && j - (n - i + 1) * (i - l) >= 0; l--) {
				dp[i][j] = (dp[i][j] + ((LL)('z' - s[i]) * dp[l][j - (n - i + 1) * (i - l)]) % mod) % mod;
			}
			dp[i][j] = (dp[i][j] + ((LL)(s[i] - 'a') * sum[j]) % mod) % mod;
			sum[j] = (sum[j] + dp[i][j]) % mod;
		}
	}
	LL ans = 0;
	for (int i = 0; i <= n; i++) {
		ans = (ans + dp[i][k]) % mod;	
	}
	cout<<ans;
}