// Cpp/COBOL.cpp
// This program takes a COBOL file, compiles it with GnuCOBOL, and generates a C++ file to execute the binary.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <File.cob>\n";
        return 1;
    }

    std::string CobolFilePath = argv[1];
    std::ifstream TestInput(CobolFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: COBOL file not found - " << CobolFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::string BinaryName = "cobol_program.out";
    std::string CompileCommand = "cobc -x -o " + BinaryName + " " + CobolFilePath;

    std::cout << "Compiling COBOL file...\n";
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile COBOL file.\n";
        return 1;
    }

    std::ofstream Out("GeneratedCobolWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"./" << BinaryName << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute COBOL binary.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedCobolWrapper.cpp\n";

    return 0;
}
