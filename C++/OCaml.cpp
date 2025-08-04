// Cpp/OCaml.cpp
// Compiles an OCaml file using ocamlc and creates a C++ wrapper to run it.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Source.ml>\n";
        return 1;
    }

    std::string OcamlFilePath = argv[1];
    std::ifstream TestInput(OcamlFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: OCaml source file not found - " << OcamlFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::filesystem::path ExecutablePath = std::filesystem::path(OcamlFilePath).replace_extension(".out");
    std::string CompileCommand = "ocamlc -o " + ExecutablePath.string() + " " + OcamlFilePath;

    std::cout << "Compiling OCaml source...\n";
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Compilation failed.\n";
        return 1;
    }

    std::ofstream Out("GeneratedOcamlWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"" << ExecutablePath.string() << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute OCaml binary.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedOcamlWrapper.cpp\n";

    return 0;
}
