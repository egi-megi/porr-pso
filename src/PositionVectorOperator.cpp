#include "../include/PositionVectorOperator.h"

#include <vector>

std::vector<double> PositionVectorOperator::add(const std::vector<double> &v_a,
    const std::vector<double> &v_b)
{
    int v_aSize = v_a.size();
    int v_bSize = v_b.size();

    if (v_aSize != v_bSize)
        throw "Vectors should have the same size.";

    std::vector<double> v_c(v_aSize);
    for (int i = 0; i < v_aSize; i++)
        v_c[i] = v_a[i] + v_b[i];

    return v_c;
}

std::vector<double> PositionVectorOperator::minus(const std::vector<double> &v_a,
    const std::vector<double> &v_b)
{
    int v_aSize = v_a.size();
    int v_bSize = v_b.size();

    if (v_aSize != v_bSize)
        throw "Vectors should have the same size.";

    std::vector<double> v_c(v_aSize);
    for (int i = 0; i < v_aSize; i++)
        v_c[i] = v_a[i] - v_b[i];

    return v_c;
}

std::vector<double> PositionVectorOperator::minus(const double &s_a,
    const std::vector<double> &v_a)
{
    int v_aSize = v_a.size();

    std::vector<double> v_b(v_aSize);
    for (int i = 0; i < v_aSize; i++)
        v_b[i] = s_a - v_a[i];

    return v_b;
}

std::vector<double> PositionVectorOperator::mult(const double &s_a,
    const std::vector<double> &v_a)
{
    int v_aSize = v_a.size();

    std::vector<double> v_b(v_aSize);
    for (int i = 0; i < v_aSize; i++)
        v_b[i] = s_a * v_a[i];

    return v_b;
}