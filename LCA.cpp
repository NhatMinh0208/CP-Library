#include<bits/stdc++.h>
using namespace std;
#define rmq_tar depthtour
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
typedef long long ll;
typedef pair<int,int> pii;
const int maxn=1010;
map<int,int> cnt,tmp;
struct req {long long x; long long d;};
deque<req> q;
int n,a,b,i,j,m,c,d,k,enter[100001],ext[100001],used[100001];
vector<int> gt[100001];
vector<int> eulertour,depthtour,rmq[21];
void dfs(int x, int depth)
{
	used[x]=1;
	eulertour.push_back(x);
	depthtour.push_back(depth);
	enter[x]=eulertour.size()-1;
	for (int i=0;i<gt[x].size();i++) if (!used[gt[x][i]]) 
	{
	eulertour.push_back(x);
	depthtour.push_back(depth);
	dfs(gt[x][i],depth+1);
	eulertour.push_back(x);
	depthtour.push_back(depth);
	}
	eulertour.push_back(x);
	depthtour.push_back(depth);
	ext[x]=eulertour.size()-1;
}
void buildrmq(int x)
{
if (1<<x>rmq_tar.size()) return;
if (x==0)
{
	for (int i=0;i<rmq_tar.size();i++) rmq[x].push_back(i);
}
else
{
	for (int i=0;i+(1<<x)<=rmq_tar.size();i++) 
	rmq[x].push_back((rmq_tar[rmq[x-1][i]]<rmq_tar[rmq[x-1][i+(1<<(x-1))]])?rmq[x-1][i]:rmq[x-1][i+(1<<(x-1))]);
}
buildrmq(x+1);
}
int getmin(int l, int r)
{
	int d=log2(r-l+1);
	return (rmq_tar[rmq[d][l]]<rmq_tar[rmq[d][r-(1<<d)+1]])?rmq[d][l]:rmq[d][r-(1<<d)+1];
}
void init()
{
	dfs(1,0);
	buildrmq(0);
}
int lca(int a, int b)
{
	return eulertour[getmin(min(enter[a],enter[b]),max(ext[a],ext[b]))];
}
int main()
{
	#define endl "\n"
//	freopen("pow2in.txt","r",stdin);
//	freopen("pow2out.txt","w",stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>c;
	for (d=1;d<=c;d++)
	{
		eulertour.clear();
		depthtour.clear();
		for (i=0;i<20;i++) rmq[i].clear();
	cin>>n;
	for (i=1;i<=n;i++)
	{
		enter[i]=0;
		ext[i]=0;
		used[i]=0;
		gt[i].clear();
		cin>>m;
		for (j=0;j<m;j++)
		{
			cin>>a;
			gt[i].push_back(a);
		}
	}
	init();
	cin>>k;
	cout<<"Case "<<d<<":\n";
	for (i=0;i<k;i++)
	{
		cin>>a>>b;
		cout<<lca(a,b)<<endl;
	}
	}
}
