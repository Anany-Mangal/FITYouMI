// Cpp/JavaScript.cpp
// This C++ program takes a JavaScript file path as input, then generates a C++ file
// which, when compiled and run, executes the JS file using Duktape (an embeddable JS engine).

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path_to_javascript_file>\n";
        return 1;
    }

    std::string JSFilePath = argv[1];
    std::ifstream TestInput(JSFilePath);
    if (!TestInput.good())
    {
        std::cerr << "Error: File not found - " << JSFilePath << "\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedJavaScriptWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output file.\n";
        return 1;
    }

    Out << "#include <duktape.h>\n";
    Out << "#include <fstream>\n";
    Out << "#include <sstream>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    std::ifstream File(\"" << JSFilePath << "\");\n";
    Out << "    if (!File.is_open()) {\n";
    Out << "        std::cerr << \"Failed to open JavaScript file.\\n\";\n";
    Out << "        return 1;\n";
    Out << "    }\n";
    Out << "    std::stringstream Buffer;\n";
    Out << "    Buffer << File.rdbuf();\n";
    Out << "    std::string Script = Buffer.str();\n\n";
    Out << "    duk_context* Ctx = duk_create_heap_default();\n";
    Out << "    if (!Ctx) {\n";
    Out << "        std::cerr << \"Failed to create Duktape context.\\n\";\n";
    Out << "        return 1;\n";
    Out << "    }\n\n";
    Out << "    if (duk_peval_string(Ctx, Script.c_str()) != 0) {\n";
    Out << "        std::cerr << \"JavaScript Error: \" << duk_safe_to_string(Ctx, -1) << std::endl;\n";
    Out << "    }\n";
    Out << "    duk_destroy_heap(Ctx);\n";
    Out << "    return 0;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedJavaScriptWrapper.cpp\n";

    return 0;
}
