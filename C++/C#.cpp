// Cpp/C#.cpp
// This program takes a C# file, compiles it using `csc`, and generates a C++ file that runs the C# executable.
// Assumes `csc` (C# compiler) is installed and available in PATH.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <CSharpFile.cs>\n";
        return 1;
    }

    std::string CSharpFilePath = argv[1];
    std::ifstream TestInput(CSharpFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: C# file not found - " << CSharpFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::string OutputExe = "GeneratedCSharpProgram.exe";
    std::string CompileCommand = "csc -out:" + OutputExe + " " + CSharpFilePath;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Error: Failed to compile C# file.\n";
        return 1;
    }

    std::ofstream Out("GeneratedCSharpWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"GeneratedCSharpProgram.exe\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute C# program.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedCSharpWrapper.cpp\n";

    return 0;
}
