// C++/Python.hpp
// This header defines a Convert() function that takes a Python file as input
// and generates a C++ file that, when compiled and run, executes the Python code.

#ifndef PYTHON_TO_CPP_HPP
#define PYTHON_TO_CPP_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>

std::string Convert(const std::string& PythonFilePath)
{
    if (!std::filesystem::exists(PythonFilePath))
    {
        throw std::runtime_error("Python file not found: " + PythonFilePath);
    }

    std::string OutputCpp = "GeneratedPythonWrapper.cpp";
    std::ofstream Out(OutputCpp);

    if (!Out.is_open())
    {
        throw std::runtime_error("Failed to create C++ output file");
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"python3 " << PythonFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Python file.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    return OutputCpp;
}

#endif // PYTHON_TO_CPP_HPP
