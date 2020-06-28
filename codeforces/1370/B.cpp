
// Problem : A. Maximum GCD
// Contest : Codeforces - Codeforces Round #651 (Div. 2)
// URL : https://codeforces.com/contest/1370/problem/A
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

/*
 A Submission by $%U%$
 at time: $%Y%$-$%M%$-$%D%$ $%h%$:$%m%$:$%s%$
*/
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define rep(i,n) for(int64_t i=0;i < (int64_t)(n);i++)
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FILE_IN "cseq.inp"
#define FILE_OUT "cseq.out"
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
#define ordered_set tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update>
#define endl "\n"
#define bi BigInt
typedef long long ll;
//---------END-------//
int n,m,k,c[501],pos[100001],t,t1,i,j;
vector<int> buc0,buc1;
int main()
{
//  ofile;
    fio;
    cin>>t;
    for (t1=0;t1<t;t1++)
    {
    	buc0.clear(); buc1.clear();
    	cin>>n;
    	for (i=0;i<2*n;i++)
    	{
    		cin>>k;
    		if (k%2==0) buc0.push_back(i+1);
    		else buc1.push_back(i+1);
    	}
    	if (buc0.size()%2==0)
    	{
    	if (buc0.size())
    	{
    		buc0.pop_back();
    		buc0.pop_back();
    	}
    	else
    	{
    		buc1.pop_back();
    		buc1.pop_back();
    	}
    	}
    	else
    	{
    		
    		buc0.pop_back();
    		buc1.pop_back();
    	}
    	for (i=0;i<buc0.size();i+=2)
    	cout<<buc0[i]<<' '<<buc0[i+1]<<endl;
    	for (i=0;i<buc1.size();i+=2)
    	cout<<buc1[i]<<' '<<buc1[i+1]<<endl;
    }
}
