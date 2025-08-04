// Cpp/Raku.cpp
// This program takes a Raku file and generates a C++ file that runs it using the Raku interpreter.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.raku>\n";
        return 1;
    }

    std::string RakuFilePath = argv[1];
    std::ifstream TestInput(RakuFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Raku file not found - " << RakuFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedRakuWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"raku " << RakuFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Raku script.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedRakuWrapper.cpp\n";

    return 0;
}
