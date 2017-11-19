#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
//判断x大于，小于或者等于0
//PI的值
const double PI=acos(-1.0);
const double eps = 1e-10;
int dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    else return x<0?-1:1;
}
//点定义
struct Point
{
    double x,y;
    Point(double x=0, double y=0):x(x),y(y){}
};
//向量定义
typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }
double Dot(const Vector& A, const Vector& B) {return A.x*B.x+A.y*B.y;}
double Length(const Vector& A){return sqrt(Dot(A, A));}
double Angle(const Vector& A,const Vector& B){return acos(Dot(A, B)/Length(A)/Length(B));}
double Cross(const Vector& A,const Vector& B){return A.x*B.y-A.y*B.x;}
Vector Rotate(const Vector& A,double rad){return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));}
Vector Normal(Vector A)
{
    double L = Length(A);
    return Vector(-A.y/L, A.x/L);
}
//读一个点
Point read_point()
{
    double x,y;
    scanf("%lf%lf",&x,&y);
    return Point(x,y);
};
Point P,Q,A[maxn],B[maxn];
int n,m;
double x,y;
double r;
bool getmind(Point O,Point A,Point B)
{
    double minD=min(Length(O-A),Length(O-B));
    Vector OC=A-O;
    Vector OD=B-O;
    Vector OH=Rotate(B-A,PI/2);
    if(dcmp(Cross(OH,OC))*dcmp(Cross(OH,OD))>=0)return minD;
    double h=fabs(Cross(OC,OD))/Length(B-A);
    return h;
}
bool solve(Point O,Point A,Point B)
{
    double maxd=max(Length(O-A),Length(O-B));
    double mind=getmind(O,A,B);
    if(dcmp(r-mind)>=0&&dcmp(maxd-r)>=0)return true;
    else return false;
}
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>x>>y)
    {
        P=Point(x,y);
        cin>>n;
        for(int i=0;i<n;i++)A[i]=read_point();
        cin>>x>>y;
        Q=Point(x,y);
        cin>>m;
        for(int i=0;i<m;i++)B[i]=read_point();
        Vector PQ=Q-P;
        r=Length(PQ);
        bool ans=false;
        for(int i=0;i<n;i++)
        {
            Point O=A[i]+PQ;
            for(int j=0;j<m;j++)
                ans|=solve(O,B[j],B[(j+1)%m]);
        }
        for(int i=0;i<m;i++)
        {
            Point O=B[i]-PQ;
            for(int j=0;j<n;j++)
                ans|=solve(O,A[j],A[(j+1)%n]);
        }
        printf("%s\n",ans?"YES":"NO");
    }
    return 0;
}
