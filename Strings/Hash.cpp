#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int64_t i=0;i < (int64_t)(n);i++)
 
#define FILE_IN "pviz.in"
#define FILE_OUT "pviz.out"
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
#define pow2(x) (ll(1)<<x)
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
#define endl "\n"
 
ll n,m,i,j,k;
    seed_seq seq{
        (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
        (uint64_t) __builtin_ia32_rdtsc(),
        (uint64_t) (uintptr_t) make_unique<char>().get()
    };
    mt19937 rng(seq);
    int p,base;
    int prime(ll x)
    {
    	if (x<2) return 0;
    	for (int i=2;i<=sqrt(x);i++) if (x%i==0) return 0;
    	return 1;
    }
ll get_p()
{
	ll res;
	while(true)
	{
		res=uniform_int_distribution<int>(1e9, 2e9)(rng);
		if (prime(res)) return res;
	}
}
ll bow (ll a, ll x)
{
	if (!x) return 1;
    ll res=bow(a,x/2);
    res*=res;
    res%=p;
    if (x%2) res*=a;
    res%=p;
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
	string s,t;
	cin>>s>>t;
	n=s.length();
	m=t.length();
	p=get_p();
    base = uniform_int_distribution<int>(27, p-1)(rng);
    ll cur[n+1],tar=0;
    for (i=0;i<m;i++)
    {
    	tar*=base;
    	tar+=t[i]-96;
    	tar%=p;
    }
//    cout<<base<<' '<<p<<endl;
    cur[0]=0;
    for (i=0;i<n;i++)
    {
        cur[i+1]=cur[i];
    	cur[i+1]*=base;
    	cur[i+1]+=s[i]-96;
    	cur[i+1]%=p;
        }
        for (i=0;i+m<=n;i++)
        {
//            cout<<cur[i]<<endl;
            ll itr=(cur[i]*bow(base,m))%p;
            ll fin=(cur[i+m]-itr+p)%p;
            fin+=p;
            fin%=p;
//            cout<<fin<<' '<<tar<<endl;
            if (fin==tar) cout<<i+1<<' ';
        }
}


