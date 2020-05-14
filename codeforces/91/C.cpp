
// Problem : C. Ski Base
// Contest : Codeforces - Codeforces Beta Round #75 (Div. 1 Only)
// URL : https://codeforces.com/problemset/problem/91/C
// Memory Limit : 256 MB
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
#define pb push_back
#define mp make_pair
#define ld long double
#define F first
#define S second
//---------END-------//
using namespace :: std;
const ll maxn=1e5+500;
const ll mod=1e9+9;
const ll inf=1e9+500;
ll par[maxn];
ll find_par(ll a){
	if(par[a]==a){
		return a;
	}
	return par[a]=find_par(par[a]);
}	
int main(){
	ll n,m;
	cin>>n>>m;
	for(ll i=0;i<n;i++){
		par[i]=i;
	}
	ll ans=1;
	for(ll i=0;i<m;i++){
		ll a,b;
		cin>>a>>b;
		a--;
		b--;
		a=find_par(a);
		b=find_par(b);
		if(a==b){
			ans*=2;
			ans%=mod;
		}
		else{
			par[a]=b;
		}
		cout<<(ans-1+mod)%mod<<endl;
	}
}