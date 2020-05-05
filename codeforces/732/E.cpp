/*
 A Submission by $%U%$
 at time: $%Y%$-$%M%$-$%D%$ $%h%$:$%m%$:$%s%$
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
#define FILE_IN "tayto.inp"
#define FILE_OUT "tayto.out"
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
typedef long long ll;
//---------END-------// 
int main()
{
    fio;
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> s(m + 1);
  vector<int> c(n + 1);
  unordered_map<int, vector<int>> t;
  for (int i = 1; i <= n; ++i) {
    cin >> c[i];
    t[c[i]].push_back(i);
  }
  for (int i = 1; i <= m; ++i) {
    cin >> s[i].first;
    s[i].second = i;
  }
  sort(s.begin(), s.end());
  int ta = 0, tc = 0;
  vector<int> na(m + 1);
  vector<int> cs(n + 1);
  for (int i = 1; i <= m; ++i) {
    int u = s[i].first;
    int cnt = 0;
    while (1) {
      if (!t[u].empty()) {
        cs[t[u].back()] = s[i].second;
        t[u].pop_back();
        na[s[i].second] = cnt;
        ta += cnt;
        ++tc;
        break;
      }
      if (u == 1) break;
      u = (u + 1) / 2;
      ++cnt;
    }
  }
  cout << tc << ' ' << ta << endl;
  for (int i = 1; i <= m; ++i) {
    cout << na[i] << ' ';
  }
  cout << endl;
  for (int i = 1; i <= n; ++i) {
    cout << cs[i] << ' ';
  }
  cout << endl;
}
 