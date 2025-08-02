import os
from Python import Cpp

def Execute(FilePath: str) -> None:
    Extension = os.path.splitext(FilePath)[1].lower()

    if Extension == ".cpp":
        Cpp.GeneratePythonWrapper(FilePath)
        Wrapper = "GeneratedCppWrapper.py"
        os.system(f"python {Wrapper}")

    elif Extension == ".lua":
        # Placeholder: Assume a binary like `Cpp/Lua` exists
        os.system(f"./Cpp/Lua {FilePath}")
        os.system("g++ GeneratedLuaWrapper.cpp -o RunLua -llua")
        os.system("./RunLua")

    else:
        raise ValueError(f"Unsupported file type: {Extension}")
