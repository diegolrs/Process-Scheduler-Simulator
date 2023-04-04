#include "Process_FileReader.hpp"
#include <iostream>

std::vector<Process*> Process_FileReader::ReadFile(std::string address)
{
    std::string myText;
    std::ifstream myFile(address);

    if(!myFile.is_open())
    {
        throw std::invalid_argument("Could not open file at address " + address);
    }  

    std::vector<Process*> allProcesses;
    while (getline(myFile, myText)) 
    {
        std::vector<std::string> _lineArguments = StringExtensions::Split(myText, DELIMETER);
        Process* p = new Process();

        if(_lineArguments.size() == 2)
        {
            p->SetEnteringTime(std::stof(_lineArguments[0]));
            p->SetDurationTime(std::stof(_lineArguments[1]));
            //std::cout << "LIDO: " <<_lineArguments[0] << " " << _lineArguments[1]<< std::endl;
            //std::cout << _lineArguments[1] << " " << std::stof(_lineArguments[1]) << std::endl;

            std::cout << p->GetDurationTime() << std::endl;
        } 
        else
        {
            myFile.close();
            throw std::invalid_argument("AddPositiveIntegers arguments must be positive");
        }

        allProcesses.push_back(p);
    }

    myFile.close();
    return allProcesses;
}
