#include <bits/stdc++.h>
using namespace std;
vector<int> gt[200001];
int used[200001];
int matched[200001];
int n,m,i,j,k,t,t1,u,v,a,b;
vector<int> res1,res2;
int augment(int u)
{
	if (used[u]) return 0;
	used[u]=1;
	for (int v : gt[u])
	{
		if ((matched[v]==-1)or(augment(matched[v])))
		{
			matched[v]=u;
			return 1;
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b>>m;
	for (i=a;i<a+b;i++)
	{
		matched[i]=-1;
	}
	for (i=0;i<m;i++)
	{
		cin>>u>>v;
		gt[u].push_back(a+v);
		gt[a+v].push_back(u);
	}
	for (i=0;i<a;i++) 
	{
		for (j=0;j<a+b;j++) used[j]=0;
		augment(i);
	}
	for (i=a;i<a+b;i++)
	{
		if (matched[i]!=-1) k++;
	}
	cout<<k<<endl;
	for (i=a;i<a+b;i++)
	{
		if (matched[i]!=-1) cout<<matched[i]<<' '<<i-a<<endl;
	}
}
