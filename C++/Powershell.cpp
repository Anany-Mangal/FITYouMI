// Cpp/Powershell.cpp
// Generates a C++ wrapper that runs a PowerShell script (.ps1)

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.ps1>\n";
        return 1;
    }

    std::string PsFilePath = argv[1];
    std::ifstream TestInput(PsFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: PowerShell script not found - " << PsFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedPowershellWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    // NOTE: Use powershell.exe on Windows or pwsh for cross-platform PowerShell Core
    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"powershell -ExecutionPolicy Bypass -File " << PsFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute PowerShell script.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedPowershellWrapper.cpp\n";

    return 0;
}
