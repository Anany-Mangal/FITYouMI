// Cpp/Lisp.cpp
// Generates a C++ wrapper to execute a Lisp script using SBCL.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.lisp>\n";
        return 1;
    }

    std::string LispFilePath = argv[1];
    std::ifstream TestInput(LispFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Lisp script not found - " << LispFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedLispWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"sbcl --script " << LispFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Lisp script execution failed.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedLispWrapper.cpp\n";

    return 0;
}
