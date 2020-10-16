#include <bits/stdc++.h>
using namespace std;
#define MOD (ll(1000000007))
typedef long long ll;
ll n,m,i,j,k,t,u,v,a,b;
string s;
ll lesser,greater,dp[2001][2001];
ll sum[2001];
int main()
{
    cin>>n>>k;
    cin>>s;
    for (i=n;i>=0;i--) for (j=0;j<=k;j++)
    {
        if (i==n)
        {
            if (j==0) dp[i][j]=1;
            else dp[i][j]=0;
        }
        else
        {
            dp[i][j]+=sum[j]+dp[n][j];
        }
        dp[i][j]%=MOD;
        for (t=i-1;t>=0;t--) if (j+(i-t)*(n-i+1)<=k)
        {
            dp[t][j+(i-t)*(n-i+1)]+=dp[i][j]*(26-1-(s[i-1]-97));
        } else break;
        sum[j]+=dp[i][j]*(s[i-1]-97);
        sum[j]%=MOD;
    //    cout<<i<<' '<<j<<' '<<dp[i][j]<<' '<<sum[j]<<endl;
    }
    cout<<dp[0][k];
}