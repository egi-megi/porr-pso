#include "../include/Options.h"

Options::Options()
{
    optimizationExerciseConfig = nullptr;
    stopCriterionConfig = nullptr;
    stopCriterionThreshold  = 0.001;
    amountOfParticles = 10;
    dimension = 2;

    verbose = true;
    timing = true;

    communication = CommunicationType::GLOBAL_BEST;
}

std::string Options::optionsToString(const bool& useDate) 
{
    std::stringstream buffer;
    buffer << amountOfParticles <<'_'<< dimension <<'_'<<stopCriterionThreshold;
    if(useDate)
    {
    buffer<<'_'<<currentDateTime();
    }
    return buffer.str();  
}

std::string Options::currentDateTime()
{
   time_t now = time(0);
   struct tm tstruct;
   char buf[80];
   tstruct = *localtime(&now);

   strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);
   return buf;
}