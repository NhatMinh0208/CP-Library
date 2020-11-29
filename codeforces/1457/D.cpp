#include <bits/stdc++.h>
using namespace std;
int arr[200001],pre[200001],bc[1000001][30];
int n,m,i,j,k,t,t1,u,v,a,b;
int p;
int check(int x)
{
    for (int i=0;i+x<=n;i++)
    {
        for (int j=29;j>=0;j--)
        {
        if ((pre[i]&(1<<j))<(pre[i+x]&(1<<j)))
        {
            if (bc[i+x-1][j]-bc[i][j]>0) return 1;
            else break;
        }
        else if ((pre[i]&(1<<j))>(pre[i+x]&(1<<j)))
        {
            if (bc[i+x-1][j]-bc[i][j]<x-1) return 1;
            else break;
        }
        }
    }
    return 0;
}
int bs(int l, int r)
{
    if (l==r) return l;
    int mid=(l+r)/2;
    if (check(l)) return bs(l,l); else return bs(l+1,r);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    if (n>60) return cout<<1,0;
    for (i=1;i<=n;i++)
    {
        cin>>u;
        pre[i]=pre[i-1]^u;
        for (j=29;j>=0;j--)
        {
            bc[i][j]=bc[i-1][j]+((pre[i]&(1<<j))>0);
        }
    }
    int res=bs(2,n+1);
    if (res==n+1) cout<<-1; else cout<<res-2;
}