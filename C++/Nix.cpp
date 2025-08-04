// Cpp/Nix.cpp
// This program takes a Nix expression file and generates a C++ wrapper that runs the evaluation.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.nix>\n";
        return 1;
    }

    std::string NixFilePath = argv[1];
    std::ifstream TestInput(NixFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Nix file not found - " << NixFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::cout << "Testing Nix evaluation...\n";
    std::string EvalCommand = "nix-instantiate " + NixFilePath + " --eval";
    if (std::system(EvalCommand.c_str()) != 0)
    {
        std::cerr << "Failed to evaluate Nix file.\n";
        return 1;
    }

    std::ofstream Out("GeneratedNixWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"nix-instantiate " << NixFilePath << " --eval\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Nix expression failed.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedNixWrapper.cpp\n";

    return 0;
}
