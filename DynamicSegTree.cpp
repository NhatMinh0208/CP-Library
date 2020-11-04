/*
    New, shiny, hand-crafted dynamic segtree template.
    Perfect for use in any online contest.
    Tested with Codeforces Edu and library-checker. 
*/
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define fef(i,a,b) for(ll i=a;i<=b;i++)
#define rer(i,a,b) for(ll i=b;i>=a;i--)
#define wew while(true)
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
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define For(i,__,___) for(int i=__;i<=___;i++)
#define Rep(i,__,___) for(int i=__;i>=___;i--)
#define ordered_set tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update>
#define endl "\n"
#define bi BigInt
typedef long long ll;
//---------END-------//
typedef long long int_t;
int_t star[1000001];
struct node
{
    int_t lazy=0,val=0;
    node *nl=0, *nr=0;
};
struct DynamicSegTree
{
    node start;
    void reset()
    {
        resetK(&start);
    }
    void resetK(node* cur)
    {
        cur->lazy=0;
        cur->val=0;
        if (cur->nl) resetK(cur->nl);
        if (cur->nr) resetK(cur->nr);
    }
    void flusha(node* cur, int_t l, int_t r)
    {
        if (!(cur->nl)) cur->nl=new(node);
        if (!(cur->nr)) cur->nr=new(node);
        cur->nl->lazy+=cur->lazy;
        cur->nr->lazy+=cur->lazy;
        int_t mid=(l+r)/2;
        cur->nl->val+=(cur->lazy)*(mid-l+1);
        cur->nr->val+=(cur->lazy)*(r-(mid+1)+1);
        cur->lazy=0;
    }
    void updateK(node* cur, int_t l, int_t r, int_t tar_l, int_t tar_r, int_t diff)
    {
   //     cout<<"updateK "<<node<<' '<<l<<' '<<r<<' '<<tar_l<<' '<<tar_r<<endl; 
        if ((l>tar_r)or(r<tar_l)) return;
        else if ((l>=tar_l)and(r<=tar_r))
        {
            cur->lazy+=diff;
            cur->val+=diff*(r-l+1);
        }
        else
        {
            flusha(cur,l,r);
            int_t mid=(l+r)/2;
            updateK(cur->nl,l,mid,tar_l,tar_r,diff);
            updateK(cur->nr,mid+1,r,tar_l,tar_r,diff);
            cur->val=(cur->nl->val)+(cur->nr->val);
        }
        
    }
    void update(int_t l, int_t r, int_t diff)
    {
        updateK(&start,-1e9,1e9,l,r,diff);
    }
    int_t getK(node* cur, int_t l, int_t r, int_t tar_l, int_t tar_r)
    {
 
  //      cout<<"getK "<<node<<' '<<l<<' '<<r<<' '<<tar_l<<' '<<tar_r<<endl; 
        if ((l>tar_r)or(r<tar_l)) return 0;
        else if ((l>=tar_l)and(r<=tar_r))
        {
            return cur->val;
        }
        else
        {
            flusha(cur,l,r);
            int_t mid=(l+r)/2;
            int_t aa; aa=getK(cur->nl,l,mid,tar_l,tar_r);
            int_t bb; bb=getK(cur->nr,mid+1,r,tar_l,tar_r);
            return aa+bb;
        }
        
    }
    int_t get(int_t l, int_t r)
    {
        return getK(&start,-1e9,1e9,l,r);
    }
};
ll n,m,i,j,k,t;
ll a,b,u,v;
DynamicSegTree st;
int main()
{
    fio;
    cin>>n>>m;
    st.reset();
  //      for (i=1;i<=n;i++)    cout<<i<<' '<<st.get(i,i)<<endl;
    for (i=1;i<=m;i++)
    {
        cin>>k;
        if (k==1)
        {
            cin>>a>>b>>u; a++;
    //        cout<<b<<endl;
            st.update(a,b,u);
        }
        else
        {
            cin>>a>>b;a++;
            cout<<st.get(a,b)<<endl;
        }
    }
}
