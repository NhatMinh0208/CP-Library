/*
Pollard - Rho factorization algorithm.
Tested on library-checker.
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
#define FILE_IN "birds.inp"
#define FILE_OUT "birds.out"
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
#define ll128 __int128
#define pi 3.1415926535897
//------START-----------//
//	Random number generator. Works by defining a generator as below:
//	generator gen(lower_bound,upper_bound)
//	and then call gen(rng).
    std::random_device dev;
    std::mt19937 rng(dev());
 #define generator std::uniform_int_distribution<std::mt19937::result_type> 
//---------END---------//
typedef long long ll;

ll mul64(ll a, ll b, ll mo)
// Function to multiply 2 long longs using binary exponentation and then return the result mod mo.
// Input: a,b,mo
// Output: (a*b)%mo
{
    ll res = 0;
    while (b) {
        if (b & 1)
            res = (res + a) % mo;
        a = (a + a) % mo;
        b >>= 1;
    }
    return res;
}

ll mul(ll a, ll b, ll mo)
// Function to multiply 2 long longs using binary exponentation and then return the result mod mo.
// Input: a,b,mo
// Output: (a*b)%mo
{
	return (a*b)%mo;
}
ll bow (ll a, ll x, ll mo)
// Input: a,x,mo
// Output: (a^x)%mo
{
	if (x==0) return 1;
	ll res=bow(a,x/2,mo);
	res=mul(res,res,mo);
	if (x%2) res=mul(res,a,mo);
	return res;
}

ll bow64 (ll a, ll x, ll mo)
// Input: a,x,mo
// Output: (a^x)%mo
{
	if (x==0) return 1;
	ll res=bow64(a,x/2,mo);
	res=mul64(res,res,mo);
	if (x%2) res=mul64(res,a,mo);
	return res;
}
ll check (ll n, ll a, ll po, ll re)
// Checks if (a^n-1) is divisible by n using Miller-Rabin optimization
{
	ll og=bow64(a,re,n);
	if (og==1) return true;
	if (og==n-1) return true;
	for (ll i=1;i<=po;i++)
	{
		og=mul64(og,og,n);
		if (og==n-1) return true;
	}
	return false;
}
ll isPrime(ll n)
// Does a deterministic Miller-Rabin primality test for n<=2^63
{
	ll k=n-1,po=0,re=1;
	while (k%2==0)
	{
		k/=2;
		po++;
	}
	re=k;
	for (ll i : {2,3,5,7,11,13,17,19,23,29})
	if (n==i) return true;
	else
	if (!check(n,i,po,re)) return false;
	return true;
}
ll f(ll x, ll y, ll z, ll mo)
// The polynomial function (x^2+bx+c)%mo. Weirdly enough, the function (x^2+c)%mo gives TLE on test "4" for some reason.
{
	return ((mul64(x,x,mo)+mul64(x,y,mo))%mo+z)%mo;
}
ll gcd (ll x1, ll x2)
// GCD function for long long.
{
	if (x1*x2==0) return max(x1,x2);
	return gcd(min(x1,x2),max(x1,x2)%min(x1,x2));
}
ll pollard (ll n)
// Returns one factor of n (can be n), or -1 if the number is prime.
{
//	cout<<"pollard("<<n<<")\n";
	if (isPrime(n)) return -1;
	generator gen(2,1e9),gen2(2,1e9);
	ll start=gen(rng); ll seed=gen(rng),seed2=gen(rng); // Starting number and seeds for function
//	cout<<"start="<<start<<endl;
//	cout<<"seed="<<seed<<endl;
	ll x1=start,x2=start;
	while(true)
	{
		// Does Floyd's cycle-finding algorithm.
//		cout<<x1<<' '<<x2<<endl;
		x1=f(x1,seed,seed2,n);
		x2=f(x2,seed,seed2,n);
		x2=f(x2,seed,seed2,n);
//		cout<<x1<<' '<<x2<<endl;
		if (gcd(abs(x1-x2),n)>1) // found the cycle! Reuturns the factor.
		{
//	cout<<"end_pollard"<<endl;
			return gcd(abs(x1-x2),n);
		}
	}
}
vector<ll> factorize(ll n) //Factorizes n. Return a list of prime factors.
{
//	cout<<n<<endl;
	while(true)
	{
		ll g=pollard(n);
//		cout<<g<<' ';
		if (g==-1) return {n}; // Base case: n is a prime
		else if ((g<n)and(g>1)) // Make sure that we find an actual factor
		{
			vector<ll> res1=factorize(g),res2=factorize(n/g); // Once a factor is found, does recursive calls
			for (auto gg: res2) res1.push_back(gg);
			return res1;
		 } 
	}
}
//------END-----------//
ll n,m,k,c[501],arr[100001],dy[100001],t,t1,i,j,res;
vector<ll> gt[51];
long double v,vh,vv,g,angle,l,r,x,y,mid;
long double get_height(long double x)
{
	long double mp=vv/g*vh,apex=vv*(vv/g)/2;
	long double temp=abs(x-mp);
	temp/=vh;
	return apex-temp*temp*g/2;
}
int main()
{
	cin>>t1;
	for (t=0;t<t1;t++)
	{
		cin>>n;
		if (n==1) {
			cout<<0<<endl; 
			continue;
		}
		vector<ll> res=factorize(n);
		sort(res.begin(),res.end());
		cout<<res.size();
		for (ll g : res) cout<<' '<<g;
		cout<<endl;
	}
}

