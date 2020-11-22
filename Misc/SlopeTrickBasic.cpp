#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct slope_func 
{
	public:
	ll a,b;
	priority_queue<ll> bp;
	slope_func(ll aa, ll bb, vector<ll> v)
	{
		a=aa;
		b=bb;
		for (ll g : v) bp.push(g);
	}
	void slope_add (ll aa, ll bb, vector<ll> v)
	{
		a+=aa;
		b+=bb;
		for (ll g : v) bp.push(g);
	}	
	void slope_min()
	{
		while(a+bp.size()>0) bp.pop();
	}
};