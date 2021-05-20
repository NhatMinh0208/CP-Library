#ifndef CPL_TEMPLATE
#define CPL_TEMPLATE
/*
    Geometry utilities and interfaces, version 1.0.
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
namespace CPL_Geometry
{
/*
    CONVENTIONS:
    Angles are given in radians, except in function names for readability.
    Positive angles indicate CCW direction.
    Polygon points are listed in CCW direction.
*/
const ld eps=1e-10;
template<class T> int sgn(T x) {
    return ((x>0)-(x<0));
}

template<class T>
struct point{
    typedef point po;
    T x,y;
    point(T _x=0, T _y=0): x(_x),y(_y) {}

    bool operator< (po p)       {return tie(x,y)<tie(p.x,p.y);}
    bool operator< (const po p) const       {return tie(x,y)<tie(p.x,p.y);}
    bool operator== (po p)      {return tie(x,y)==tie(p.x,p.y);}

    po operator+= (po p)        {x+=p.x; y+=p.y; return (*this);}
    po operator+ (po p)         {return point(x+p.x,y+p.y);}

    po operator-= (po p)        {x-=p.x; y-=p.y; return (*this);}
    po operator- (po p)         {return point(x-p.x,y-p.y);}
    po operator- (const po p) const         {return point(x-p.x,y-p.y);}
    po operator- ()             {return point(-x,-y);}

    po operator*= (T d)         {x*=d; y*=d; return (*this);}
    po operator* (T d)          {return point(x*d,y*d);}

    po operator/= (T d)         {x/=d; y/=d; return (*this);}
    po operator/ (T d)          {return point(x/d,y/d);}

    T dot(po p)                 {return (x*p.x+y*p.y);}
    T cross(po p)               {return (x*p.y-y*p.x);} //>0 => (*this) is to the right of p
    T cross3(po u, po v)        {return (u-(*this)).cross(v-(*this));} //cross product between u and v with (*this) as origin

    T dist2()                   {return (x*x+y*y);}
    ld dist()                   {return sqrt((ld)dist2());}
    po unitVec()                {return (*this)/dist();}


    ld angle()                  {return atan2(y,x);} // angle relative to x-axis
    po rot90()                  {return point(-y,x);}
    po normal()                 {return rot90().unit();}
    po rotate(ld a)             {return point(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));}

    friend ostream& operator<<(ostream& os, po p)
    {
        return os<<"po("<<p.x<<","<<p.y<<")";
    }
};
typedef point<ld> P;
typedef ld T;

// Distance
//template<class P> 
ld distToLine(P u, P v, P p);                // signed distance from p to vector u->v
//template<class P> 
int lineSide(P u, P v, P p, ld per=eps);     // side of p with respect to vector u->v  
//template<class P> 
ld distToSeg(P u, P v, P p);                 // distance from p to segment (u,v)
//template<class P> 
int onSeg(P u, P v, P p);                    // is p on segment (u,v)?


// Intersection
//template<class P> 
vector<P> segIntersect(P u1, P v1, P u2, P v2);      // intersections of segments (u1,v1) and (u2,v2)
//template<class P> 
pair<int,P> lineIntersect(P u1, P v1, P u2, P v2);   // intersection of lines (u1,v1) and (u2,v2). 0=two parallel lines, -1=two lines coincide


//template<class P> 
P linearTransform(P u1, P v1, P u2, P v2, P r);      // Let f be a linear transformation defined by f(u1)=u2 and f(v1)=v2. Returns f(r).


// Circle
//template<class P>
vector<vector<P>> circleTangent(P u1, ld r1, P u2, ld r2);  // tangent lines of circles (u1,r1) and (u2,r2)
//template<class P> 
vector<P> circleIntersect(P u1, ld r1, P u2, ld r2);        // intersections of circles (u1,r1) and (u2,r2)
//template<class P>
ld circlePolyArea(P u, ld r, vector<P> poly);               // area of intersection between circle (u,r) and polygon (poly)
//template<class P>
pair<P,ld> circumcircle(P a, P b, P c);                     // circumcircle of 3 points a,b,c
//template<class P>
pair<P,ld> minEnclose(vector<P> pts);                       // minimum-radius enclosing circle of a set of points


// Polygon
//template<class P>
int inPolygon(vector<P> poly, P u, int strict=0); // is u inside polygon p? strict=1 makes "on the boundary" returns false. 
//template<class T>
T polyArea2(vector<point<T>> poly);               // area of polygon, multiplied by 2
//template<class P>
P polyCenter(vector<P> poly);                     // center of mass of polygon
//template<class P>
vector<P> lineRemove(vector<P> poly, P u, P v);   // remove the part to the left (CCW) of vector (u->v) from polygon


// Convex hull/polygon
//template<class P>
vector<P> convexHull(vector<P> pts);                   // convex hull of a set of points O(nlogn)
//template<class T>
pair<T,pii(point<T>)> hullDiam(vector<point<T>> hull); // longest diagonal in a convex polygon (O(n))
// All of these are O(logn) time
//template<class P>
int inHull(vector<P> hull, P u, int strict=0);         // is u inside convex polygon p? strict=1 makes "on the boundary" returns false.
//template<class P>
int extrVertex(vector<P>& hull, P vec);                // returns index of vertex with highest projection onto vector      
//template<class P>
vector<int> lineHull(P a, P b, vector<P>& hull);       // returns index of intersection(s) of (a,b) with convex polygon
// Return table for lineHull:
// (-1,-1) = no intersection
// ( i,-1) = touches i
// ( i, i) = touches line (i,i+1)
// ( i, j) = intersects lines (i,i+1) and (j,j+1)

// Misc.
//template<class T>
pair<T,pii(point<T>)> closest(vector<point<T>> pts); // nearest pair of points in set (O(nlogn))
}