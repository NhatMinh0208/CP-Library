#include <bits/stdc++.h>
using namespace std;
int n,m,i,j,k,t,u,t1,v,a,b,res1,res2,res3,res4,cur=0;
vector<int> gt[1001],gt2[1001];
int tin[100001],low[100001];
int banned[1001][1001];
int arti[100001];
void dfs(int x, int p)
{
	j++;
	tin[x]=j;
	low[x]=j;
	for (int g : gt[x])
	{
		if (g==p);
		else if (tin[g])
		{
			low[x]=min(low[x],tin[g]);
		}
		else
		{
			dfs(g,x);
			low[x]=min(low[x],low[g]);
			gt2[x].push_back(g);
		}
	}
	int cnt=0;
	for (int g : gt2[x])
	{
		if (tin[x]<low[g])
		{
			banned[x][g]=1;
			banned[g][x]=1;
			res1++;
		}
		if (tin[x]<=low[g]) cnt++;
	}
	if ((cnt>=2)or((cnt==1)and(x>1))) {
	res2++; arti[x]=1;}
}
void dfs2(int x)
{
	tin[x]=1;
	for (int g : gt[x]) if (!banned[x][g]) 
	{
		cur++;
		if (!tin[g]) dfs2(g);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	cur=0;
	for (t1=0;t1<t;t1++)
	{
		res1=0;
		res2=0;
		res3=0;
		res4=0;
		cin>>n>>m;
		for (i=1;i<=n;i++)
		{
			arti[i]=0;
			gt[i].clear();
			gt2[i].clear();
			tin[i]=0;
			low[i]=0;
			for (j=1;j<=n;j++) banned[i][j]=0;
		}
		for (i=1;i<=m;i++)
		{
			cin>>u>>v;
			gt[u].push_back(v);
			gt[v].push_back(u);
		}
		j=0;
		dfs(1,0);
		for (i=1;i<=n;i++)
		{
			tin[i]=0;
		}
		for (i=1;i<=n;i++) if (!tin[i])
		{
			cur=0;
			dfs2(i);
			if (cur) res3++;
			res4=max(res4,cur/2);
		}
// At this point, res1 contains the number of bridges.
// res2 contains the number of articulation points.
// banned[i][j] indicates whether (i,j) is a bridge.
// arti[i] indicates whether (i) is an articulation point.
		res3+=res1;
		res4=max(res4,1);
		cur=__gcd(res3,res4);
		res3/=cur;
		res4/=cur;
		cout<<res2<<' '<<res1<<' '<<res3<<' '<<res4<<endl;
	}
}
