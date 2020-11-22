#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define rep(i,n) for(int64_t i=0;i < (int64_t)(n);i++)
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FILE_IN "petrol.inp"
#define FILE_OUT "petrol.out"
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
#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
#define endl "\n"
typedef long long ll;
//-------------HASH----------//
//-------------END-----------//
int n,m,i,j,k,t,t1,p,aad,bad,bruh[30],maxx=0,istree,pathcnt=0;
int pos[1001][1001],dp[1001],tab[11]={2,3,5,7,11,13,17,19,23,29,31};
ordered_set s;
vector<int> gt[1001]; pii pathfather[1001]; pii path[1001]; int siz[1001];
vector<int> hld;
int cntsize(int cur, int prev)
{
    siz[cur]=1;
    for (int i=0;i<gt[cur].size();i++)
    {
        int a=gt[cur][i];
        if (a!=prev) siz[cur]+=cntsize(a,cur);
    }
    return siz[cur];
}
int dfs(int cur, int prev)
{
    hld.push_back(cur);
    int cnt=0;
    path[cur]={pathcnt,hld.size()-1};
    for (int i=0;i<gt[cur].size();i++)
    {
        int a=gt[cur][i];
        if (a!=prev) 
        {
            if (cnt)
            {
               pathcnt++;
               pathfather[pathcnt]={path[cur].fi,cur};
            }
            dfs(a,cur);
            cnt++;
        }
    }
    return siz[cur];
}
int main(){
    nfio;
    cin>>n;
    for (i=0;i<n-1;i++)
    {
        cin>>aad>>bad;
        gt[aad].push_back(bad);
        gt[bad].push_back(aad);
    }
    cntsize(1,1);
    for (i=1;i<=n;i++) sort(gt[i].begin(),gt[i].end(),[](int a, int b){return (siz[a]>siz[b]);});
    pathcnt=1;
    dfs(1,1);
    for (i=0;i<n;i++) cout<<hld[i]<<' ';
    cout<<endl;
    for (i=1;i<=n;i++) cout<<path[i].fi<<' ';
    cout<<endl;
    for (i=1;i<=pathcnt;i++) cout<<pathfather[i].fi<<' '<<pathfather[i].se<<endl;
}



