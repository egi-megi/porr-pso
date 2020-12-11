#include <vector>
#include <map>

using namespace std;

class Logger
{
    struct ParamStruct
    {
        int amountOfParticles;
        int vectorDim; 
        float stopCriterion;
        float weight;
        float speedConst1;
        float speedConst2;
        int ompChunkSize;

        ParamStruct(const int& amount, const int& dim, const float& stop, 
                    const float& w, const float& s1, const float& s2, const int& chunk):
                    amountOfParticles(amount), vectorDim(dim),stopCriterion(stop),
                    weight(w), speedConst1(s1), speedConst2(s2),ompChunkSize(chunk)
                    {};

        
    };
    
    void paramsToFile();        
    

    Logger();
    ~Logger();
};