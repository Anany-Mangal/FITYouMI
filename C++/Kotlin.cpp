// Cpp/Kotlin.cpp
// Takes a Kotlin file, compiles it, and generates a C++ file that runs it via Java.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <KotlinFile.kt>\n";
        return 1;
    }

    std::string KotlinFilePath = argv[1];
    std::ifstream TestInput(KotlinFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Kotlin file not found - " << KotlinFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::cout << "Compiling Kotlin...\n";

    std::string JarOutput = "KotlinOutput.jar";
    std::string CompileCommand = "kotlinc " + KotlinFilePath + " -include-runtime -d " + JarOutput;
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile Kotlin file.\n";
        return 1;
    }

    if (!std::filesystem::exists(JarOutput))
    {
        std::cerr << "Error: Compiled JAR not found - " << JarOutput << "\n";
        return 1;
    }

    std::ofstream Out("GeneratedKotlinWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"java -jar " << JarOutput << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Kotlin program.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedKotlinWrapper.cpp\n";

    return 0;
}
