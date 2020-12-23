#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void reduce(vector<int> &v)
{
	while ((v.size())and(v[v.size()-1]==0)) v.pop_back();
}
void string_to_vector(string &s, vector<int> &res)
{
	res.clear();
	for (int i=s.size()-1;i>=0;i--) res.push_back(s[i]-48);
	reduce(res);
}
void equalize(vector<int> &a, vector<int> &b)
{
	while(a.size()<b.size()) a.push_back(0);
	while(a.size()>b.size()) b.push_back(0);
}
void add(vector<int> &a, vector<int> &b, vector<int> &c)
{
	equalize(a,b);
	c.clear();
	int cur=0;
	for (int i=0;i<a.size();i++)
	{
		cur+=a[i];
		cur+=b[i];
		c.push_back(cur%10);
		cur/=10;
	}
	if (cur) c.push_back(cur);
	reduce(a);
	reduce(b);
	reduce(c);
}
int subtract(vector<int> &a, vector<int> &b, vector<int> &c)
{
	equalize(a,b);
	c.clear();
	int cur=0,sign=0;
	for (int i=a.size()-1;i>=0;i--) 
	if ((sign==0)and(a[i]>b[i])) sign=1; else if ((sign==0)and(a[i]<b[i])) sign=-1;
	if (sign>=0)
	{
		for (int i=0;i<a.size();i++)
		{
			cur+=a[i];
			cur-=b[i];
			c.push_back((cur+10)%10);
			if (cur<0) cur=-1; else cur=0;
		}
	}
	else
	{
		for (int i=0;i<a.size();i++)
		{
			cur+=b[i];
			cur-=a[i];
			c.push_back((cur+10)%10);
			if (cur<0) cur=-1; else cur=0;
		}
	}
	reduce(a);
	reduce(b);
	reduce(c);
	return sign;
}
void vector_to_string(vector<int> &v, string &res)
{
	res="";
	reduce(v);
		char c;
	for (int i=v.size()-1;i>=0;i--) 
	{
		c=v[i]+48;
		res.push_back(c);
	}
	if (res=="") res="0";
}
ll ia,ib,ic;
string sa,sb,sc;
vector<int> va,vb,vc;
int main()
{
	srand(time(NULL));
	cout<<"Testing 10000000 iterations of function add...\n";
	for (int t=1;t<=10000000;t++)
	{
		ia=(rand()<<15)^(rand());
		ib=(rand()<<15)^(rand());
		if (t<=1000000)
		{
			ia%=100;
			ib%=100;
		}
		sa=to_string(ia);
		sb=to_string(ib);
		string_to_vector(sa,va);
		string_to_vector(sb,vb);
		add(va,vb,vc);
		vector_to_string(vc,sc);
		ic=stoi(sc);
		if (ia+ib-ic)
		{
			cout<<"Test "<<t<<" failed!\n";
			cout<<"sa="<<sa<<endl;
			cout<<"sb="<<sb<<endl;
			cout<<"sc="<<sc<<endl;
			return 0;
		}
		if (t%100000==0) 
		{
		
		cout<<t/100000<<"% completed.\n";
			cout<<"Test "<<t<<" 's description:\n";
			cout<<"sa="<<sa<<endl;
			cout<<"sb="<<sb<<endl;
			cout<<"sc="<<sc<<endl;
		}
	}
	
	///////////////////////////////////////////////////////
	
	cout<<"Testing 10000000 iterations of function subtract...\n";
	for (int t=1;t<=10000000;t++)
	{
		ia=(rand()<<15)^(rand());
		ib=(rand()<<15)^(rand());
		if (t<=1000000)
		{
			ia%=100;
			ib%=100;
		}
		sa=to_string(ia);
		sb=to_string(ib);
		string_to_vector(sa,va);
		string_to_vector(sb,vb);
		int res=subtract(va,vb,vc);
		vector_to_string(vc,sc);
		ic=stoi(sc);
		if ((abs(ia-ib)!=ic)or((ia<ib)and(res!=-1))or((ia==ib)and(res!=0))or((ia>ib)and(res!=1)))
		{
			cout<<"Test "<<t<<" failed!\n";
			cout<<"sa="<<sa<<endl;
			cout<<"sb="<<sb<<endl;
			cout<<"sc="<<sc<<endl;
			return 0;
		}
		if (t%100000==0) 
		{
		
		cout<<t/100000<<"% completed.\n";
			cout<<"Test "<<t<<" 's description:\n";
			cout<<"sa="<<sa<<endl;
			cout<<"sb="<<sb<<endl;
			cout<<"sc="<<sc<<endl;
		}
	}
}
