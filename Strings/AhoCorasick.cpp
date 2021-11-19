#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
	Normie's Aho-Corasick, version 2.0.
	This data structure receives a set of strings and builds 2 trees: 
	+) A trie of the strings
	+) A suffix link tree of the strings
	The implementation is kept as barebones as possible to promote flexibility.
	Tested with https://codeforces.com/problemset/problem/1202/E
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

namespace CP_Library {
const int ALPHA_SZ=26;
const int SHIFT_CONST=-97;
struct Node {
	unordered_map<int,int> ch_trie;
	vector<int> ch2_trie;
	int p_trie;
	vector<int> ch_suff;
	int p_suff=0;
	vector<int> leaf;

	int ch;

	int nxt[ALPHA_SZ];

	Node(int par=0, int _ch=0) {
		p_trie=par;
		ch=_ch;
	}
};

struct Aho_Corasick {
	vector<Node*> trie;
	vector<int> str_store;
	Aho_Corasick() {
		trie.push_back(new Node);
		trie.push_back(new Node);
	}
	void add_str(string s) { // Adds a string to the Aho_Corasick trie
		int u=1;
		for (auto g : s) {
			if (trie[u]->ch_trie[g+SHIFT_CONST]==0) {
				trie.push_back(new Node(u, g+SHIFT_CONST));
				trie[u]->ch_trie[g+SHIFT_CONST]=trie.size()-1;
			}
			u=trie[u]->ch_trie[g+SHIFT_CONST];
		}
		trie[u]->leaf.push_back(str_store.size());
		str_store.push_back(u);
	}
	void build_suff() { // Finalizes the trie and builds the suffix tree
		vector<int> dq;
		dq.push_back(1);
		int u,v;
		for (int j=0;j<dq.size();j++) {
			u=dq[j];
			// cout<<"suflink "<<u<<endl;
			if (u==1) {
				trie[u]->p_suff=u;
				for (int i=0;i<ALPHA_SZ;i++) {
					if (trie[u]->ch_trie[i]) trie[u]->nxt[i]=trie[u]->ch_trie[i];
					else trie[u]->nxt[i]=1;
				}
			}
			else if (trie[u]->p_trie==1) {
				trie[u]->p_suff=1;
				trie[1]->ch_suff.push_back(u);

				
				for (int i=0;i<ALPHA_SZ;i++) {
					if (trie[u]->ch_trie[i]) trie[u]->nxt[i]=trie[u]->ch_trie[i];
					else trie[u]->nxt[i]=trie[1]->nxt[i];
				}
			}
			else {
				v=trie[trie[trie[u]->p_trie]->p_suff]->nxt[trie[u]->ch];
				trie[u]->p_suff=v;
				trie[v]->ch_suff.push_back(u);

				
				for (int i=0;i<ALPHA_SZ;i++) {
					if (trie[u]->ch_trie[i]) trie[u]->nxt[i]=trie[u]->ch_trie[i];
					else trie[u]->nxt[i]=trie[trie[u]->p_suff]->nxt[i];
				}
			}
			// cout<<"result: "<<u<<' '<<trie[u]->p_suff<<endl;
			// for (int i=97;i<123;i++) {
			// 	cout<<"trans "<<char(i)<<' '<<trie[u]->nxt[i]<<endl;
			// }
			for (auto g : trie[u]->ch_trie) {
				// cout<<char(g.fi)<<' '<<g.se<<endl;
				if (g.se) dq.push_back(g.se);
			}
			trie[u]->ch_trie.clear();
			// cout<<endl;
		}
	}
	void debug() {
		for (int i=1;i<trie.size();i++) {
			cout<<"Debugging node "<<i<<endl;
			cout<<trie[i]->ch<<' '<<trie[i]->p_trie<<' '<<trie[i]->p_suff<<endl;
			
			for (int j=0;j<26;j++) {
				cout<<char(j-SHIFT_CONST)<<' '<<trie[i]->nxt[j]<<' ';
			}
			cout<<endl;
		}
	}
};

}

// Sample usage follows.
// Source: https://codeforces.com/contest/1202/submission/132412398


using namespace CP_Library;

Aho_Corasick ah1,ah2;

ll r1[200011];
ll r2[200011];

ll dep[200011];
string s[200011];
string tr;
ll n,m,i,j,k,t,t1,u,v,a,b;
void dfs1(int x) {
	dep[x]=dep[ah1.trie[x]->p_suff]+ah1.trie[x]->leaf.size();
	for (auto g : ah1.trie[x]->ch_suff) dfs1(g);
	
	// cout<<"dfs1 "<<x<<' '<<dep[x]<<endl;
}
void dfs2(int x) {
	dep[x]=dep[ah2.trie[x]->p_suff]+ah2.trie[x]->leaf.size();
	for (auto g : ah2.trie[x]->ch_suff) dfs2(g);
}
int main()
{
	fio;
	cin>>tr;
	m=tr.size();
	cin>>n;
	for (i=0;i<n;i++) {
		cin>>s[i];
	}



	for (i=0;i<n;i++) {
		ah1.add_str(s[i]);
	}
	ah1.build_suff();

	dfs1(1);
	
	u=1;
	// ah1.debug();
	for (i=0;i<m-1;i++) {
		// cout<<u<<endl;
		v=int(tr[i]+SHIFT_CONST);
		// cout<<v<<endl;
		u=ah1.trie[u]->nxt[v];
		r1[i]=dep[u];
		// cout<<u<<' '<<dep[u]<<endl;
	}

	for (i=0;i<n;i++) {
		reverse(s[i].begin(),s[i].end());
	}

	reverse(tr.begin(),tr.end());
	
	for (i=0;i<n;i++) {
		ah2.add_str(s[i]);
	}
	ah2.build_suff();
	
	dfs2(1);

	u=1;
	for (i=0;i<m-1;i++) {
		// cout<<u<<endl;
		v=int(tr[i]+SHIFT_CONST);
		// cout<<v<<endl;
		u=ah2.trie[u]->nxt[v];
		r2[i]=dep[u];
		// cout<<u<<' '<<dep[u]<<endl;
	}
	ll res=0;
	for (i=0;i<m-1;i++) {
		res+=r1[i]*r2[m-2-i];
		// cout<<r1[i]<<' '<<r2[i]<<endl;
	}
	// if (res==1815024) cout<<n<<' '<<m<<' '<<ah2.trie.size()<<endl;
	cout<<res;
}
