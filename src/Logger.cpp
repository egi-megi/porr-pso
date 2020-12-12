#include "../include/Logger.h"

Logger::Logger(const std::string& outputFilename) :  outFile(outputFilename, std::ios::out | std::ios::trunc)
{
   if (outFile.is_open())
   {
      std::cout << "File for datalog opened.\n";
      stream << "$INFO$\n";
      stream << "This is file for data log. \n";
      stream << "$DATE$\n";
      date = currentDateTime();
      stream << "File created: " << currentDateTime() << '\n';    
   }
   else
      std::cout << "Unable to open file for datalog.\n";
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
   obj->logAndClose();
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
}

void Logger::paramsToFile()
{
}