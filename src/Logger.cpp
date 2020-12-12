#include "../include/Logger.h"

Logger::Logger(const std::string &outputFilename, 
               const std::string &particlesFile, 
               const int &dim,
               const bool& isLogAll) : outFile(outputFilename, std::ios::out | std::ios::trunc),
                                 outParticlesFile(particlesFile, std::ios::out | std::ios::trunc),
                                 isLogAllParticles(isLogAll)
{

   
   if (outFile.is_open())
   {
      std::cout << "File for datalog opened.\n";
      stream << "$INFO$\n";
      stream << "This is file for data log. \n";
      stream << "$DATE$\n";
      date = currentDateTime();
      stream << currentDateTime() << '\n';
   }
   else
      std::cout << "Unable to open file for datalog.\n";

   if (dim == 2)
   {
      isParticlesLog = true;

      if (outParticlesFile.is_open())
      {
         std::cout << "File for particles log opened(n = 2).\n";
         if(!isLogAllParticles)
         {
         pStream << "Iter,Cost,PositionN1,PositionN2,SpeedVec1,SpeedVec\n";
         }
      }
      else
         std::cout << "Unable to open file for particlesLog.\n";
   }
   else
   {
      isParticlesLog = false;
      outParticlesFile.close();
   }
}

Logger::~Logger()
{

}

Logger::ParamStruct::ParamStruct(const int &amount, const int &dim, const float &stop,
                                 const float &w, const float &s1, const float &s2, const int &chunk, Logger* obj) : amountOfParticles(amount), vectorDim(dim), stopCriterion(stop),
                                                                                                       weight(w), speedConst1(s1), speedConst2(s2), ompChunkSize(chunk)

{
   char d = ',';
   char n = '\n';
   obj->stream << "$PARAMS$\n";
   obj->stream << "AmountOfParticles"<<d<<amount<<n;
   obj->stream <<"DimensionsOfVector"<<d<<dim<<n;
   obj->stream <<"StopCriterion"<<d<<stop<<n;
   obj->stream <<"Weight"<<d<<w<<n;
   obj->stream <<"SpeedConstant1"<<d<<s1<<n;
   obj->stream <<"SpeedConstant2"<<d<<s2<<n;
   obj->stream <<"OmpSizeOfChunk"<<d<<chunk<<n;     
}

std::string Logger::currentDateTime()
{
   time_t now = time(0);
   struct tm tstruct;
   char buf[80];
   tstruct = *localtime(&now);

   strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &tstruct);
   return buf;
}

void Logger::logAndClose()
{
   outFile << stream.rdbuf();
   outFile.close();

   outParticlesFile << pStream.rdbuf();
   outParticlesFile.close();
}

void Logger::setLogAll(const bool& val) 
{
    isLogAllParticles = val;
}

void Logger::sendToParticlesStream(const int &iter, const float &cost, const float &pos1, const float &pos2, const float &speed1, const float &speed2)
{
   char d = ',';
   pStream << iter << d << cost << d << pos1 << d << pos2 << d << speed1 << d << speed2 << '\n';
}

void Logger::sendAllParticlesStream(const int& iter, const int& id, const float& pos1, const float& pos2, const float& speed1, const float& speed2)
{
  char d = ',';
  pStream << iter << d << id << d << pos1 << d << pos2 << d << speed1 << d << speed2 << '\n';
}

void Logger::saveParticleStreamBuffer() 
{
    outParticlesFile << pStream.rdbuf();    
    pStream.str("");
}



