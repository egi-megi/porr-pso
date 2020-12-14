#include "../include/Logger.h"

Logger::Logger(Options* options, const std::string &_mainLogPath, const std::string &_particlesLogPath, const bool &isLogAll, const bool &isActive) : options(options), mainLogPath(_mainLogPath), particlesLogPath(_particlesLogPath), isLogAllData(isLogAll), isLoggerActive(isActive)
{
   isLogOnlyBest = false;
   outFile = nullptr;
   outParticlesFile = nullptr;

   if (!mainLogPath.empty())
   {
      isLoggerActive = true;
      outFile = new std::ofstream(); 
      outFile->open(mainLogPath, std::ios::out | std::ios::trunc);
      if (outFile->is_open())
      {
         std::cout << "File for datalog opened.\n";
      }
      else
      {
         std::cout << "Unable to open: " << mainLogPath << " file\n";
      }
   }
   if (!particlesLogPath.empty() && options->dimension == 2 && isLogAll)
   {
      isLogAllData = true;
      outParticlesFile = new std::ofstream(); 
      outParticlesFile->open(particlesLogPath, std::ios::out | std::ios::trunc);
      if (outParticlesFile->is_open())
      {
         std::cout << "File for all particles log opened.\n";
      }
      else
      {
         std::cout << "Unable to open: " << particlesLogPath << " file\n";
      }
   }
   else if (!particlesLogPath.empty() && options->dimension != 2)
   {
      isLogOnlyBest = true;
      outParticlesFile = new std::ofstream(particlesLogPath, std::ios::out | std::ios::trunc);
      if (outParticlesFile->is_open())
      {
         std::cout << "File for only best particles opened.\n";
      }
      else
      {
         std::cout << "Unable to open: " << particlesLogPath << " file\n";
      }
   }
}

Logger::~Logger()
{

}

std::string Logger::currentDateTime()
{
   time_t now = time(0);
   struct tm tstruct;
   char buf[80];
   tstruct = *localtime(&now);

   strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);
   return buf;
}

void Logger::saveToFileAndClose()
{
   *outFile << stream.rdbuf();
   outFile->close();
   
   *outParticlesFile << pStream.rdbuf();
   outParticlesFile->close();   
}

void Logger::sendToParticlesStream(const int &iter, const float &cost, const float &pos1, const float &pos2, const float &speed1, const float &speed2)
{
   char d = ',';
   pStream << iter << d << cost << d << pos1 << d << pos2 << d << speed1 << d << speed2 << '\n';
}

void Logger::sendAllParticlesStream(const int& iter, const int& id, const float& pos1, const float& pos2, const float& speed1, const float& speed2, const float& cost)
{
  char d = ',';
  pStream << iter << d << id << d << pos1 << d << pos2 << d << speed1 << d << speed2 << d << cost << '\n';
}

void Logger::saveParticleStreamBuffer() 
{
    *outParticlesFile << pStream.rdbuf();    
    pStream.str(""); // clears stream buffer
}

void Logger::setActivityOfLogger(const bool& _isActive) 
{
   isLoggerActive = _isActive;
}

