#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
int n,m,i,j,k,t,t1,u,v,a,b;
int eu[500001],ev[500001];
vector<int> out_ord,hol; vector<pii> gt[500001];
int used[500001];
vector<vector<int>> res;
void dfs(int x)
{
	used[x]=1;
	for (pii g : gt[x])
	{
		if (!used[g.fi]) dfs(g.fi); 
	}
	out_ord.push_back(x);
}
void dfs2(int x)
{
	used[x]=1;
	hol.push_back(x);
	for (pii g : gt[x]) if (!used[g.fi]) dfs2(g.fi);
}
int main()
{
	cin>>n>>m;
	for (i=0;i<m;i++)
	{
		cin>>eu[i]>>ev[i];
		gt[eu[i]].push_back({ev[i],i});	
	}
	for (i=0;i<n;i++) if (!used[i])
	{
		dfs(i);
	}
	for (i=0;i<n;i++)
	{
		used[i]=0;
		gt[i].clear();
	}
	for (i=0;i<m;i++)
	{
		gt[ev[i]].push_back({eu[i],i});	
	}
	while(out_ord.size())
	{
		u=out_ord[out_ord.size()-1];
		if (!used[u])
		{
			hol.clear();
			dfs2(u);
			res.push_back(hol);
		}
		out_ord.pop_back();
	}
	cout<<res.size()<<endl;
	for (auto g : res)
	{
		cout<<g.size()<<' ';
		for (int gg : g) cout<<gg<<' ';
		cout<<endl;
	}
}
