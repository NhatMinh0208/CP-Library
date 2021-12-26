#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
	Normie's Template v2.5
	Changes:
    Added warning against using pragmas on USACO.
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
namespace CPL_MCF {

	const int MAXN = 1101;
	const int INF = 1e9;

	template<class T>
	struct edge {
		T u, v, cap, cost, rev;
		edge(T a, T b, T c, T d, T e) {
			u=a;
			v=b;
			cap=c;
			cost=d;
			rev=e;
		}
	};

	template<class T>
	struct mcf {
		vector<edge<T>> lis;
		vector<edge<T>> lis_t;
		vector<T> adj[MAXN];
		
		T n, s, t, lim, m;
		pair<T,T> res;
		T dis[MAXN];
		T lead[MAXN];

		void reset(T nn) {
			for (int i=0;i<nn;i++) adj[i].clear();
			n=nn;
			res={0,0};
			lis.clear();
			lis_t.clear();
		}

		void add_edge(T u, T v, T cap, T cost) {
			int i = lis.size();
			adj[u].push_back(i);
			adj[v].push_back(i+1);
			lis.push_back(edge<T>(u,v,cap,cost,i+1));
			lis.push_back(edge<T>(v,u,0,-cost,i));
		}

		void reduce() {
			for (int i=0;i<m;i++) if (lis_t[i].rev>i) {
				lis_t[i].cap+=dis[lis_t[i].u]-dis[lis_t[i].v];
				lis_t[lis_t[i].rev].cap=0;
			}
		}

		void disBF() {
			T inq[n],cnt[n];
			deque<T> q;
			for (int i=0;i<n;i++) {
				cnt[i]=0;
				inq[i]=0;
				dis[i]=INF;
			}
			q.push_back(s);
			dis[s]=0;
			inq[s]=1;
			cnt[s]++;
			while(q.size())
			{
				T cur=q.front();
		//        cout<<"relaxing "<<cur<<' '<<dis[cur]<<endl;
				for (T g : adj[cur])
				{
					if ((dis[cur]+lis_t[g].cost<dis[lis_t[g].v])and(lis_t[g].cap))
					{
						dis[lis_t[g].v]=dis[cur]+lis_t[g].cost;
						if (!inq[lis_t[g].v])
						{
							inq[lis_t[g].v]=1;
							cnt[lis_t[g].v]++;
							if (cnt[lis_t[g].v]>n) break;
							q.push_back(lis_t[g].v);
						}
					}
				}
				q.pop_front();
				inq[cur]=0;
			}
		}

		void disDIJ() {
			priority_queue<pair<T,T>,vector<pair<T,T>>,greater<pair<T,T>>> pq;
			pq.clear();
			for (int i=0;i<n;i++) {
				dis[i]=INF;
			}
			dis[s]=0;
			pq.push({0,s});
			while(pq.size()) {
				auto pp = pq.top();
				pq.pop();
				if (dis[pp.se]<pp.fi) continue;
				for (auto g : adj[pp.se]) {
					edge<T> ed = lis_t[g];
					if (ed.cap && dis[ed.v]>pp.fi+ed.cost) {
						dis[ed.v] = pp.fi+ed.cost;
						lead[ed.v] = g;
						pq.push({dis[ed.v],ed.v});
					}
				}
			}
		}

		void augment() {
			vector<T> path;
			T uu = t;
			while (uu != s) {
				path.push_back(lead[uu]);
				uu = lis_t[lead[uu]].u;
			}
			T added;
			added = lim-res.fi;
			for (auto g : path) {
				added=min(added,lis_t[g].cap);
			}
			for (auto g : path) {
				lis_t[g].cap-=added;
				lis_t[lis_t[g].rev].cap+=added;
			}
			res.fi+=added;
		}

		void get_result() {
			for (int i=0;i<m;i++) if (lis_t[i].rev>i) {
				res.se += lis_t[lis_t[i].rev].cap * lis_t[i].cost;
			}
		}

		pair<T,T> calc_flow(T ss, T tt, T limm) {
			s=ss;
			t=tt;
			lim=limm;
			m=lis.size();
			lis_t=lis;
			res={0,0};

			disBF();
			reduce();

			while(true) {
				disDIJ();
				if (dis[t]==INF) break;
				reduce();
				augment();
				if (res.fi == lim) break;
			}
			get_result();
			return res;
		}
	};

}



vector<int> vec;
int n,m,i,j,k,t,t1,u,v,a,b;
int main()
{
	fio;
}
