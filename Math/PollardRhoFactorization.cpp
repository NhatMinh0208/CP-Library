#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
	Normie's Template v2.6
	Changes:
	Added range
*/
// Standard library in one include.
#include <bits/stdc++.h>
using namespace std;
 
// ordered_set library.
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set(el) tree<el,null_type,less<el>,rb_tree_tag,tree_order_statistics_node_update>
 
// AtCoder library. (Comment out these two lines if you're not submitting in AtCoder.) (Or if you want to use it in other judges, run expander.py first.)
//#include <atcoder/all>
//using namespace atcoder;

//Pragmas (Comment out these three lines if you're submitting in szkopul or USACO.)
// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast,unroll-loops,tree-vectorize")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
 
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
// template<typename T>
// __attribute__((always_inline)) void chkmin(T& a, const T& b) {
//     a=(a<b)?a:b;
// }

// template<typename T>
// __attribute__((always_inline)) void chkmax(T& a, const T& b) {
//     a=(a>b)?a:b;
// }
 
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

//Custom begin/end shorthand.
#define rnge(rnge) rnge.begin(),rnge.end()
 
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

//	Random number generator. Works by defining a generator as below:
//	generator gen(lower_bound,upper_bound)
//	and then call gen(rng).
    std::random_device dev;
    std::mt19937 rng(dev());
 #define generator std::uniform_int_distribution<std::mt19937::result_type> 

// Function to multiply 2 long longs using binary exponentation and then return the result mod mo.
// Input: a,b,mo
// Output: (a*b)%mo
ll mul64(ll a, ll b, ll mo)
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

// Input: a,x,mo
// Output: (a^x)%mo
ll bow64 (ll a, ll x, ll mo)
{
	if (x==0) return 1;
	ll res=bow64(a,x/2,mo);
	res=mul64(res,res,mo);
	if (x%2) res=mul64(res,a,mo);
	return res;
}

// Checks if (a^n-1) is divisible by n using Miller-Rabin optimization
ll check (ll n, ll a, ll po, ll re)
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

// Does a deterministic Miller-Rabin primality test for n<=2^63
ll isPrime(ll n)
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

// The polynomial function (x^2+bx+c)%mo.
ll f(ll x, ll y, ll z, ll mo)
{
	return ((mul64(x,x,mo)+mul64(x,y,mo))%mo+z)%mo;
}

// GCD function for long long.
ll gcd (ll x1, ll x2)
{
	if (x1*x2==0) return max(x1,x2);
	return gcd(min(x1,x2),max(x1,x2)%min(x1,x2));
}

// Returns one factor of n (can be n), or -1 if the number is prime.
// Idea: use a function x -> (x^2+bx+c)%mo. We should get into a cycle after ~O(sqrt(factor_of_n)) steps.
ll pollard (ll n)
{
	if (isPrime(n)) return -1;
	generator gen(2,1e9),gen2(2,1e9);
	ll start=gen(rng); ll seed=gen(rng),seed2=gen(rng); // Starting number and seeds for function
	ll x1=start,x2=start;
	while(true)
	{
		// Does Floyd's cycle-finding algorithm.
		// The algorithm terminates when x1%fac == x2%fac for some factor of n.
		x1=f(x1,seed,seed2,n);
		x2=f(x2,seed,seed2,n);
		x2=f(x2,seed,seed2,n);
		if (gcd(abs(x1-x2),n)>1) // found the cycle - return the factor
		{
			return gcd(abs(x1-x2),n);
		}
	}
}
// Factorizes n. Return a list of prime factors.
vector<ll> factorize(ll n) 
{
	if (n<=1) return {};
	while(true)
	{
		ll g=pollard(n);
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

