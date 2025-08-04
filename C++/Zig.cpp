// Cpp/Zig.cpp
// This program takes a Zig file and generates a C++ file that compiles and runs it using Zig.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.zig>\n";
        return 1;
    }

    std::string ZigFilePath = argv[1];
    std::ifstream TestInput(ZigFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Zig file not found - " << ZigFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::string OutputBinary = "ZigOutputExecutable";
    std::string CompileCommand = "zig build-exe " + ZigFilePath + " -femit-bin=" + OutputBinary;

    std::cout << "Compiling Zig file...\n";
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile Zig file.\n";
        return 1;
    }

    std::ofstream Out("GeneratedZigWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"./" << OutputBinary << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to run Zig executable.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedZigWrapper.cpp\n";

    return 0;
}
