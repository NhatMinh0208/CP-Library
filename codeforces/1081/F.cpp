// Problem : F. Make It One
// Contest : Codeforces - Codeforces Round #519 by Botan Investments
// URL : https://codeforces.com/problemset/problem/1043/F
// Memory Limit : 256 MB
// Time Limit : 3000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)
 
/*
 A Submission by $%U%$
 at time: $%Y%$-$%M%$-$%D%$ $%h%$:$%m%$:$%s%$
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
#define For(i,__,___) for(int i=__;i<=___;i++)
#define Rep(i,__,___) for(int i=__;i>=___;i--)
#define ordered_set tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update>

#define bi BigInt
typedef long long ll;
//---------END-------//
 
const int N = 305;
 
int n, t, lst, a[N], pre[N];
 
pair<int, int> ask(int l, int r)
{
    cout << "? " << l << " " << r << endl;
    int ret; cin >> ret;
    assert(ret >= 0);
    int msk = 1 << (abs(ret - lst) % 2 == r % 2);
    lst = ret;
    return {ret, msk};
}
 
int get(int l, int r, bool le)
{
    int len = le ? r : n - l + 1;
    while (true)
    {
        pair<int, int> ans = ask(l, r);
        int msk = ans.se;
        while (ans.se != 0)
            ans.se ^= ask(l, r).se;
        if (msk == (1 << le))
            return (t - ans.fi + len) / 2;
    }
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> t;
    lst = t;
    if (n == 1)
        return cout << "! " << t << endl, 0;
    if (n % 2 == 0)
        pre[1] = get(1, 1, true);
    else
        pre[1] = t - get(2, n, false);
    for (int i = 2; i <= n; i++)
        pre[i] = get(i - n % 2, i, true);
    cout << "! ";
    for (int i = 1; i <= n; i++)
        cout << pre[i] - pre[i - 1];
    cout << endl;
}