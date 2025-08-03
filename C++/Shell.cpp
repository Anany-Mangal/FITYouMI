// Cpp/Shell.cpp
// Generates a C++ file that runs a shell script.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.sh>\n";
        return 1;
    }

    std::string ShellFilePath = argv[1];
    std::ifstream TestInput(ShellFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Shell script not found - " << ShellFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedShellWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"bash " << ShellFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Shell script failed to run.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedShellWrapper.cpp\n";

    return 0;
}
