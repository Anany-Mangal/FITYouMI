// Cpp/Janet.cpp
// This program takes a Janet file (.janet) and generates a C++ file that executes it via the Janet interpreter.

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.janet>\n";
        return 1;
    }

    std::string JanetFilePath = argv[1];
    if (!std::filesystem::exists(JanetFilePath))
    {
        std::cerr << "Error: Janet file not found - " << JanetFilePath << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedJanetWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"janet " << JanetFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Janet script.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedJanetWrapper.cpp\n";

    return 0;
}
