// Cpp/Java.cpp
// This program takes a Java .class file (with a main method) and outputs a C++ file
// that, when compiled and run, executes the Java class using the Java Virtual Machine (JNI).

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <JavaClassName (without .class)>\n";
        return 1;
    }

    std::string JavaClassName = argv[1];
    std::ifstream TestInput(JavaClassName + ".class");
    if (!TestInput.good())
    {
        std::cerr << "Error: .class file not found - " << JavaClassName << ".class\n";
        return 1;
    }
    TestInput.close();

    std::ofstream Out("GeneratedJavaWrapper.cpp");
    if (!Out.is_open())
    {
        std::cerr << "Error: Could not create output file.\n";
        return 1;
    }

    Out << "#include <jni.h>\n";
    Out << "#include <iostream>\n\n";
    Out << "int main() {\n";
    Out << "    JavaVM* Jvm;\n";
    Out << "    JNIEnv* Env;\n";
    Out << "    JavaVMInitArgs VmArgs;\n";
    Out << "    JavaVMOption Options[1];\n";
    Out << "    Options[0].optionString = const_cast<char*>(\"-Djava.class.path=.\");\n";
    Out << "    VmArgs.version = JNI_VERSION_1_8;\n";
    Out << "    VmArgs.nOptions = 1;\n";
    Out << "    VmArgs.options = Options;\n";
    Out << "    VmArgs.ignoreUnrecognized = false;\n\n";
    Out << "    jint Res = JNI_CreateJavaVM(&Jvm, reinterpret_cast<void**>(&Env), &VmArgs);\n";
    Out << "    if (Res != JNI_OK) {\n";
    Out << "        std::cerr << \"Failed to create JVM\\n\";\n";
    Out << "        return 1;\n";
    Out << "    }\n\n";
    Out << "    jclass MainClass = Env->FindClass(\"" << JavaClassName << "\");\n";
    Out << "    if (!MainClass) {\n";
    Out << "        std::cerr << \"Could not find class \" << \"" << JavaClassName << "\" << std::endl;\n";
    Out << "        Jvm->DestroyJavaVM();\n";
    Out << "        return 1;\n";
    Out << "    }\n\n";
    Out << "    jmethodID MainMethod = Env->GetStaticMethodID(MainClass, \"main\", \"([Ljava/lang/String;)V\");\n";
    Out << "    if (!MainMethod) {\n";
    Out << "        std::cerr << \"main method not found.\" << std::endl;\n";
    Out << "        Jvm->DestroyJavaVM();\n";
    Out << "        return 1;\n";
    Out << "    }\n\n";
    Out << "    jobjectArray Args = Env->NewObjectArray(0, Env->FindClass(\"java/lang/String\"), nullptr);\n";
    Out << "    Env->CallStaticVoidMethod(MainClass, MainMethod, Args);\n";
    Out << "    Jvm->DestroyJavaVM();\n";
    Out << "    return 0;\n";
    Out << "}\n";

    Out.close();
    std::cout << "Generated C++ wrapper: GeneratedJavaWrapper.cpp\n";

    return 0;
}
