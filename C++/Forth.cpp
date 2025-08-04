// Cpp/Forth.cpp
// This program takes a Forth file and generates a C++ file that runs it using Gforth.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.fs>\n";
        return 1;
    }

    std::string ForthFilePath = argv[1];
    std::ifstream TestInput(ForthFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Forth file not found - " << ForthFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedForthWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"gforth " << ForthFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Forth script.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedForthWrapper.cpp\n";

    return 0;
}
