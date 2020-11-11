#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pll pair<ll,ll>
#define fi first
#define se second
#define bitvector bitset<501>
struct bitmatrix
{
    bitvector hh[501],vv[501];
    void assign(int i, int j, int k)
    {
        hh[i][j]=(k==1);
        vv[j][i]=(k==1);
    }
    int get(int i, int j)
    {
  //      cout<<"get "<<i<<' '<<j<<' '<<hh[i][j]<<endl;
       return hh[i][j]; 
    }
};
bitmatrix mulmm(bitmatrix a, bitmatrix b)
{
    bitmatrix c;
    int i,j;
    for (i=1;i<=500;i++) for (j=1;j<=500;j++)
    {
        c.assign(i,j,((a.hh[i]&b.vv[j]).count())%2);
    }
	return c;
}
bitvector mulvm (bitvector a, bitmatrix b)
{
    bitvector c;
    int i,j;
	for (i=1;i<=500;i++) for (j=1;j<=500;j++)
	{
	    c[j]=c[j]^(int(a[i])&b.get(i,j));
	}
	return c;
}
bitmatrix bowm(bitmatrix a, ll x)
{
//	cout<<"bowm "<<' '<<x<<endl;
	if (x==1) return a;
	auto res=bowm(a,x/2);
	res=mulmm(res,res);
	if (x%2) res=mulmm(res,a);
	return res;
}