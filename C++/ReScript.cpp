// Cpp/ReScript.cpp
// This program takes a ReScript file (.res), compiles it using bsc, and generates a C++ file
// that runs the resulting JavaScript output using Node.js.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.res>\n";
        return 1;
    }

    std::string ResFilePath = argv[1];
    std::ifstream TestInput(ResFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: ReScript file not found - " << ResFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::filesystem::path FilePath = ResFilePath;
    std::string BaseName = FilePath.stem().string();

    std::cout << "Compiling ReScript...\n";
    std::string CompileCommand = "bsc -make-world";
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile ReScript file.\n";
        return 1;
    }

    std::filesystem::path JsPath = FilePath.parent_path() / ("lib/ocaml/" + BaseName + ".js");
    if (!std::filesystem::exists(JsPath))
    {
        std::cerr << "Compiled JS file not found: " << JsPath << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedReScriptWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"node " << JsPath.string() << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute ReScript output.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedReScriptWrapper.cpp\n";

    return 0;
}
