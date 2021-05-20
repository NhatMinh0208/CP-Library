#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
    Simulated annealing example, version 1.0.
    Solves the TSP problem.
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
int vec1[5001],vec2[5001];
int n,m,i,j,k,t,t1,u,v,a,b;
ld x[5001],y[5001];
ld getDist(int v[], int n)
{
    ld res=0;
    for (int i=0;i<n;i++)
    {
        res+=sqrt((x[v[i]]-x[v[(i+1)%n]])*(x[v[i]]-x[v[(i+1)%n]])+
        (y[v[i]]-y[v[(i+1)%n]])*(y[v[i]]-y[v[(i+1)%n]])
        );
    }
    return res;
}
ld prob(ld e1, ld e2, ld t)
{
    if (e2<e1) return 1;
    return exp(-(e2-e1)/t);
}
// Temps for distance 5k-10k
ld temp (int it)
{
    if (it<=2000000) return 80+(ld)20/(2000000)*(2000000-it);
    if (it<=5000000) return 60+(ld)20/(3000000)*(5000000-it);
    if (it<=9000000) return 40+(ld)20/(4000000)*(9000000-it);
    if (it<=14000000) return 20+(ld)20/(5000000)*(14000000-it);
    if (it<=20000000) return 0+(ld)20/(6000000)*(20000000-it);
}
void solve()
{
    ld e1,e2,p,act,t;
    for (i=0;i<n;i++) vec1[i]=i;
    for (int iter=1;iter<=20000000;iter++)
    {
        memcpy(vec2,vec1,4*n);
        a=rand()%n;
        b=rand()%min(n-1,(n-1));
        b+=a+1;
        b%=n;
        swap(vec2[a],vec2[b]);
        e1=getDist(vec1,n);
        e2=getDist(vec2,n);
        t=temp(iter);
        p=prob(e1,e2,t);
        act=ld(rand())/RAND_MAX;
        if ((iter==1)or(iter%10000==0))
        {
        cout<<"Iteration #"<<iter<<endl;
        cout<<"Current energy = "<<fixed<<setprecision(5)<<e1<<endl;
        cout<<"New energy = "<<fixed<<setprecision(5)<<e2<<endl;
        cout<<"Temp = "<<t<<endl;
        cout<<"Prob = "<<p<<endl;
        if (act<=p) cout<<"Result = ACCEPT"<<endl;
        else cout<<"Result = DECLINE"<<endl;
        }
        if (act<=p) memcpy(vec1,vec2,4*n);
    }
}
int main()
{
    srand(time(NULL));
    freopen("test.txt","r",stdin);
    cin>>n;
    for (i=1;i<=n;i++) cin>>i>>x[i-1]>>y[i-1];
    solve();
}
