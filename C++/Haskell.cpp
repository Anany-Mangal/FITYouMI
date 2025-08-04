// Cpp/Haskell.cpp
// Compiles a Haskell file using GHC and generates a C++ wrapper to execute the binary.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.hs>\n";
        return 1;
    }

    std::string HsFilePath = argv[1];
    std::ifstream TestInput(HsFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Haskell file not found - " << HsFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::filesystem::path HsPath(HsFilePath);
    std::string OutputBinary = HsPath.stem().string();

    std::cout << "Compiling Haskell file with GHC...\n";
    std::string CompileCommand = "ghc -o " + OutputBinary + " " + HsFilePath;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Haskell compilation failed.\n";
        return 1;
    }

    std::ofstream Out("GeneratedHaskellWrapper.cpp");
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
    Out << "        std::cerr << \"Haskell binary execution failed.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedHaskellWrapper.cpp\n";

    return 0;
}
