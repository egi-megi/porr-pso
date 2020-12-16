#include "../include/Options.h"

Options::Options()
{
    optimizationExerciseConfig = nullptr;
    stopCriterionConfig = nullptr;
    stopCriterionThreshold  = 1.1;
    amountOfParticles = 10;
    dimension = 2;

    verbose = true;
    timing = true;
    filenameEqualsParameters = false;
    fileReadyToReadFrom = false;

    communication = CommunicationType::GLOBAL_BEST;
}

void Options::prepareAndActivateWriteLogger() 
{
    isSaveStartPosition = true;
    openOutputFile();
}

void Options::prepareAndActivateReadLogger()
{
    if (particlesStartPositionsFileName.empty())
    {
        createFileNameFromParameters();
        checkFileName();
    }
    if (filenameEqualsParameters)
    {
        isSaveStartPosition = false;
        openInputFile();
        loadStartPositionFromFile();
    }
}

void Options::loadStartPositionFromFile()
{
    if (fileReadyToReadFrom)
    {
        std::vector<std::vector<double> > temp_swarm;
        temp_swarm.resize(amountOfParticles);
        std::vector<double> temp_particle;
        temp_particle.resize(dimension);
        int outside_iter = 0;
        
        for (std::string line; std::getline(*inputFile, line);)
        {
            std::stringstream lineStream;
            std::string segment;
            std::vector<std::string> seglist;
            int iter = 0; 
            lineStream << line;

            while (std::getline(lineStream, segment, ','))
            {
                temp_particle[iter] = std::stod(segment);
                //std::cout<<temp_particle[iter]<<' ';
                iter++;
            }
            //std::cout<<'\n';
            temp_swarm[outside_iter]=temp_particle;
            outside_iter++;
        }
        particlesFromFile = temp_swarm;
    }
}

void Options::addStartPositionToBuffer(std::vector<double> positionsVector, const int& id) 
{
    std::stringstream localBuffer;
    for(const auto position : positionsVector)
    {
    localBuffer << position <<',';
    }

    particlePositionStream << localBuffer.str()<<'\n';
    
}

void Options::createFileNameFromParameters() 
{
    std::stringstream buffer;
    buffer << "startPos_" << amountOfParticles <<'_'<<dimension<<".txt";
    particlesStartPositionsFileName  = buffer.str();
}

void Options::checkFileName()
{
    if (!particlesStartPositionsFileName.empty())
    {
        bool checkStatus = false;
        std::stringstream filename;
        std::string segment;
        std::vector<std::string> seglist;
       
        filename << particlesStartPositionsFileName;

        while (std::getline(filename, segment, '_'))
        {
            seglist.push_back(segment);
        }

        int particlesNumber = std::stoi(seglist[1]);
        int dim = std::stoi(seglist[2]);

        checkStatus = (particlesNumber == amountOfParticles);
        checkStatus = (dim == dimension);        
        filenameEqualsParameters = checkStatus;
    }
}

void Options::openOutputFile() 
{
    if(isSaveStartPosition)
    {
    createFileNameFromParameters();

      outputFile = new std::ofstream(); 
      outputFile->open(particlesStartPositionsFileName, std::ios::out | std::ios::trunc);
      if(outputFile->is_open())
      {
          std::cout<<"File for writing particles start position log opened.\n";
      }
      else
      {
           std::cout<<"Unable to open to write: "<<particlesStartPositionsFileName<<" particles start position file.\n";
      }      
    }
}

void Options::openInputFile() 
{
    if(filenameEqualsParameters && isSaveStartPosition == false)
    {
      inputFile = new std::ifstream(); 
      inputFile->open(particlesStartPositionsFileName, std::ios::in);
      
      if(inputFile->is_open())
      {
          fileReadyToReadFrom = true;
          std::cout<<"File for reading particles start position log opened.\n";
      }
      else
      {
           std::cout<<"Unable to open to read: "<<particlesStartPositionsFileName<<" particles start position file.\n";
      } 
    }
}

void Options::readBufferAndCloseFile() 
{
    *outputFile<<particlePositionStream.rdbuf();
    particlePositionStream.str("");
    outputFile->close();
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