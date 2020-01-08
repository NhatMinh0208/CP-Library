#include <algorithm>
#include <stdio.h>
#include <string.h>
#include<vector>
#define maxn 5011
#define maxm 61000
 
using namespace std;
 
typedef long long int LD;
 int i,j,n,m;
 
int p[1000];
 
int noprime[20010];
int q[20010], t;
struct Graph {
  int n, et, ind[maxn], e[maxm], last[maxm];
 
  bool checked[maxn];
 
  vector<vector<int>> blocks;
 
  int nowcolor;
 
  inline void adde(int a, int b) {
    last[++et] = ind[a];
    e[et] = b;
    ind[a] = et;
  }
 
  inline void init(int nn) {
    n = nn, et = 1;
    memset(ind, 0, sizeof(int) * (n + 1));
  }
  void dfs(int a) {
    checked[a]=true;
    int i;
    blocks[nowcolor].push_back(a);
    for(i=ind[a];i;i=last[i]) if(!checked[e[i]]) {
      dfs(e[i]);
    }
  }
  void colorit() {
    int i;
    for(i=1;i<=n;i++) if(!checked[i]) {
      blocks.push_back({});
      dfs(i);
      nowcolor++;
    }
  }
};
 
struct FlowGraph : public Graph {
  int S, T;
 
  LD cap[maxm], f[maxm];
 
  inline void adde(int a, int b, LD c) {
    Graph::adde(a, b);
    f[et] = 0, cap[et] = c;
  }
 
  inline void addee(int a, int b, LD c) { adde(a, b, c), adde(b, a, c); }
 
  inline void init(int nn, int s, int t) {
    Graph::init(nn);
    S = s, T = t;
  }
};
 
struct ResiGraph : public FlowGraph {
  int ek[maxm];
  bool checked[maxn];
 
  void adde(int a, int b, LD c, int k) {
    FlowGraph::adde(a, b, c);
    ek[et] = k;
  }
 
  LD dfs(int a, LD flow) {
    if (flow == 0) {
      return 0;
    }
    if (a == T)
      return flow;
 
    LD ans = 0, now;
 
    for (int i = ind[a]; i; i = last[i])
      if (!checked[e[i]] && cap[i] - f[i]) {
        now = dfs(e[i], std::min(flow, cap[i] - f[i]));
        ans += now, f[i] += now, flow -= now;
      }
    if (flow)
      checked[a] = true;
    return ans;
  }
 
  LD blocking_flow() {
    LD upper_bound = 0;
    memset(checked, 0, sizeof(bool) * (n + 1));
    for (int i = ind[S]; i; i = last[i]) {
      upper_bound += cap[i];
    }
    return dfs(S, upper_bound);
  }
};
 
struct DinicGraph : public FlowGraph {
  ResiGraph resi;
  int que[maxn], nowqt, qt, checked[maxn];
 
  LD cf() {
    resi.init(n, S, T);
    memset(checked, 0, sizeof(int) * (n + 1));
    qt = nowqt = 1;
    que[1] = S;
    checked[S] = 1;
 
    for (int i = 1, j = 0, nowlv = 2; i <= qt; i++) {
      if (i > nowqt) {
        nowlv++, nowqt = qt;
        if (checked[T]) {
          break;
        }
      }
 
      for (j = ind[que[i]]; j; j = last[j])
        if ((!checked[e[j]] || checked[e[j]] == nowlv) && f[j] < cap[j]) {
          if ((j & 1) && f[j ^ 1]) {
            resi.adde(que[i], e[j], f[j ^ 1], j);
            if (!checked[e[j]]) {
              que[++qt] = e[j];
              checked[e[j]] = nowlv;
            }
          } else if (!(j & 1)) {
            resi.adde(que[i], e[j], cap[j] - f[j], j);
            if (!checked[e[j]]) {
              que[++qt] = e[j];
              checked[e[j]] = nowlv;
            }
          }
        }
    }
 
    LD incr = resi.blocking_flow();
    if (incr == 0) {
      return 0;
    }
 
    for (int i = 1, j, k; i <= n; i++) {
      for (j = resi.ind[i]; j; j = resi.last[j])
        if (resi.f[j]) {
          k = resi.ek[j];
          if (f[k ^ 1]) {
            f[k ^ 1] -= resi.f[j];
          } else {
            f[k] += resi.f[j];
          }
        }
    }
    return incr;
  }
 
  LD maxflow() {
    LD ans = 0, now = cf();
    while (now) {
      ans += now;
      now = cf();
    }
    return ans;
  }
} G;
 
 
void prepare() {
  int i, j;
  for(i=2;i<20010;i++) {
    if(!noprime[i]) {
      q[++t]=i;
      noprime[i]=i;
    }
    for(j=1;j<=t;j++) {
      if(double(q[j])*i + 1e-9< 20010) {
        noprime[q[j]*i] = q[j];
      } else {
        break;
      }
      if(i%q[j]==0)
        break;
    }
  }
}
 
Graph gg;
 
int main() {
  prepare();
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
  }
  if(n&1) {
    printf("Impossible\n");
    return 0;
  }
  int S = n+1, T=n+2;
  G.init(T, S, T);
  for(i=1;i<=n;i++) if(p[i]&1){
    G.addee(S, i, 2);
    for(j=1;j<=n;j++) {
      if(noprime[p[i]+p[j]] == p[i] + p[j]) {
        G.addee(i, j, 1);
      }
    }
  } else {
    G.addee(i, T, 2);
  }
  int ans = G.maxflow();
  if(ans!=n) {
    printf("Impossible\n");
    return 0;
  }
 
  gg.init(n);
  for(i=1;i<=n;i++) {
    for(j=G.ind[i];j;j=G.last[j]) if(!(j&1) && G.f[j]&& G.e[j] <= n) {
      gg.adde(i, G.e[j]);
      gg.adde(G.e[j], i);
    }
  }
  gg.colorit();
  printf("%d\n", gg.nowcolor);
  for(i=0;i<gg.nowcolor;i++) {
    printf("%d", (int) gg.blocks[i].size());
    for( auto jj : gg.blocks[i]) {
      printf(" %d", jj);
    }
    printf("\n");
  }
 
 
  return 0;
}