// Cpp/Elixir.cpp
// Generates a C++ wrapper to execute an Elixir script using the Elixir runtime.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.exs>\n";
        return 1;
    }

    std::string ElixirFilePath = argv[1];
    std::ifstream TestInput(ElixirFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Elixir script not found - " << ElixirFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedElixirWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"elixir " << ElixirFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Elixir script execution failed.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedElixirWrapper.cpp\n";

    return 0;
}
