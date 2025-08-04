// Cpp/Scala.cpp
// Generates a C++ wrapper to compile and execute a Scala program.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.scala>\n";
        return 1;
    }

    std::string ScalaFilePath = argv[1];
    std::ifstream TestInput(ScalaFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Scala file not found - " << ScalaFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::cout << "Compiling Scala file...\n";
    std::string CompileCommand = "scalac " + ScalaFilePath;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile Scala file.\n";
        return 1;
    }

    std::string FileNameWithoutExt = std::filesystem::path(ScalaFilePath).stem().string();

    std::ofstream Out("GeneratedScalaWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"scala " << FileNameWithoutExt << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Scala program execution failed.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedScalaWrapper.cpp\n";

    return 0;
}
