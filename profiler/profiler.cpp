#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

//============================================================================================================
//[��� Check �ʿ�!] ���� ��δ� Project22 �ַ�� �϶� �����ڵ��̴�.
//============================================================================================================
//���� ���α׷� ���� ��� (MSBuild.exe)
const string msbuild_path = R"(C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe)";

//������Ʈ ���� ��� (targetCode.vcxproj)
const string pjt_path = R"(C:\Users\user\source\repos\Project22\targetCode\targetCode.vcxproj)";

//���� �� �����ؾ� �� ���� ��� (targetCode.exe)
const string exe_path = R"(C:\Users\user\source\repos\Project22\targetCode\Release\targetCode.exe)";
//============================================================================================================

void build() {
    //Release Mode�� Build
    const string option = R"(/p:Configuration=Release)";

    string cmd = string{ "\"" } + msbuild_path + string{ "\" " } + pjt_path + string{ " " } + option;
    system(cmd.c_str());
}

void run() {
    string cmd = string{ "\"" } + exe_path + string{ "\"" };
    system(cmd.c_str());
}

static void LATENCY_INIT() {
    static int flag = 0;
    if (flag != 0) return;
    flag = 1;

    //�ʱ�ȭ �ڵ�
}

static void LATENCY_CHECK_START() {
    LATENCY_INIT();

}

static void LATENCY_CHECK_END() {

}

int main() {
    build();
    run();
}