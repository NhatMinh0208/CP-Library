#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
	Normie's Extended Euclidean algorithm implementation.
    Given a,b, calculate x,y,z such that:
    *) z=gcd(a,b)
    *) ax+by=z
    Also includes CRT implementation.
*/
// Standard library in one include.
#include <bits/stdc++.h>
using namespace std;
 
// ordered_set library.
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set(el) tree<el,null_type,less<el>,rb_tree_tag,tree_order_statistics_node_update>
 
// AtCoder library. (Comment out these two lines if you're not submitting in AtCoder.) (Or if you want to use it in other judges, run expander.py first.)
//#include <atcoder/all>
//using namespace atcoder;
 
//Pragmas (Comment out these three lines if you're submitting in szkopul.)
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,unroll-loops,tree-vectorize")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
 
//File I/O.
#define FILE_IN "cseq.inp"
#define FILE_OUT "cseq.out"
#define ofile freopen(FILE_IN,"r",stdin);freopen(FILE_OUT,"w",stdout)
 
//Fast I/O.
#define fio ios::sync_with_stdio(0);cin.tie(0)
#define nfio cin.tie(0)
#define endl "\n"
 
//Order checking.
#define ord(a,b,c) ((a>=b)and(b>=c))
 
//min/max redefines, so i dont have to resolve annoying compile errors.
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

// Fast min/max assigns to use with AVX.
// Requires g++ 9.2.0.
template<typename T>
__attribute__((always_inline)) void chkmin(T& a, const T& b) {
    a=(a<b)?a:b;
}

template<typename T>
__attribute__((always_inline)) void chkmax(T& a, const T& b) {
    a=(a>b)?a:b;
}
 
//Constants.
#define MOD (ll(998244353))
#define MAX 300001
#define mag 320
const long double PI=3.14159265358979;
 
//Pairs and 3-pairs.
#define p1 first
#define p2 second.first
#define p3 second.second
#define fi first
#define se second
#define pii(element_type) pair<element_type,element_type>
#define piii(element_type) pair<element_type,pii(element_type)>
 
//Quick power of 2.
#define pow2(x) (ll(1)<<x)
 
//Short for-loops.
#define ff(i,__,___) for(int i=__;i<=___;i++)
#define rr(i,__,___) for(int i=__;i>=___;i--)
 
//Typedefs.
#define bi BigInt
typedef long long ll;
typedef long double ld;
typedef short sh;

// Binpow and stuff
ll BOW(ll a, ll x, ll p)
{
	if (!x) return 1;
	ll res=BOW(a,x/2,p);
	res*=res;
	res%=p;
	if (x%2) res*=a;
	return res%p;
}
ll INV(ll a, ll p)
{
	return BOW(a,p-2,p);
}
//---------END-------//
#endif
vector<int> vec;
int n,m,i,j,k,t,t1,u,v,a,b;
namespace CPL_Euclid
{
    vector<ll> extendedEuclid(ll a, ll b)
    {
        ll arr[3][3],x;
        arr[0][1]=1;
        arr[0][2]=0;
        arr[1][1]=0;
        arr[1][2]=1;
        if (a>b)
        {
            arr[0][0]=a;
            arr[1][0]=b;
        }
        else
        {
            arr[0][0]=b;
            arr[1][0]=a;
        }
        while(true)
        {
            x=arr[0][0]/arr[1][0];
            arr[2][0]=arr[0][0]-arr[1][0]*x;
            arr[2][1]=arr[0][1]-arr[1][1]*x;
            arr[2][2]=arr[0][2]-arr[1][2]*x;
            if (arr[2][0]==0)
            {
                if (a>b) return {arr[1][1],arr[1][2],arr[1][0]};
                if (a<=b) return {arr[1][2],arr[1][1],arr[1][0]};
            }
            else
            {
                memcpy(arr[0],arr[1],sizeof(arr[0]));
                memcpy(arr[1],arr[2],sizeof(arr[0]));
            }
        }
    }
    ll chineseRemainder(ll a, ll ra, ll b, ll rb)
    {
        vector<ll> u=extendedEuclid(a,b);
        if (u[2]>1) return -1;
        else return ((ra*b*u[1]+rb*a*u[0])%(a*b)+(a*b))%(a*b);
    }
    
}
int main()
{
    cout<<CPL_Euclid::chineseRemainder(3,0,2,1)<<endl;
    cout<<CPL_Euclid::chineseRemainder(3,1,2,1)<<endl;
    cout<<CPL_Euclid::chineseRemainder(3,2,2,1)<<endl;
    cout<<CPL_Euclid::chineseRemainder(3,0,2,0)<<endl;
    cout<<CPL_Euclid::chineseRemainder(3,1,2,0)<<endl;
    cout<<CPL_Euclid::chineseRemainder(3,2,2,0)<<endl;
}