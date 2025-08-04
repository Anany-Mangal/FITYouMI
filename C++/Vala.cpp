// Cpp/Vala.cpp
// This program takes a Vala source file, compiles it with valac, and generates a C++ wrapper that runs the compiled output.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.vala>\n";
        return 1;
    }

    std::string ValaFilePath = argv[1];
    std::ifstream TestInput(ValaFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Vala file not found - " << ValaFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::filesystem::path FilePath = ValaFilePath;
    std::string BaseName = FilePath.stem().string();
    std::string ExecutableName = "./" + BaseName;

    std::cout << "Compiling Vala file...\n";
    std::string CompileCommand = "valac " + ValaFilePath;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile Vala file.\n";
        return 1;
    }

    if (!std::filesystem::exists(ExecutableName))
    {
        std::cerr << "Compiled executable not found: " << ExecutableName << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedValaWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"" << ExecutableName << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Vala program.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedValaWrapper.cpp\n";

    return 0;
}
