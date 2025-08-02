// Cpp/Ruby.cpp
// This program takes a Ruby file and generates a C++ file that runs the Ruby file using the system Ruby interpreter.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <RubyFile.rb>\n";
        return 1;
    }

    std::string RubyFilePath = argv[1];
    std::ifstream TestInput(RubyFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Ruby file not found - " << RubyFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedRubyWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"ruby " << RubyFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Ruby script.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedRubyWrapper.cpp\n";

    return 0;
}
