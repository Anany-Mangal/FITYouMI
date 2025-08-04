// Cpp/Erlang.cpp
// This program takes an Erlang file, compiles it, and generates a C++ file
// that calls the compiled Erlang module using the Erlang shell.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Source.erl>\n";
        return 1;
    }

    std::string ErlangFilePath = argv[1];
    std::ifstream TestInput(ErlangFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Erlang file not found - " << ErlangFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::filesystem::path FilePath = ErlangFilePath;
    std::string ModuleName = FilePath.stem().string();

    std::string CompileCommand = "erlc " + ErlangFilePath;
    std::cout << "Compiling Erlang file...\n";
    if (std::system(CompileCommand.c_str()) != 0)
    {
        std::cerr << "Failed to compile Erlang file.\n";
        return 1;
    }

    if (!std::filesystem::exists(ModuleName + ".beam"))
    {
        std::cerr << "Compiled BEAM file not found: " << ModuleName << ".beam\n";
        return 1;
    }

    std::ofstream Out("GeneratedErlangWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"erl -noshell -eval '" << ModuleName << ":main(),' -s init stop\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Erlang module.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedErlangWrapper.cpp\n";

    return 0;
}
