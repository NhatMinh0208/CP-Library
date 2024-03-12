#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
	Kuhn's bipartite matching algorithm, version 1.1.
    Given a (n,m) bipartite unweighted graph (n<=m), the algorithm finds the maximum matching in O(n*m).
    Tested with library-checker (https://judge.yosupo.jp/problem/bipartitematching)
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

namespace CPL_Kuhn {
    vector<int> gt[200001];
    int used[200001];
    vector<int> toclear;
    int matched[200001];
    int n,m,i,j,k,t,t1,u,v,a,b;
    vector<int> res1,res2;
    int augment(int u, int p)
    {
        // cout<<"aug "<<u<<' '<<p<<endl;
        if (used[u]) return 0;
        used[u]=1;
        toclear.push_back(u);
        for (int v : gt[u])
        {
            // cout<<v<<endl;
            if ((v!=p)&&((matched[v]==-1)or(augment(matched[v], v))))
            {
                matched[v]=u;
                return 1;
            }
        }
        return 0;
    }
    void init(int _n, int _m) {
        a=_n,b=_m;
        for (i=a;i<a+b;i++) matched[i]=-1;
    }
    void add_edge(int x, int y) {
        gt[x].push_back(a+y);
    }
    int solve() {
        int res=0;
        for (i=0;i<a;i++) {
            random_shuffle(gt[i].begin(), gt[i].end());
            for (auto g : toclear) used[g] = 0;
            toclear.clear();
            augment(i,-1);
        }
        for (i=a;i<a+b;i++) if (matched[i]!=-1) res++;
        return res;
    }
    vector<pii(int)> get_matches() {
        vector<pii(int)> res;
        for (i=a;i<a+b;i++) if (matched[i]!=-1) res.push_back({matched[i],i-a});
        return res;
    }
};
int n,m,i,u,v;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

    cin>>u>>v>>m;
    CPL_Kuhn::init(u,v);
	for (i=0;i<m;i++)
	{
        cin>>u>>v;
        CPL_Kuhn::add_edge(u,v);
	}
    
	cout<<CPL_Kuhn::solve()<<endl;
	for (auto g : CPL_Kuhn::get_matches())
	{
        cout<<g.fi<<' '<<g.se<<endl;
	}
}
