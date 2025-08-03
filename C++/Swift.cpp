// Cpp/Swift.cpp
// Compiles a Swift file and generates a C++ wrapper that executes it.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <SwiftFile.swift>\n";
        return 1;
    }

    std::string SwiftFilePath = argv[1];
    std::ifstream TestInput(SwiftFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Swift file not found - " << SwiftFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::string BinaryOutput = "SwiftBinary.out";
    std::cout << "Compiling Swift file...\n";

    std::string CompileCommand = "swiftc " + SwiftFilePath + " -o " + BinaryOutput;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile Swift file.\n";
        return 1;
    }

    if (!std::filesystem::exists(BinaryOutput))
    {
        std::cerr << "Error: Compiled binary not found - " << BinaryOutput << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedSwiftWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"./" << BinaryOutput << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Swift binary.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedSwiftWrapper.cpp\n";

    return 0;
}
