#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int arr[100005];
int m;
int n;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
   cin>>n;
   for(int i=1;i<=n;i++)cin>>arr[i];
   cin>>m;
   while(m--)
   {
       int t;
       cin>>t;
       if(t&1)
       {
           int l,r;
           cin>>l>>r;
           ll ans=0;
           for(;l<=r;l++)ans+=arr[l];cout<<ans<<"\n";
       }
       else
       {
           int l,r,x;
           cin>>l>>r>>x;
           for(;l<=r;l++)arr[l]^=x;
       }
       
   }
}
