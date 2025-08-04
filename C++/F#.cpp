// Cpp/FSharp.cpp
// Generates a C++ wrapper to execute an F# script using dotnet fsi.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.fsx>\n";
        return 1;
    }

    std::string FsharpFilePath = argv[1];
    std::ifstream TestInput(FsharpFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: F# script not found - " << FsharpFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedFsharpWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"dotnet fsi " << FsharpFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"F# script execution failed.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedFsharpWrapper.cpp\n";

    return 0;
}
