import os
import tempfile
import subprocess
from typing import Optional

def Convert(CppFilePath: str) -> Optional[str]:
    if not os.path.exists(CppFilePath):
        print(f"Error: File not found -> {CppFilePath}")
        return None

    # Compile the C++ file
    TempDir = tempfile.gettempdir()
    ExecutablePath = os.path.join(TempDir, "CppFromPythonExec")

    CompileCommand = ["g++", CppFilePath, "-o", ExecutablePath]
    CompilationResult = subprocess.run(CompileCommand, capture_output=True)

    if CompilationResult.returncode != 0:
        print("C++ Compilation failed:")
        print(CompilationResult.stderr.decode())
        return None

    # Generate Python wrapper file
    PythonWrapperPath = os.path.join(TempDir, "CppWrapper.py")
    with open(PythonWrapperPath, "w") as Wrapper:
        Wrapper.write("import subprocess\n")
        Wrapper.write(f"subprocess.run([r'{ExecutablePath}'])\n")

    return PythonWrapperPath
