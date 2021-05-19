#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
    Push-relabel max flow algorithm, version 1.0
    Solves the max flow problem in O(V^2*sqrt(E)) (with highest-label optimization).
    Works much slower than Dinic in practice (for some reason, maybe I'm just bad at implementation).
    Tested (for correctness) at https://judge.yosupo.jp/problem/bipartitematching
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
/*
namespace CPL_PRFlow
{
    struct mf_graph
    {
    struct edge
    {
        int v,rev;
        ll flow,cap;
        edge(int _v, int _rev, ll _flow, ll _cap) : v(_v),rev(_rev),flow(_flow),cap(_cap) {}
    };
    vector<vector<edge>> gt;
    vector<ll> ec;
    vector<edge*> cur;
    vector<vector<int>> hs;
    vector<int> H;
    mf_graph(int n=1000) : gt(n),ec(n),cur(n),hs(2*n),H(n) {}
    void add_edge(int s, int t, ll cap, ll rcap=0)
    {
        if (s-t)
        {
            gt[s].push_back({t,gt[t].size(),0,cap});
            gt[t].push_back({t,gt[s].size()-1,0,cap});
        }
    }
    void push(edge& e, ll f){
        edge &rev=gt[e.v][e.rev];
        if ((!ec[e.v])and(f)) hs[H[e.v]].push_back(e.v);
        e.flow+=f;
        e.cap-=f;
        ec[e.v]+=f;
        rev.flow-=f;
        rev.cap+=f;
        ec[rev.v]-=f;
    }
    ll calc_flow(int s, int t)
    {
        int n=gt.size(); H[s]=n; ec[t]=1;
        vector<int> co(2*n); co[0]=n-1;
        for (int i=0;i<n;i++) cur[i]=gt[i].data();
        for (edge& e : gt[s]) push(e,e.cap);

        
        for (int hi=0;;)
        {
            while(!hs[hi].size()) if (!hi--) return -ec[s];
            int u=hs[hi].back(); hs[hi].pop_back();
            while(ec[u]>0)
            {
                if (cur[u]==gt[u].data()+gt[u].size())
                {
                    H[u]=1e9+7;
                    for (edge& e : gt[u]) 
                    if ((e.cap)and(H[u]>H[e.v]))
                    {
                        H[u]=H[e.v]+1;
                        cur[u]=&e;
                    }
                
                co[H[u]]++;
                co[hi]--;
                if ((!co[hi])and(hi<n)) 
                {
                for (int i=0;i<n;i++)
                    if ((hi<H[i])and(hi<n))
                    {
                        co[H[i]]--;
                        H[i]=n+1;
                    }
                
                }
                }
                else if ((cur[u]->cap)and(H[u]==H[cur[u]->v]+1))
                push(*cur[u],min(ec[u],cur[u]->cap));
                else cur[u]++;
            }
        }
    }
    };
}

*/
namespace CPL_PRFlow
{
    struct mf_graph
    {
    struct edge
    {
        int v,rev;
        int forward;
        ll flow,cap;
        edge(int _v, int _rev, ll _flow, ll _cap, ll _f) : v(_v),rev(_rev),flow(_flow),cap(_cap),forward(_f) {}
    };
    vector<vector<edge>> gt;
    vector<int> h,po;
    vector<ll> excess;
    queue<int> q;
    vector<vector<int>> buc;
    int cur_height;
    int n,ss,tt;
    mf_graph(int _n=1000) : gt(_n),h(_n),excess(_n),n(_n),po(_n),buc(2*_n+1) {}
    void add_edge(int s, int t, ll cap, ll rcap=0)
    {
        if (s-t)
        {
            gt[s].push_back({t,gt[t].size(),0,cap,1});
            gt[t].push_back({s,gt[s].size()-1,cap,0,0});
        }
    }
    void push(int u, int x, ll f) // Push flow along edge gt[u][x].
    {
        if (!f) return;
        gt[u][x].flow+=f;
        gt[u][x].cap-=f;
        excess[u]-=f;
 
        int v=gt[u][x].v,y=gt[u][x].rev;
 
        if ((!excess[v])and(v-ss)and(v-tt))
        {
            buc[h[v]].push_back(v);
            if (cur_height<h[v]) cur_height=h[v];
        }
        gt[v][y].flow-=f;
        gt[v][y].cap+=f;
        excess[v]+=f;
        //cout<<"end push "<<u<<' '<<x<<' '<<f<<endl;
 
    }
    void rise(int u) // Increases u's height.
    {
        //cout<<"rise "<<u<<endl;
        int minn=1e9+7;
        for (auto g : gt[u]) if (g.cap) minn=min(minn,h[g.v]);
        if (minn<1e9)
        h[u]=minn+1;
        //cout<<"end rise "<<u<<endl;
    }
    void discharge(int u) // Get rid of all excess in u.
    {
        
        //cout<<"discharge "<<u<<' '<<h[u]<<endl;
        while(excess[u])
        {
            if (po[u]<gt[u].size())
            {
//                cout<<u<<' '<<gt[u][po[u]].v<<' '<<gt[u][po[u]].flow<<' '<<gt[u][po[u]].cap<<' '<<excess[u]<<endl;
                if ((h[u]==h[gt[u][po[u]].v]+1)and(gt[u][po[u]].cap)) 
                {
                    push(u,po[u],min(excess[u],gt[u][po[u]].cap));
                }
                po[u]++;
            }
            else
            {
                rise(u);
                po[u]=0;
            }
        }
        //cout<<"end discharge "<<u<<' '<<h[u]<<endl;
    }
    ll calc_flow(int s, int t)
    {
        ss=s;
        tt=t;
        h.assign(n,0);
        po.assign(n,0);
        h[s]=n;
        for (int i=0;i<n;i++)
        for (auto& g : gt[i]) if (g.forward)
        {
            g.flow=0;
            g.cap=g.cap+gt[g.v][g.rev].cap;
            gt[g.v][g.rev].cap=0;
            gt[g.v][g.rev].flow=g.cap;
        }
        excess.assign(n,0);
        excess[s]=1e18+7;
        cur_height=n;
        for (int i=0;i<gt[s].size();i++)
        {
            push(s,i,gt[s][i].cap);
        }
        
        while(cur_height>=0)
        {
            if (!buc[cur_height].size()) cur_height--;
            else
            {
                auto u=buc[cur_height].back();
                buc[cur_height].pop_back();
                discharge(u);
            }
        }
        
        ll res=0;
        for (auto g : gt[t]) res+=g.cap;
        return res;
    }
    };
}
using namespace CPL_PRFlow;

// Example problem follows.
// Source: https://judge.yosupo.jp/problem/bipartitematching
int n,m,i,j,k,t,t1,u,v,a,b;
int main()
{
    fio;
    cin>>n>>m>>k;
    CPL_PRFlow::mf_graph gr(m+n+2);
    for (i=1;i<=n;i++) gr.add_edge(0,i,1);
    for (i=1;i<=m;i++) gr.add_edge(n+i,n+m+1,1);
    for (i=0;i<k;i++)
    {
        cin>>a>>b;
        gr.add_edge(a+1,b+n+1,1);
    }
//    for (i=0;i<=m+n+1;i++) for (auto g : gr.gt[i]) cout<<i<<' '<<g.v<<' '<<g.forward<<' '<<g.cap<<' '<<g.flow<<endl;
    
    cout<<gr.calc_flow(0,m+n+1)<<endl;
    for (i=1;i<=n;i++) for (auto g : gr.gt[i]) if ((g.forward)and(g.flow))
    cout<<i-1<<' '<<g.v-n-1<<endl;
    
}