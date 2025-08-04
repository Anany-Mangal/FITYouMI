// Cpp/Dart.cpp
// Generates a C++ wrapper to execute a Dart script using the Dart runtime.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.dart>\n";
        return 1;
    }

    std::string DartFilePath = argv[1];
    std::ifstream TestInput(DartFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Dart script not found - " << DartFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedDartWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"dart " << DartFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Dart script execution failed.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedDartWrapper.cpp\n";

    return 0;
}
  D
