// Cpp/Go.cpp
// This program takes a Go file, compiles it using `go build`, and generates a C++ file that runs the Go executable.
// Assumes Go is installed and `go` is available in PATH.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <GoFile.go>\n";
        return 1;
    }

    std::string GoFilePath = argv[1];
    std::ifstream TestInput(GoFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Go file not found - " << GoFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::string OutputExe = "GeneratedGoProgram.exe";
    std::string CompileCommand = "go build -o " + OutputExe + " " + GoFilePath;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Error: Failed to compile Go file.\n";
        return 1;
    }

    std::ofstream Out("GeneratedGoWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"GeneratedGoProgram.exe\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Go program.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedGoWrapper.cpp\n";

    return 0;
}
