#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../StringExtensions/StringExtensions.hpp"
#include "Process.hpp"

namespace Process_FileReader
{
    // Constants used in text file
    const std::string DELIMETER = " ";

    std::vector<Process*> ReadFile(std::string address);
}