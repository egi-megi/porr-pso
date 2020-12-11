#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_POSITIONVECTOROPERATOR_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_POSITIONVECTOROPERATOR_H

#include <vector>

class PositionVectorOperator
{
public:
    static std::vector<double> add(const std::vector<double> &v_a, const std::vector<double> &v_b);
    static std::vector<double> minus(const std::vector<double> &v_a, const std::vector<double> &v_b);
    static std::vector<double> minus(const double &s_a, const std::vector<double> &v_a);
    static std::vector<double> mult(const double &s_a, const std::vector<double> &v_a);
};

#endif