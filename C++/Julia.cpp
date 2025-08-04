// Cpp/Julia.cpp
// Generates a C++ wrapper to run a Julia script using the Julia runtime.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.jl>\n";
        return 1;
    }

    std::string JuliaFilePath = argv[1];
    std::ifstream TestInput(JuliaFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Julia script not found - " << JuliaFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedJuliaWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"julia " << JuliaFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Julia script execution failed.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedJuliaWrapper.cpp\n";

    return 0;
}
