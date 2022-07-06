#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
/*
#define I
#define J
#define K
*/

namespace help{

}

struct quat{
    double x,y,z,w;

    quat(double a, double b, double c, double d){
        x = a;
        y = b;
        z = c;
        w = d;
    }

    quat operator+ (quat q){
        quat q1(x + q.x, y + q.y, z + q.z, w + q.w);
        return q1;
    }

    quat operator+ (double c){
        quat q(x + c, y, z, w);
        return q;
    }

    quat operator- (quat q){
        quat q1(x - q.x, y - q.y, z - q.z, w - q.w);
        return q1;
    }

    quat operator- (double c){
        quat q(x-c, y, z, w);
        return q;
    }

    quat operator* (quat q){
        quat q1(x*q.x - y*q.y - z*q.z - w*q.w,x*q.y + y*q.x + z*q.w - w*q.z, x*q.z + z*q.x + w*q.y - y*q.w, x*q.w + w*q.x + y*q.z - z*q.y);
        return q1;
    }

    quat operator* (double c){
        quat q(x*c, y*c, z*c, w*c);
        return q;
    }

    quat operator-- (){ //sopr
        quat q(x, -y, -z, -w);
        return q;
    }

    quat operator/ (double c)
    {
        quat q(x/c, y/c, z/c, w/c);
        return q;
    }

    quat operator/ (quat q)
    {
        quat q0(x,y,z,w);

        q0 = (q0*(--q))/((q*(--q)).x);

        return q0;
    }

    void DispQuat(){
        cout << "q = " << x << " + " << y << "i + " << z << "j + " << w << 'k' << endl;
    }

};

struct figure{
    vector<quat> dots;

    figure(quat* r, long int n){
        for(long int i = 0; i < n; ++i)
            dots.push_back(r[i]);
    }
    /*
     void RotateRelPoint(double ang, complex<double> P = {0, 0})
    {
        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] -= P;

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] = {vertex[i].real()*cos(ang) - vertex[i].imag()*sin(ang), vertex[i].imag()*cos(ang) + vertex[i].real()*sin(ang)};

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] += P;
    }

    void RotateCentral(double ang)
    {
        complex<double> C;
        for(int i = 0; i < vertex.size(); ++i)
            C += vertex[i];

        C = (1.0/(double)N) * C;

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] -= C;

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] = {vertex[i].real()*cos(ang) - vertex[i].imag()*sin(ang), vertex[i].imag()*cos(ang) + vertex[i].real()*sin(ang)};

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] += C;
    }

    void MoveTo(complex<double> r)
    {
        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] += r;
    }

    void Reflect(complex<double> ax)
    {
        double betta = GetAngle(ax, {1,0});

        RotateRelPoint(-betta);

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] = {vertex[i].real(), -vertex[i].imag()};

        RotateRelPoint(betta);
    }

    void HomothetyPol(double k, complex<double> h)
    {
        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] = Homothety(vertex[i], k, h);
    }

    void DisplayVert()
    {
        for(int i = 0; i < vertex.size(); ++i)
            cout << vertex[i] << endl;
        cout << endl;
    }

    void Draw()
    {
        for(int i = 0; i < vertex.size() - 1; ++i)
            DrawLine(vertex[i],vertex[i+1]);
        DrawLine(vertex[0], vertex[N-1]);
    }
     */
};
