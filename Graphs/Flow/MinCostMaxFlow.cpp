/*
khoi orz, go check out his algo
-normie-
Tested with 102801B.
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
#define ll long long
#define pi 3.1415926535897
//------START-----------//
// Normie's implementation of Dinic max flow.
// NOTE: if you need to work with numbers > 1e9, change int_t from int to ll and MAXINT to 1e18+7
#define MAXN 1101 // maximum number of vertices you will be using
#define int_t int
#define MAXINT 1000000007
struct edge
// Structure to represent a directed graph edge.
// u  : outgoing vertex
// v  : incoming vertex
// cap: remaining capacity of vertex
// rev: This edge's reverse edge id.
{
	int_t u,v,cap,rev,cost;
	edge(int_t uu, int_t vv, int_t revv, int_t capp=0, int_t costt=0) // constructor
	{
		u=uu;
		v=vv;
		rev=revv;
		cap=capp;	
		cost=costt;
	} 
};
struct mcmf_graph
// Structure to reppresent a directed flow graph.
{
	private:
	
	vector<edge> lis;                          // List of edges in graph.
	vector<edge> lis_t;                        // A copy of lis, for use with the algorithms.
	vector<int_t> adj[MAXN];                   // Adjacency list for each vertex. Edges are identified by their id as stored in [lis]
	
	
	int_t n;                                   // Actual number of vertices.
	int_t s,t;                                 // Source and sink of graph.
	int_t res;                                 // The current result, for use with the algorithms.
	int_t resc;
	int_t nxt[MAXN],dis[MAXN],inq[MAXN],cnt[MAXN];
	
	vector<int_t> spfa()
	{
	deque<int_t> to_relax;
	    to_relax.push_back(s);
	    for (int_t i=0;i<n;i++)
	    {
	        nxt[i]=-1;
	        dis[i]=MAXINT;
	        inq[i]=0;
	        cnt[i]=0;
	    }
	    to_relax.push_back(s);
	    dis[s]=0;
	    inq[s]=1;
	    cnt[s]++;
	    while(to_relax.size())
	    {
	        int_t cur=to_relax.front();
	//        cout<<"relaxing "<<cur<<' '<<dis[cur]<<endl;
	        for (int_t g : adj[cur])
	        {
	            if ((dis[cur]+lis_t[g].cost<dis[lis_t[g].v])and(lis_t[g].cap))
	            {
	                dis[lis_t[g].v]=dis[cur]+lis_t[g].cost;
	                nxt[lis_t[g].v]=g;
	                if (!inq[lis_t[g].v])
	                {
	                    inq[lis_t[g].v]=1;
	                    cnt[lis_t[g].v]++;
	                    if (cnt[lis_t[g].v]>n) break;
	                
	                    to_relax.push_back(lis_t[g].v);
	                    
	                }
	            }
	        }
	        to_relax.pop_front();
	        inq[cur]=0;
	    }
	    int_t curn=t;
	    vector<int_t> ress;
	    while(curn!=s)
	    {
	        ress.push_back(nxt[curn]);
	        curn=lis_t[nxt[curn]].u;
	    }
	    return ress;
	    
	}
	public:
	
	void debug() // just some debugging
	{
	    cout<<n<<' '<<s<<' '<<t<<endl;
	    for (int_t i=0;i<lis.size();i++)
	    {
	    	cout<<i<<' '<<lis[i].u<<' '<<lis[i].v<<' '<<lis[i].cap<<' '<<lis[i].rev<<' '<<lis[i].cost<<endl;
		}
		for (int_t i=0;i<n;i++)
		{
			cout<<i<<' ';
			for (int_t g: adj[i]) cout<<g<<' ';
			cout<<endl;
		}
	}
	
	mcmf_graph(int_t nn=1)                    // Constructor
	{
		n=nn;
	}
	
	void reset()
	{
		lis.clear();
		lis_t.clear();
		for (int_t i=0;i<n;i++) adj[i].clear();
	}
	void add_edge(int_t u, int_t v, int_t cap, int_t cost) // Adds an edge to the graph, as well as its residual edge.
	{
		int_t id=lis.size()-1;
		lis.push_back(edge(u,v,id+2,cap,cost));     // Adds edge to lis
		adj[u].push_back(id+1);                // Adds newly created edge's id to u's adjacency list
		lis.push_back(edge(v,u,id+1,0,-cost));         // Same with residual edge
		adj[v].push_back(id+2);
	}
	
	void setn(int_t nn)
	{
		n=nn;
	}
	int_t calc_flow(int_t ss, int_t tt, int_t kk)        // Calculate the maximum flow
	{
		// Some initialization stuff.
		s=ss; t=tt;
		res=0;
		resc=0;
		int_t cycle=0;
		lis_t=lis;
		while (res<kk)                           // Loops the algorithm until there's no more blocking flows.
		{
//			cout<<"cycle "<<cycle<<endl;
		    cycle++;
		    vector<int_t> ind=spfa();
		    int_t addable=kk-res;
		    for (int_t g : ind)
		    {
		        addable=min(addable,lis_t[g].cap);
		    }
		    res+=addable;
//		    cout<<addable<<endl;
		    for (int_t g : ind)
		    {
		        resc+=lis_t[g].cost*addable;
		        lis_t[g].cap-=addable;
		        lis_t[lis_t[g].rev].cap+=addable;
		    }
		}
		return resc;
	}
	
};
//------END-----------//
int n,m,k,aa[501],bb[501],cc[501],t,t1,i,j,res;
vector<ll> gt[51];
mcmf_graph gr(1101);
ll f(ll u, ll v, ll k)
{
    return ((u+v)*(u^v))%k;
}
int main()
{
	cin>>t;
	for (t1=0;t1<t;t1++)
	{
		gr.reset();
	    cin>>n>>m>>k;
		gr.setn(2+n+n+n+n+1);
	    for (i=0;i<n;i++) cin>>aa[i];
	    for (i=0;i<n;i++) cin>>bb[i];
	    for (i=0;i<n;i++) cin>>cc[i];
	    gr.add_edge(0,1,m,0);
	    for (i=0;i<n;i++) gr.add_edge(1,2+i,1,0);
	    for (i=0;i<n;i++) for (j=0;j<n;j++) gr.add_edge(2+i,2+n+j,1,-f(bb[i],aa[j],k));
	    for (i=0;i<n;i++) gr.add_edge(2+n+i,2+n+n+i,1,0);
	    for (i=0;i<n;i++) for (j=0;j<n;j++) gr.add_edge(2+n+n+i,2+n+n+n+j,1,-f(aa[i],cc[j],k));
	    for (i=0;i<n;i++) gr.add_edge(2+n+n+n+i,2+n+n+n+n,1,0);
//	    gr.debug();
	    cout<<-gr.calc_flow(0,2+n+n+n+n,m)<<endl;
	}
}
