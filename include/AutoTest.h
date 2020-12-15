#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_AUTOTEST_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_AUTOTEST_H

#include <vector>
#include <string>

typedef std::vector<std::string> Parameters;

enum class TEST
{
    S1AP = 0,
    S1NP, //1
    MC1AP,
    MC1NP,
    S2AP,
    S2NP,
    MC2AP,
    MC2NP,
    S1AS,
    S1NS,
    MC1AS,
    MC1NS,
    S2AS,
    S2NS,
    MC2AS,
    MC2NS //15
};

struct Combination
{
    const std::vector<std::string> taskTypes = {"s1aP", "s1nP", "mc1aP", "mc1nP", "s2aP", "s2nP", "mc2aP", "mc2nP",
                                                "s1aS", "s1nS", "mc1aS", "mc1nS", "s2aS", "s2nS", "mc2aS", "mc2nS"};

    std::string algorithm;
    std::string task;
    std::string stopCondition;
    std::string cpuBehaviour;

    Combination() = default;
    Combination(Parameters params);
    Combination(TEST testId);

    void updateConfiguration(const Parameters& params);
};

#endif // ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_AUTOTEST_H