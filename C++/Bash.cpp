// Cpp/Bash.cpp
// This program takes a Bash script file and generates a C++ file that runs it.

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

    std::string BashScriptPath = argv[1];
    std::ifstream TestInput(BashScriptPath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Bash script not found - " << BashScriptPath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedBashWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"bash " << BashScriptPath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Bash script.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedBashWrapper.cpp\n";

    return 0;
}
