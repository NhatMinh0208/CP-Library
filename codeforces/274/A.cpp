#include <bits/stdc++.h>
#include <stdio.h>
#define int long long int
#define us unsigned long long int
#define null 0
using namespace std;
void IOS()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
int32_t main() {
 
IOS();
 
int n,k;
cin>>n>>k;
int a[n];
for(int i=0;i<n;i++)
    cin>>a[i];
sort(a,a+n);
int no=0;
for(int i=0;i<n;i++)
{
    if(a[i]==0)
        continue;
    else
        no++;
    int low=i+1,high=n-1;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(a[mid]==a[i]*k)
        {
            a[mid]=0;
            break;
        }
        if(a[mid]<k*a[i])
            low=mid+1;
        else
            high=mid-1;
    }
}
cout<<no;
}