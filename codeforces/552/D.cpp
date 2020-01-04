#include<bits/stdc++.h>
using namespace std;
 
const int mx=2005;
int x[mx], y[mx];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	int n; cin>>n;
	for (int i=0; i<n; i++) cin>>x[i]>>y[i];
	int ret=0;
	for (int i=0; i<n; i++)
		for (int j=i+1; j<n; j++)
			for (int k=j+1; k<n; k++)
				if(x[i]*(y[j]-y[k])+x[j]*(y[k]-y[i])+x[k]*(y[i]-y[j])!=0) ret++;
	cout << ret << endl;
}
