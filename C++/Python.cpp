// Cpp/Python.cpp
// This C++ program takes a Python file path as input, then generates a new C++ source file.
// When that C++ file is compiled and executed, it runs the original Python file.

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path_to_python_file>\n";
        return 1;
    }

    std::string PythonFilePath = argv[1];
    std::ifstream TestInput(PythonFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: File not found - " << PythonFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedPythonWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output file.\n";
        return 1;
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    std::cout << \"Running Python script...\\n\";\n";
    Out << "    int Result = std::system(\"python3 " << PythonFilePath << "\");\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedPythonWrapper.cpp\n";

    return 0;
}
