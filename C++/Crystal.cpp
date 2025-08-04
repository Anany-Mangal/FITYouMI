// Cpp/Crystal.cpp
// This program takes a Crystal file, compiles it using the Crystal compiler,
// and generates a C++ wrapper that executes the resulting binary.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Source.cr>\n";
        return 1;
    }

    std::string CrystalFilePath = argv[1];
    std::ifstream TestInput(CrystalFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Crystal file not found - " << CrystalFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::filesystem::path FilePath = CrystalFilePath;
    std::string FileStem = FilePath.stem().string();
    std::string BinaryName = FileStem;
#ifdef _WIN32
    BinaryName += ".exe";
#endif

    std::string CompileCommand = "crystal build " + CrystalFilePath + " -o " + BinaryName;
    std::cout << "Compiling Crystal file...\n";
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile Crystal file.\n";
        return 1;
    }

    if (!std::filesystem::exists(BinaryName))
    {
        std::cerr << "Compiled Crystal binary not found: " << BinaryName << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedCrystalWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"" << BinaryName << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Crystal binary.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedCrystalWrapper.cpp\n";

    return 0;
}
