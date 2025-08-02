// Cpp/Lua.cpp
// This program takes a Lua file as input and generates a C++ file that embeds and executes that Lua script.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string EscapeForCString(const std::string& Input) {
    std::ostringstream Escaped;
    for (char C : Input) {
        if (C == '\\') Escaped << "\\\\";
        else if (C == '"') Escaped << "\\\"";
        else if (C == '\n') Escaped << "\\n";
        else Escaped << C;
    }
    return Escaped.str();
}

int main(int Argc, char** Argv) {
    if (Argc < 2) {
        std::cerr << "Usage: Lua <path_to_lua_file>\n";
        return 1;
    }

    std::string LuaFilePath = Argv[1];
    std::ifstream LuaFile(LuaFilePath);
    if (!LuaFile) {
        std::cerr << "Failed to open Lua file: " << LuaFilePath << "\n";
        return 1;
    }

    std::ostringstream LuaContent;
    std::string Line;
    while (std::getline(LuaFile, Line)) {
        LuaContent << Line << "\n";
    }
    LuaFile.close();

    std::string EscapedLua = EscapeForCString(LuaContent.str());

    std::string OutputFileName = "GeneratedLuaWrapper.cpp";
    std::ofstream OutFile(OutputFileName);
    if (!OutFile) {
        std::cerr << "Failed to create output file: " << OutputFileName << "\n";
        return 1;
    }

    OutFile << "#include <iostream>\n";
    OutFile << "#include <lua.hpp>\n\n";
    OutFile << "int main() {\n";
    OutFile << "    lua_State* L = luaL_newstate();\n";
    OutFile << "    luaL_openlibs(L);\n\n";
    OutFile << "    const char* LuaCode = \"" << EscapedLua << "\";\n";
    OutFile << "    if (luaL_dostring(L, LuaCode)) {\n";
    OutFile << "        std::cerr << \"Lua Error: \" << lua_tostring(L, -1) << std::endl;\n";
    OutFile << "    }\n";
    OutFile << "    lua_close(L);\n";
    OutFile << "    return 0;\n";
    OutFile << "}\n";

    OutFile.close();
    std::cout << "Generated C++ file: " << OutputFileName << "\n";
    return 0;
}
