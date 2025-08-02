# Python/Cpp.py
# This script takes a C++ source file as input and generates a Python script
# that compiles and runs the C++ file when the Python script is executed.

import os
import subprocess
import sys

def GeneratePythonWrapper(CppFilePath: str, OutputFilePath: str = "GeneratedCppWrapper.py") -> None:
    if not os.path.exists(CppFilePath):
        print(f"Error: '{CppFilePath}' not found.")
        return

    ExecutableName = os.path.splitext(os.path.basename(CppFilePath))[0] + "_bin"
    
    with open(OutputFilePath, "w") as OutFile:
        OutFile.write("import subprocess\n")
        OutFile.write("import os\n\n")
        OutFile.write(f"CppFile = \"{CppFilePath}\"\n")
        OutFile.write(f"Executable = \"{ExecutableName}\"\n")
        OutFile.write("if not os.path.exists(Executable):\n")
        OutFile.write("    print(\"Compiling...\")\n")
        OutFile.write("    Result = subprocess.run(['g++', CppFile, '-o', Executable, '-llua'])\n")
        OutFile.write("    if Result.returncode != 0:\n")
        OutFile.write("        raise RuntimeError(\"Compilation failed\")\n")
        OutFile.write("print(\"Running C++ Executable...\")\n")
        OutFile.write("subprocess.run(['./' + Executable])\n")

    print(f"Generated Python wrapper: {OutputFilePath}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python Cpp.py <path_to_cpp_file>")
    else:
        GeneratePythonWrapper(sys.argv[1])
