#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pll pair<ll,ll>
#define fi first
#define se second
int n,m,i,j,k,t,u,v,a,b; ll x,t1;
int arr[1000001],pre[1000001],las[1000001];
vector<vector<ll>> mulmm(vector<vector<ll>> a, vector<vector<ll>> b)
{
	ll n=a.size();
//	cout<<a.size()<<a[0].size()<<b.size()<<b[0].size()<<endl;
	vector<vector<ll>> c=vector<vector<ll>>(n,vector<ll>(n,0));
//	cout<<c.size()<<c[0].size()<<endl;
	for (ll i=0;i<n;i++) for (ll j=0;j<n;j++) for (ll u=0;u<n;u++)
	{
//		cout<<i<<' '<<j<<' '<<u<<endl;
		c[i][j]+=a[i][u]*b[u][j];
		c[i][j]%=k;
	}
	return c;
}
vector<ll> mulvm (vector<ll> a, vector<vector<ll>> b)
{
	ll n=a.size();
	vector<ll> c=vector<ll> (n,0);
	for (ll i=0;i<n;i++) for (ll j=0;j<n;j++) 
	{
		c[j]+=a[i]*b[i][j];
		c[j]%=k;
	}
	return c;
}
vector<vector<ll>> bowm(vector<vector<ll>> a, ll x)
{
//	cout<<"bowm "<<' '<<x<<endl;
	if (x==1) return a;
	auto res=bowm(a,x/2);
	res=mulmm(res,res);
	if (x%2) res=mulmm(res,a);
	return res;
}