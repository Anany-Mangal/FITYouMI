// Cpp/Clojure.cpp
// Generates a C++ wrapper to execute a Clojure script using the clojure CLI tool.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Script.clj>\n";
        return 1;
    }

    std::string ClojureFilePath = argv[1];
    std::ifstream TestInput(ClojureFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: Clojure file not found - " << ClojureFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedClojureWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output C++ file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"clojure " << ClojureFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Clojure script.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedClojureWrapper.cpp\n";

    return 0;
}
