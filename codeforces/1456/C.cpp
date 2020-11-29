#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,i,j,k,t,u,v,a,b,res;
ll arr[500001];
ll pre[500001];
int main()
{
	cin>>n>>k;
	k++;
	for (i=0;i<n;i++)
	{
		cin>>arr[i];
	}

	//for (i=0;i<n;i++) cout<<arr[i]<<' ';
	sort(arr,arr+n);
	for (i=1;i<=n;i++)
	{
		pre[i]=pre[i-1]+arr[i-1];
	}

	for (i=0;i<n;i++) res+=arr[i]*i;
	//for (i=0;i<n;i++) cout<<arr[i]<<' ';
	for (i=0;i<n-1;i++)
	{
		if (i%k<k-1)
		{
			if (pre[n]-pre[i+1]<ll(0))
			{
				res-=pre[n]-pre[i+1];
			}
			else break;
		}
	}
	
	cout<<res;
}