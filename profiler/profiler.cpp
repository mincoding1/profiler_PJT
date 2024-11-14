#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

//============================================================================================================
//[경로 Check 필요!] 다음 경로는 Project22 솔루션 일때 예시코드이다.
//============================================================================================================
//빌드 프로그램 파일 경로 (MSBuild.exe)
const string msbuild_path = R"(C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe)";

//프로젝트 파일 경로 (targetCode.vcxproj)
const string pjt_path = R"(C:\Users\user\source\repos\Project22\targetCode\targetCode.vcxproj)";

//빌드 후 실행해야 할 파일 경로 (targetCode.exe)
const string exe_path = R"(C:\Users\user\source\repos\Project22\targetCode\Release\targetCode.exe)";
//============================================================================================================

void build() {
    //Release Mode로 Build
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

    //초기화 코드
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