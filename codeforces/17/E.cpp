#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define P 51123987
#define maxn 4000005
 
int N,M=1,f[maxn],l[maxn],r[maxn],ans;
char a[maxn],b[maxn];
 
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    cin>>N>>a;
    b[0]=1;
    for (int i=0; i<N; i++) b[++M]=a[i],M++;
    for (int i=1,p=0,q=0; i<=M; i++)
    {
        f[i]=q>i?std::min(f[2*p-i],q-i):1;
        for (;b[i+f[i]]==b[i-f[i]]; f[i]++);
        if (i+f[i]>q) p=i,q=i+f[i];
    }
    for (int i=1; i<=M; i++) l[i-f[i]+1]++,l[i+1]--,r[i]++,r[i+f[i]]--,(ans+=f[i]/2)%=P;
    ans=1ll*ans*(ans-1)/2%P;
    for (int i=1,s=0; i<=M; i++)
    {
        l[i]+=l[i-1],r[i]+=r[i-1];
        if (i%2==0) (ans-=1ll*s*l[i]%P)%=P,(s+=r[i])%=P;
    }
    cout<<((ans+P)%P)<<"\n";
}