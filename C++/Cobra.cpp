// Cpp/Cobra.cpp
// This program takes a Cobra source file, compiles it, and generates a C++ wrapper that runs the Cobra output.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.cobra>\n";
        return 1;
    }

    std::string CobraFilePath = argv[1];
    std::ifstream TestInput(CobraFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Cobra file not found - " << CobraFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::filesystem::path FilePath = CobraFilePath;
    std::string BaseName = FilePath.stem().string();
    std::string OutName = BaseName + ".exe";

    std::cout << "Compiling Cobra file...\n";
    std::string CompileCommand = "cobra -compile -target:exe " + CobraFilePath;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile Cobra file.\n";
        return 1;
    }

    if (!std::filesystem::exists(OutName))
    {
        std::cerr << "Compiled executable not found: " << OutName << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedCobraWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"" << OutName << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Cobra program.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedCobraWrapper.cpp\n";

    return 0;
}
