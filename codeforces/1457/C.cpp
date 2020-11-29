#include <bits/stdc++.h>
using namespace std;
int arr[100001],cnt0[100001];
int n,m,i,j,k,t,t1,u,v,a,b;
int p;
int main()
{
    cin>>t;
    for (t1=0;t1<t;t1++)
    {
        cin>>n;
        cin>>p>>k;
        p--;
        for (i=0;i<n;i++) {char c; cin>>c; arr[i]=c-48;}
        cin>>a>>b;
        int res=2e9;
        for (i=0;i<k;i++) cnt0[i]=0;
        for (i=n-1;i>=p;i--)
        {
            cnt0[i%k]+=1-arr[i];
            res=min(res,(i-p)*b+cnt0[i%k]*a);
        }
        cout<<res<<endl;
    }
}