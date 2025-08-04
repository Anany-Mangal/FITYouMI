// Cpp/Nim.cpp
// This program takes a Nim file, compiles it using the Nim compiler,
// and generates a C++ wrapper that runs the compiled Nim binary.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Source.nim>\n";
        return 1;
    }

    std::string NimFilePath = argv[1];
    std::ifstream TestInput(NimFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Nim file not found - " << NimFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::filesystem::path FilePath = NimFilePath;
    std::string FileStem = FilePath.stem().string();
    std::string CompileCommand = "nim c " + NimFilePath;

    std::cout << "Compiling Nim file...\n";
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile Nim file.\n";
        return 1;
    }

    std::filesystem::path BinaryPath = FileStem;
#ifdef _WIN32
    BinaryPath += ".exe";
#endif

    if (!std::filesystem::exists(BinaryPath))
    {
        std::cerr << "Compiled Nim binary not found: " << BinaryPath << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedNimWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"" << BinaryPath.string() << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Nim binary.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedNimWrapper.cpp\n";

    return 0;
}
