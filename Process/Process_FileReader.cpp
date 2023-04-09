#include "Process_FileReader.hpp"

std::vector<Process*> Process_FileReader::ReadFile(std::string address)
{
    std::string myText;
    std::ifstream myFile(address);

    if(!myFile.is_open())
    {
        throw std::invalid_argument("Could not open file at address " + address);
    }  

    std::vector<Process*> allProcesses;
    int lineCounter = 1;
    while (getline(myFile, myText)) 
    {
        std::vector<std::string> _lineArguments = StringExtensions::Split(myText, DELIMETER);
        Process* p = new Process();

        if(_lineArguments.size() == 2)
        {
            p->SetEnteringTime(std::stof(_lineArguments[0]));
            p->SetDurationTime(std::stof(_lineArguments[1]));
        } 
        else
        {
            myFile.close();
            
            std::string msg = "Input format is invalid at line " 
                               + std::to_string(lineCounter) 
                               + " of file at " + address;
            throw std::invalid_argument(msg);
        }

        allProcesses.push_back(p);
        lineCounter++;
    }

    myFile.close();
    return allProcesses;
}
