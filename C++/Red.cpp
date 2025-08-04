// Cpp/Red.cpp
// This program takes a Red script and generates a C++ file that runs it via the Red CLI.

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.red>\n";
        return 1;
    }

    std::string RedFilePath = argv[1];
    if (!std::filesystem::exists(RedFilePath))
    {
        std::cerr << "Error: Red file not found - " << RedFilePath << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedRedWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"red " << RedFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Ou
