#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
    Geometry implementations, version 1.0.
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
 
//Pragmas (Comment out these three lines if you're submitting in szkopul.)
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
#include "GeometryIface.hpp"
namespace CPL_Geometry
{

//template<class P> 
ld distToLine(P u, P v, P p)
{
    return (ld)(v-u).cross(p-u)/(v-u).dist();
}

//template<class P> 
ld distToSeg(P u, P v, P p)
{
    if (u==v) return (p-u).dist();
    auto dis=(v-u).dist2();
    auto t=min(dis,max((ld)0,(p-u).dot(v-u)));
    return ((p-u)*dis-(v-u)*t).dist()/dis;
}

//template<class P> 
int onSeg(P u, P v, P p) 
{
    return ((ld)distToSeg(u,v,p)<=eps);
}
//template<class P> 
vector<P> segIntersect(P u1, P u2, P v1, P v2)
{
    vector<P> res;
    auto oa=v1.cross3(v2,u1);
    auto ob=v1.cross3(v2,u2);
    auto oc=u1.cross3(u2,v1);
    auto od=u1.cross3(u2,v2);
    if ((sgn(oa)*sgn(ob)<0)and(sgn(oc)*sgn(od)<0))
    {
        res.push_back((u1*ob-u2*oa)/(ob-oa));
    }
    else
    {
        if (onSeg(v1,v2,u1)) res.push_back(u1);
        if (onSeg(v1,v2,u2)) res.push_back(u2);
        if (onSeg(u1,u2,v1)) res.push_back(v1);
        if (onSeg(u1,u2,v2)) res.push_back(v2);
    }
    sort(res.begin(),res.end());
    auto it=unique(res.begin(),res.end());
    res.erase(it,res.end());
    return res;
}

//template<class P> 
pair<int,P> lineIntersect(P u1, P v1, P u2, P v2)
{
    auto d=(v1-u1).cross(v2-u2);
    if (d==0) return {-(u1.cross3(v1,v2)==0), P(0,0)};
    auto p=u2.cross3(v1,v2);
    auto q=u2.cross3(v2,u1);
    return {1, (u1*p+v1*q)/d};
}

//template<class P> 
int lineSide(P u, P v, P p, ld per)
{
    auto uu=distToLine(u,v,p);
    if (uu<-per) return -1;
    if (uu>per) return 1;
    return 0;
}

//template<class P> 
P linearTransform(P u1, P v1, P u2, P v2, P r)
{
    P d1=v1-u1,d2=v2-u2;
    P num=(d1.cross(d2), d1.dot(d2));
    return u2+P((r-u1).cross(num), (r-u1).dot(num)/d1.dist2());
}

//template<class P> 
vector<P> circleIntersect(P u1, ld r1, P u2, ld r2)
{
    if (u1==u2) {
        assert(r1-r2);
        return {};
    }
    P d=u2-u1;
    ld d2=d.dist2(),sum=r1+r2,dif=r1-r2;
    ld p=(d2+r1*r1-r2*r2)/(d2*2);
    ld h2=(r1*r1 - p*p*d2);
    if ((sum*sum<d2)or(dif*dif>d2)) return {};
    P mid = u1+d*p,per=d.rot90()*sqrt(fmax(0,h2)/d2);
    return {mid+per,mid-per};
}

//template<class P>
vector<vector<P>> circleTangent(P u1, ld r1, P u2, ld r2)
{
    P d=u2-u1;
    ld dr=r1-r2, d2=d.dist2(), h2=d2-dr*dr;
    if ((d2==0)or(h2<0)) return {};
    vector<vector<P>> res;
    for (ld sgn : {-1,1})
    {
        P v=(d*dr+d.rot90()*sqrt(h2)*sgn)/d2;
        res.push_back({u1+v*r1,u2+v*r2});
    }
    if (h2==0) res.pop_back();
    return res;
}

//template<class P>
ld arg(P p, P q) 
{
    return atan2(p.cross(q),p.dot(q));
}

//template<class P>
ld circleTriArea(ld r, P v1, P v2)
{
    ld r2=r*r/2;
    P d= v2-v1;
    auto a=d.dot(v1)/d.dist2();
    auto b=(v1.dist2()-r*r)/d.dist2();
    auto det=a*a-b;
    ld res=arg(v1,v2)*r2;
    if (det<=0) return res;
    auto s=max(ld(0),-a-sqrt(det));
    auto t=min(ld(1),-a+sqrt(det));
    if ((t<0)or(s>=1)) return res;
    P u1=v1+d*s,u2=v1+d*t;
    return arg(v1,u1)*r2+ u1.cross(u2)/2+arg(u2,v2)*r2;
}

//template<class P>
ld circlePolyArea(P u, ld r, vector<P> poly)
{
    ld res=0;
    for (int i=0;i<poly.size();i++)
    res+=circleTriArea(r,poly[i]-u,poly[(i+1)%poly.size()]-u);
    return res;
}

//template<class P>
pair<P,ld> circumcircle(P a, P b, P c)
{
    ld radius=(b-a).dist()
             *(c-b).dist()
             *(a-c).dist()
             /abs((b-a).cross(c-a))/2;
    P db=c-a,dc=b-a;
    P center=a+(db*dc.dist2()-dc*db.dist2()).rot90()
            /db.cross(dc)/2;
    return {center,radius};
}

//template<class P>
pair<P, ld> minEnclose(vector<P> pts) 
{
    shuffle(pts.begin(),pts.end(), mt19937(time(0)));
    P o = pts[0];
    double r = 0;
    for (int i=0;i<pts.size();i++) if ((o - pts[i]).dist() > r * (eps+1)) 
    {
        o = pts[i], r = 0;
        for (int j=0;j<i;j++) 
        if ((o-pts[j]).dist()> r * (eps+1)) 
        {
            o=(pts[i]+pts[j])/2;
            r=(o-pts[i]).dist();
            for (int k=0;k<j;k++) 
            if ((o-pts[k]).dist()>r*(eps+1)) 
            {
                o=circumcircle(pts[i], pts[j], pts[k]).se;
                r=(o-pts[i]).dist();
            }
        }
    }
    return {o, r};
}

//tempate<class P>
int inPolygon(vector<P> poly, P u, int strict)
{
    int cnt=0, n=poly.size();
    for (int i=0;i<n;i++)
    {
        P v2=poly[(i+1)%n],v1=poly[i];
        if (onSeg(v1,v2,u)) return (strict^1);
        cnt^= (((u.y<v1.y)-(u.y<v2.y))*u.cross3(v1,v2)>0);
    }
    return cnt;
}

//template<class T>
T polyArea2(vector<point<T>> poly)
{
    T res=0;
    int n=poly.size();
    for (int i=0;i<n;i++)
    {
        res+=poly[i].cross(poly[(i+1)%n]);
    }
    return res;
}

//template<class P>
P polyCenter(vector<P> poly)
{
    P res(0,0); ld area=0;
    int n=poly.size(),i,j;
    for (i=0;i<n;i++)
    {
        j=(i+n-1)%n;
        res=res+(poly[i]+poly[j])*poly[j].cross(poly[i]);
        area+=poly[j].cross(poly[i]);
    }
    return res/area/3;
}

//template<class P>
vector<P> lineRemove(vector<P> poly, P u, P v)
{
    vector<P> res;
    int n=poly.size();
    for (int i=0;i<n;i++)
    {
        P cur=poly[i];
        P prev=poly[(i+n-1)%n];
        if ((u.cross3(v,cur)<0)-(u.cross3(v,prev)<0))
        {
            res.push_back(lineIntersect(u,v,cur,prev).se);
        }
        if ((u.cross3(v,cur)<0))
        {
            res.push_back(cur);
        }
    }
        return res;
}

//template<class P>
vector<P> convexHull(vector<P> pts)
{
    int n=pts.size();
    if (n<=2) return pts;
    sort(pts.begin(),pts.end());
    vector<P> h(n+1);
    int s=0,t=0;
    for (int it=2; it--; s=--t, reverse(pts.begin(),pts.end()))
    {
        for (P p : pts)
        {
            while((t>=s+2)and(h[t-2].cross3(h[t-1],p)<=0)) t--;
            h[t++]=p;
        }
    }
    return {h.begin(),h.begin()+t-((t==2)and(h[0]==h[1]))};
}

//template<class T>
pair<T,pii(point<T>)> hullDiam(vector<point<T>> hull)
{
    int n=hull.size(),i,j=(n<2?0:1);
    pair<T,pii(point<T>)> res={0,{hull[0],hull[0]}},cur;
    for (i=0;i<j;i++)
    {
        for (;; j=(j+1)%n)
        {
            cur={(hull[i]-hull[j]).dist2(),{hull[i],hull[j]}};
            res=max(res,cur);
            if ((hull[(j+1)%n]-hull[j]).cross(hull[i+1]-hull[i])>=0)
            break;
        }
    }
    return res;
}

//template<class P>
int inHull(vector<P> hull, P u, int strict)
{
    int a=1,b=hull.size()-1,r=strict^1;
    if (hull.size()<3) return ((r)and(onSeg(hull[0],hull.back(),u)));
    if (lineSide(hull[0],hull[a],hull[b])>0) swap(a,b);
    if ((lineSide(hull[0],hull[a],u)>=r)or(lineSide(hull[0],hull[b],u)<=-r))
    return 0;
    while(abs(a-b)>1)
    {
        int c=(a+b)/2;
        if (lineSide(hull[0],hull[c],u)>0) b=c;
        else a=c;
    }
    return sgn(hull[a].cross3(hull[b],u))<r;
}

#define cmp(i,j) sgn(vec.rot90().cross(hull[(i)%n]-hull[(j)%n]))
#define extr(i) ((cmp(i+1,i)>=0)and(cmp(i,i-1+n)<0))

//template<class P> 
int extrVertex(vector<P>& hull, P vec) 
{
    int n=hull.size(), l=0, r=n;
    if (extr(0)) return 0;
    while (l+1<r) 
    {
        int mid=(l+r)/2;
        if (extr(mid)) return mid;
        int ls=cmp(l+1,l), ms=cmp(mid+1,mid);
        if ((ls<ms)or((ls==ms)and(ls==cmp(l, mid))))
            r=mid;
        else 
            l=mid;
    }
    return l;
}

#define cmpL(i) sgn(a.cross3(hull[i], b))

//template<class P>
vector<int> lineHull(P a, P b, vector<P>& hull) 
{
    int endA=extrVertex(hull,(a-b).rot90());
    int endB=extrVertex(hull,(b-a).rot90());
    if ((cmpL(endA)<0)or(cmpL(endB)>0))
    return {-1, -1};
    vector<int> res(2);
    for (int i=0;i<2;i++)
    {
        int l=endB, r=endA, n=hull.size();
        while ((l+1)%n!=r) 
        {
            int mid=((l+r+(l<r?0:n))/2)%n;
            if (cmpL(mid)==cmpL(endB)) l=mid;
            else r=mid;
        }
        res[i] = (l+!cmpL(r)) % n;
        swap(endA, endB);
    }
    if (res[0]==res[1]) return {res[0],-1};
    if (!cmpL(res[0]) && !cmpL(res[1]))
    switch ((res[0] - res[1] + hull.size() + 1) % hull.size()) 
    {
        case 0: return {res[0], res[0]};
        case 2: return {res[1], res[1]};
    }
    return res;
}

//template<class T>
pair<T,pii(point<T>)> closest(vector<point<T>> pts)
{
    assert(pts.size()>1);
    set<point<T>> sett;
    sort(pts.begin(),pts.end(),[](point<T> a, point<T> b){
        return (a.y<b.y);
    });
    pair<T,pii(point<T>)> res(4e18,pii(point<T>)(point<T>(),point<T>()));
    int j=0;
    for (point<T> p : pts)
    {
        point<T> d(1+sqrt(res.fi),0);
        while(pts[j].y<p.y-d.x) sett.erase(pts[j++]);
        auto l=sett.lower_bound(p-d);
        auto r=sett.upper_bound(p+d);
        for (;l!=r;++l)
        {
            auto cur=pair<T,pii(point<T>)>(((*l)-p).dist2(),pii(point<T>)((*l),p));
            res=min(res,cur);
        }
            sett.insert(p);
    }
    return res;
}

}
vector<int> vec;
int n,m,i,j,k,t,t1,u,v,a,b;
int main()
{
	fio;
}
