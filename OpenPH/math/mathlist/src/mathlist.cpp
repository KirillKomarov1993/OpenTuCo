#include "mathlist.h"

namespace ph {
    double kronecker(int i, int j)
    {
        if (i == j)
        {
            return 1;
        }
        else
        {
            return 0.0;
        }
    }
    double pi()
    {
        return 3.1415926535;
    }
    cDoubles i()
    {
        cDoubles im(0, 1);
        return im;
    }
    double getExteriorProduct(Vector3d v1, Vector3d v2)
    {
        return fabs(v1[0] * v2[1] - v1[1] * v2[0]);
    }
    Vector3d cross2D(Vector3d v)
    {
        return Vector3d(-v[1], v[0], 0.0);
    }
    Matrix3d getKronProduct(Vector3d v1, Vector3d v2)
    {
        long size_ = v2.size();
        Matrix3d B(v1.size(), v2.size());
        for (int i = 0; i < v1.size(); i++)
        {
            for (int j = 0; j < size_; j++)
            {
                B(i, j) = v1(i) * v2(j);
            }
        }
        return B;
    }
    Matrix3d getRotationMatrix3D(double _phi, double _theta)
    {
        Matrix3d B(3,3);
        B << cos(_phi),   -sin(_phi),           0.0,
             sin(_phi),    cos(_phi),           0.0,
                   0.0,          0.0,   cos(_theta);
        return B;
    }
    Matrix3d getRotationMatrix3D(std::string axis, double _alpha)
    {
        Matrix3d B(3,3);
        if (axis == "x") {
            B <<         1.0,            0.0, 0.0,
                 cos(_alpha),   -sin(_alpha), 0.0,
                 sin(_alpha),    cos(_alpha), 0.0;
        }
        if (axis == "y") {
            B <<  cos(_alpha), 0.0, sin(_alpha),
                         0.0,  1.0,         0.0,
                 -sin(_alpha), 0.0, cos(_alpha);
        }
        if (axis == "z") {
            B << cos(_alpha),   -sin(_alpha),           0.0,
                 sin(_alpha),    cos(_alpha),           0.0,
                       0.0,          0.0,           1.0;
        }
        return B;
    }
    std::vector<std::complex<double>> applyFFT(std::vector<std::complex<double>> data)
    {
        fftw_plan plan = fftw_plan_dft_1d(data.size(), (fftw_complex*)&data[0], (fftw_complex*)&data[0], FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(plan);
        fftw_destroy_plan(plan);
        return data;
    }
}
/*
Vector getOrtogonalVector(double x, double y)
{
    Vector e_n(2);
    Vector e_k(2); e_k << x, y;
    double norm = std::hypot(x, y);
    if (norm != 0.0)
    {
        e_k = e_k / norm;
    }
    e_n <<-e_k(1), e_k(0);
    return e_n;
}
Vector getUnitVector(Vector& vec)
{
    double norm = vec.norm();
    if (norm != 0.0)
    {
        return vec / norm;
    }
    else
    {
        return vec;
    }
}
Vector cross2D(Vector& vec_0)
{
    Vector vec(2);
    vec(0) = -vec_0(1);
    vec(1) = vec_0(0);
    return vec;
}
Vector cross3D(Vector& a, Vector& b)
{
    Vector vec(3);
    vec(0) = a(2)*b(1) - a(1)*b(2);
    vec(1) = a(0)*b(2) - a(2)*b(0);
    vec(2) = a(1)*b(0) - a(0)*b(1);
    return vec;
}
Matrix getKronProduct(Vector& v1, Vector& v2)
{
    long size_ = v2.size();
    Matrix B(v1.size(), v2.size());
    for (int i = 0; i < v1.size(); i++)
    {
        for (int j = 0; j < size_; j++)
        {
            B(i, j) = v1(i) * v2(j);
        }
    }
    return B;
}
Matrix getRotationMatrix(double _phi)
{
    Matrix A(2,2);
    A << cos(_phi), -sin(_phi),
         sin(_phi), cos(_phi);
    return A;
}
Matrix getRotationMatrix(double _phi, double _theta)
{
    Matrix B(3,3);
    B << cos(_phi),   -sin(_phi),           0.0,
         sin(_phi),    cos(_phi),           0.0,
               0.0,          0.0,   cos(_theta);
    return B;
}
Matrix getInvertibleMatrix(Matrix& A)
{
    Matrix B(2,2);
    B << A(1,1), -A(0,1),
        -A(1,0), A(0,0);
    return B/(A(0,0)*A(1,1) - A(0,1)*A(1,0));
}
Vector getInvertibleVector(Vector& vec)
{
    Vector vec_2(vec.size());
    for (int i = 0; i < vec.size(); i++)
    {
        vec_2(i) = 1.0/vec(i);
    }
    return vec_2;
}
double approx(double x, double y, double e)
{
    if (abs((x - y)) < e) {
        return 0.0;
    }
    else {
        return 1.0;
    }
}
*/
