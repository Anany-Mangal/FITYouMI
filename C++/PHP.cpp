// Cpp/PHP.cpp
// This program takes a PHP file and generates a C++ file that runs the PHP file using the system PHP interpreter.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <PHPFile.php>\n";
        return 1;
    }

    std::string PhpFilePath = argv[1];
    std::ifstream TestInput(PhpFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: PHP file not found - " << PhpFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedPhpWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"php " << PhpFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute PHP script.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedPhpWrapper.cpp\n";

    return 0;
}
