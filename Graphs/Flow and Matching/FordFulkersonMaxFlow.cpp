#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define fi first
#define se second
ll n,m,i,j,k,t,u,v,a,b,cmin=0;
ll dp[1001][101];
ll dis[1001],used[1001];
unordered_map<ll,ll> gt[1001];
ll dfs(ll x, ll d)
{
//	cout<<"dfs "<<x<<' '<<d<<endl;
	used[x]=1;
	if (x==1000) return d;
	for (pll g : gt[x])
	{
//		cout<<"trans "<<g.fi<<' '<<g.se<<endl;
		if ((!used[g.fi])and(g.se))
		{
			ll u=dfs(g.fi,min(g.se,d));
			if (u)
			{
				gt[x][g.fi]-=u;
				gt[g.fi][x]+=u;
				return u;
			}
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for (i=1;i<=n;i++)
	{
		cin>>u;
		if (u>0)
		{
			gt[999][i]=u;
			gt[i][999]=0;
			cmin+=u;
		}
		else if (u<0)
		{
			gt[i][1000]=-u;
			gt[1000][i]=0;
		}
	}
	cin>>m;
	for (i=1;i<=m;i++)
	{
		cin>>u>>v;
		gt[u][v]=1000000000000;
		gt[v][u]=0;
	}
	while(v=dfs(999,1000000000000))
	{
//		cout<<v<<endl;
		cmin-=v;
		for (i=1;i<=1000;i++) used[i]=0;
	}
	cout<<cmin;
}
