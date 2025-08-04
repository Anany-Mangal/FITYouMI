// Cpp/Reason.cpp
// This program takes a ReasonML file (.re), compiles it using bsb, and generates a C++ file to run the resulting JavaScript.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.re>\n";
        return 1;
    }

    std::string ReasonFilePath = argv[1];
    if (!std::filesystem::exists(ReasonFilePath))
    {
        std::cerr << "Error: ReasonML file not found - " << ReasonFilePath << "\n";
        return 1;
    }

    std::string Dir = std::filesystem::path(ReasonFilePath).parent_path().string();
    std::string FileName = std::filesystem::path(ReasonFilePath).stem().string();

    std::cout << "Compiling ReasonML file using bsb...\n";
    if (std::system(("cd " + Dir + " && bsb -make-world").c_str()) != 0)
    {
        std::cerr << "Failed to compile ReasonML file.\n";
        return 1;
    }

    std::filesystem::path JsOutputPath = Dir + "/lib/js/src/" + FileName + ".js";
    if (!std::filesystem::exists(JsOutputPath))
    {
        std::cerr << "Compiled JS output not found: " << JsOutputPath << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedReasonWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"node " << JsOutputPath.string() << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute ReasonML output.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedReasonWrapper.cpp\n";

    return 0;
}
