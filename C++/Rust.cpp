// Cpp/Rust.cpp
// This program takes a Rust source file and generates a C++ file that compiles and runs the Rust binary.
// It assumes Rust is installed and available via `rustc` in the system's PATH.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <RustFile.rs>\n";
        return 1;
    }

    std::string RustFilePath = argv[1];
    std::ifstream TestInput(RustFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Rust file not found - " << RustFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::string OutputName = "GeneratedRustProgram";
    std::string CompileCommand = "rustc " + RustFilePath + " -o " + OutputName;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Error: Failed to compile Rust file.\n";
        return 1;
    }

    std::ofstream Out("GeneratedRustWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"./" << OutputName << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Rust program.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedRustWrapper.cpp\n";

    return 0;
}
