// Cpp/Perl.cpp
// Generates a C++ wrapper that executes a Perl script.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.pl>\n";
        return 1;
    }

    std::string PerlFilePath = argv[1];
    std::ifstream TestInput(PerlFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Perl script not found - " << PerlFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedPerlWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"perl " << PerlFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Perl script failed to run.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedPerlWrapper.cpp\n";

    return 0;
}
