// Cpp/TypeScript.cpp
// This program takes a TypeScript file, compiles it with tsc, and generates a C++ file that runs the compiled JavaScript using Node.js.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <TypeScriptFile.ts>\n";
        return 1;
    }

    std::string TsFilePath = argv[1];
    std::ifstream TestInput(TsFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: TypeScript file not found - " << TsFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::cout << "Compiling TypeScript...\n";
    std::string CompileCommand = "tsc " + TsFilePath;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile TypeScript file.\n";
        return 1;
    }

    std::filesystem::path JsPath = std::filesystem::path(TsFilePath).replace_extension(".js");
    if (!std::filesystem::exists(JsPath))
    {
        std::cerr << "Compiled JS file not found: " << JsPath << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedTsWrapper.cpp");
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
    Out << "        std::cerr << \"Failed to execute TypeScript output.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedTsWrapper.cpp\n";

    return 0;
}
