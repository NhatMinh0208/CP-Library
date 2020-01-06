#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long int
#define pb push_back
#define MAX 35
#define f first
#define s second
 
vector<ll> g[MAX];
vector< pair<ll,ll> > vec(MAX);
ll deg[MAX]={0};
ll mp[4]={2,3,0,1};
ll dx[4]={1,0,-1,0};
ll dy[4]={0,-1,0,1};
ll dist;
 
void dfs(ll u,ll pu,ll dirx,ll diry,ll come)
{
    ll i,v,cnt=0;
 
    if( pu==-1 )
    {
        vec[u].f=0;
        vec[u].s=0;
    }
    else
    {
        vec[u].f=vec[pu].f+dist*dirx;
        vec[u].s=vec[pu].s+dist*diry;
        dist=dist/2;
    }
    for(i=0;i<g[u].size();i++)
    {
        v=g[u][i];
        if( v==pu )
            continue;
        if( cnt==come )
            cnt=(cnt+1)%4;
        dfs(v,u,dx[cnt],dy[cnt],mp[cnt]);
        cnt=(cnt+1)%4;
    }
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	cout.tie(0);
    ll n,i,u,v;
 
    cin>>n;
    for(i=1;i<n;i++)
    {
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
        deg[u]++;
        deg[v]++;
    }
    for(i=1;i<=n;i++)
    {
        if( deg[i]>4 )
        {
            cout<<"NO\n";
            return 0;
        }
    }
    dist=(1LL<<30LL);
    dfs(1,-1,0,0,-1);
    cout<<"YES\n";
    for(i=1;i<=n;i++)
        cout<<vec[i].f<<" "<<vec[i].s<<"\n";
 
}