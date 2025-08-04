// C++/Lua.hpp
// Module that converts a Lua file into a C++ file that executes it via the system's Lua interpreter.

#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

std::string Convert(const std::string& LuaFilePath)
{
    if (!std::filesystem::exists(LuaFilePath))
    {
        std::cerr << "Lua file not found: " << LuaFilePath << "\n";
        return "";
    }

    std::filesystem::path OutputPath = std::filesystem::temp_directory_path() / "LuaWrapper.cpp";
    std::ofstream Out(OutputPath);
    if (!Out.is_open())
    {
        std::cerr << "Failed to create output file: " << OutputPath << "\n";
        return "";
    }

    Out << "#include <cstdlib>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    int Result = std::system(\"lua " << LuaFilePath << "\");\n";
    Out << "    if (Result != 0) {\n";
    Out << "        std::cerr << \"Failed to execute Lua file.\\n\";\n";
    Out << "    }\n";
    Out << "    return Result;\n";
    Out << "}\n";

    Out.close();
    return OutputPath.string(); // Return path to generated C++ file
}
