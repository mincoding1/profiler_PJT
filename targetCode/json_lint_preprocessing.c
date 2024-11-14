#include <stdio.h>
#include <string.h>

char buf[10'000'000] = { 0 };
char stack[10'000'000] = { 0 };
void preprocessing(const char fileName[50]);

int main() {
	
	//경로를 본인에게 맞게 수정 필요.
	preprocessing("C:\\Users\\user\\source\\repos\\Project22\\targetCode\\input1.json");
	preprocessing("C:\\Users\\user\\source\\repos\\Project22\\targetCode\\input2.json");
	preprocessing("C:\\Users\\user\\source\\repos\\Project22\\targetCode\\input3.json");
	preprocessing("C:\\Users\\user\\source\\repos\\Project22\\targetCode\\input4.json");
}

int inputFile(char* fileName) {
	int result = 1;

	FILE* fp;
	if (fopen_s(&fp, fileName, "r") != 0) {
		printf("ERROR :: 파일 경로가 잘못되었습니다.\n");
		goto EXIT_FAIL;
	}

	char ch;
	int n = 0;
	memset(buf, 0, sizeof(buf));

	while ((ch = fgetc(fp)) != EOF) {
		buf[n++] = ch;
	}

	fclose(fp);

	return 0;

EXIT_FAIL:
	return result;
}

int step1() {
	int result = 1;

	int size = strlen(buf);

	int cnt = 0;
	for (int i = 0; i < size; i++) {
		if (buf[i] == '{') cnt++;
		if (buf[i] == '}') cnt--;
		if (cnt == -1) {
			printf("ERROR :: { 나오기 전에 } 가 등장했다.\n");
			goto EXIT_FAIL;
		}
	}

	if (cnt != 0) {
		printf("ERROR :: { 보다 } 가 더 많다.\n");
		goto EXIT_FAIL;
	}

	return 0;

EXIT_FAIL:
	return result;
}


int step2() {
	int result = 1;
	int size = strlen(buf);

	int cnt = 0;
	for (int i = 0; i < size; i++) {
		if (buf[i] == '[') cnt++;
		if (buf[i] == ']') cnt--;
		if (cnt == -1) {
			printf("ERROR :: [ 나오기 전에 ] 가 등장했다.\n");
			goto EXIT_FAIL;
		}
	}

	if (cnt != 0) {
		printf("ERROR :: [ 보다 ] 가 더 많다.\n");
		goto EXIT_FAIL;
	}

	return 0;

EXIT_FAIL:
	return result;
}

void trim() {
	int size = strlen(buf);

	int start = 0;
	int end = size - 1;

	//시작 지점 찾기
	for (int i = 0; i < size; i++) {
		if (buf[i] == ' ') continue;
		if (buf[i] == '\r') continue;
		if (buf[i] == '\t') continue;
		if (buf[i] == '\n') continue;
		start = i;
		break;
	}

	//마지막 찾기
	for (int i = size - 1; i >= 0; i--) {
		if (buf[i] == ' ') continue;
		if (buf[i] == '\r') continue;
		if (buf[i] == '\t') continue;
		if (buf[i] == '\n') continue;
		end = i;
		break;
	}

	int a = 0;
	for (int i = start; i <= end; i++) {
		buf[a] = buf[i];
		a++;
	}

	for (int i = a; i < size; i++) {
		buf[i] = 0;
	}
}

int step3() {
	int result = 1;

	trim();
	int size = strlen(buf);

	if (buf[0] != '{' && buf[0] != '[') {
		printf("ERROR :: 시작이 { 또는 [ 가 아닙니다.\n");
		goto EXIT_FAIL;
	}

	if (buf[size - 1] != '}' && buf[size - 1] != ']') {
		printf("ERROR :: 시작이 { 또는 [ 가 아닙니다.\n");
		goto EXIT_FAIL;
	}

	return 0;
EXIT_FAIL:
	return result;
}

int step4() {
	int result = 1;
	int size = strlen(buf);

	int flag = 0;

	int cnt = 0;
	//" 찾기
	for (int i = 1; i < size; i++) {
		if (buf[i - 1] == '\\' && buf[i] == '"') continue;
		if (buf[i] == '"') cnt++;
	}

	if (cnt % 2 == 1) {
		printf("ERROR :: 쌍따옴표가 열린 후 닫히지 않았습니다.\n");
		goto EXIT_FAIL;
	}

	return 0;
EXIT_FAIL:
	return result;
}

int step5() {
	int result = 1;

	int strCnt = 0;

	while (1) {

		int flag = 0;

		int start = 0;
		int size = strlen(buf);
		int end = size - 1;

		//시작 쌍 따옴표 찾기
		for (int i = 1; i < size; i++) {
			if (buf[i - 1] == '\\' && buf[i] == '"') continue;
			if (buf[i] == '"') {
				start = i;
				break;
			}
		}

		if (start == 0) break;

		//끝 쌍 따옴표 찾기
		for (int i = start + 1; i < size; i++) {
			if (buf[i - 1] == '\\' && buf[i] == '"') continue;
			if (buf[i] == '"') {
				end = i;
				break;
			}
		}

		//문자열을 S 글자로 바꾸기
		buf[start] = 'S';
		int a = start + 1;

		for (int i = end + 1; i < size; i++) {
			buf[a] = buf[i];
			a++;
		}

		for (int i = a; i < size; i++) {
			buf[i] = 0;
		}

		//문자열의 개수 세기
		strCnt++;
	}

	//버그 체크
	//쌍따옴표 내부가 아닌, 어딘가에 문자 S가 존재하면 안된다.

	int size = strlen(buf);
	int cnt = 0;
	for (int i = 0; i < size; i++) {
		if (buf[i] == 'S') cnt++;
	}

	if (strCnt != cnt) {
		printf("ERROR :: S 글자가 잘못된 위치에 존재합니다.\n");
		goto EXIT_FAIL;
	}

	return 0;
EXIT_FAIL:
	return result;
}

int step6() {
	int result = 1;

	for (int i = 0; i < strlen(buf); i++) {
		if (buf[i] == 'S') continue;
		if (buf[i] >= 'A' && buf[i] <= 'Z') {
			printf("ERROR :: 대문자가 존재할 수 없습니다.\n");
			goto EXIT_FAIL;
		}
	}

	return 0;
EXIT_FAIL:
	return result;
}


int step7() {
	int result = 1;

	//false가 있는다면 V로 변경
	while (1) {
		int flag = 0;
		int size = strlen(buf);

		for (int i = 0; i < size - 5; i++) {
			if (buf[i] == 'f' && buf[i + 1] == 'a' && buf[i + 2] == 'l' && buf[i + 3] == 's' && buf[i + 4] == 'e') {


				buf[i] = 'V';
				int a = i + 1;

				for (int j = i + 5; j < size; j++) {
					buf[a] = buf[j];
					a++;
				}

				for (int j = a; j < size; j++) {
					buf[a] = 0;
				}

				flag = 1;
				break;
			}
		}

		if (flag == 0) break;
	}

	//true / null이 있는다면 V로 변경
	while (1) {
		int flag = 0;
		int size = strlen(buf);

		for (int i = 0; i < size - 5; i++) {
			if ((buf[i] == 't' && buf[i + 1] == 'r' && buf[i + 2] == 'u' && buf[i + 3] == 'e') ||
				(buf[i] == 'n' && buf[i + 1] == 'u' && buf[i + 2] == 'l' && buf[i + 3] == 'l')) {

				buf[i] = 'V';
				int a = i + 1;

				for (int j = i + 4; j < size; j++) {
					buf[a] = buf[j];
					a++;
				}

				for (int j = a; j < size; j++) {
					buf[a] = 0;
				}

				flag = 1;
				break;
			}
		}

		if (flag == 0) break;
	}

	return 0;
EXIT_FAIL:
	return result;
}

int step8() {
	int result = 1;

	int size = strlen(buf);
	for (int i = 1; i < size - 1; i++) {
		if (buf[i] == '.') {
			if (buf[i - 1] >= '0' && buf[i - 1] <= '9' && buf[i + 1] >= '0' && buf[i + 1] <= '9') continue;

			printf("ERROR :: 소숫점 앞과 뒤에 숫자가 존재해야한다.\n");
			goto EXIT_FAIL;
		}
	}

	return 0;
EXIT_FAIL:
	return result;
}

int step9() {
	int result = 1;


	while (1) {
		int flag = 0;
		int size = strlen(buf);

		for (int i = 0; i < size; i++) {
			if (buf[i] == '.') {

				int a = i;
				for (int j = i + 1; j <= size; j++) {
					buf[a] = buf[j];
					a++;
				}

				flag = 1;
			}
		}

		if (flag == 0) break;
	}

	return 0;
EXIT_FAIL:
	return result;
}


int step10() {
	int result = 1;

	//수를 찾으면 V로 변경
	while (1) {
		int flag = 0;
		int size = strlen(buf);

		int start = -1;
		int end = -1;

		for (int i = 0; i < size; i++) {
			if (buf[i] >= '0' && buf[i] <= '9') {
				start = i;
				break;
			}
		}

		if (start == -1) break;

		for (int i = start + 1; i <= size; i++) {
			if (!(buf[i] >= '0' && buf[i] <= '9')) {
				end = i - 1;
				break;
			}
		}

		buf[start] = 'V';
		int a = start + 1;

		for (int i = end + 1; i < size; i++) {
			buf[a] = buf[i];
			a++;
		}

		for (int i = a; i < size; i++) {
			buf[i] = 0;
		}
	}

	return 0;
EXIT_FAIL:
	return result;
}


int step11() {
	int result = 1;


	while (1) {
		int flag = 0;

		for (int i = 0; i < strlen(buf); i++) {
			if (buf[i] == ' ' || buf[i] == '\r' || buf[i] == '\n' || buf[i] == '\t') {

				int a = i;
				int size = strlen(buf);
				for (int j = i + 1; j <= size; j++) {
					buf[a] = buf[j];
					a++;
				}

				flag = 1;
			}
		}

		if (flag == 0) break;
	}

	return 0;
EXIT_FAIL:
	return result;
}

int step12() {
	int result = 1;

	//허용되지 않는 문자
	//: , V S { [ ] } 만 허용된다.	

	int size = strlen(buf);
	for (int i = 0; i < size; i++) {
		if (buf[i] == ':') continue;
		if (buf[i] == ',') continue;
		if (buf[i] == '{') continue;
		if (buf[i] == '[') continue;
		if (buf[i] == ']') continue;
		if (buf[i] == '}') continue;
		if (buf[i] == 'V') continue;
		if (buf[i] == 'S') continue;

		printf("ERROR :: 허용되지 않는 문자가 존재하거나, 문법이 잘못되었습니다.\n");
		goto EXIT_FAIL;
	}

	return 0;
EXIT_FAIL:
	return result;
}

int step13() {
	int result = 1;

	//변경해야 할 것
	//Str 이 Value로 쓰였다면, V로 변경

	int size = strlen(buf);
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == ':' && buf[i + 1] == 'S') buf[i + 1] = 'V'; // {S:S} --> {S:V}
		if (buf[i] == '[' && buf[i + 1] == 'S') buf[i + 1] = 'V'; // [S] --> [V]
		if (buf[i] == 'S' && buf[i + 1] == ',') buf[i] = 'V'; // [V,S,V] --> [V,V,V]
		if (buf[i] == 'S' && buf[i + 1] == ']') buf[i] = 'V'; // [V,S] --> [V,V]
	}

	//나머지 S는 모두 K (Key)로 변경
	for (int i = 0; i < size; i++) {
		if (buf[i] == 'S') buf[i] = 'K';
	}

	return 0;
EXIT_FAIL:
	return result;
}


int step14() {
	int result = 1;

	//Key, Value, 괄호 순서가 잘못된 것이 있는지 검사

	//, 다음에는 K, V { [ 만 올 수 있다.
	int size = strlen(buf);
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == ',' && buf[i + 1] == 'K') continue;
		if (buf[i] == ',' && buf[i + 1] == 'V') continue;
		if (buf[i] == ',' && buf[i + 1] == '{') continue;
		if (buf[i] == ',' && buf[i + 1] == '[') continue;
		if (buf[i] == ',') {
			printf("ERROR :: Value에 해당하는 값이 잘못되었습니다.\n");
			goto EXIT_FAIL;
		}
	}

	//: 다음에는 V { [ 만 올 수 있다.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == ':' && buf[i + 1] == 'V') continue;
		if (buf[i] == ':' && buf[i + 1] == '{') continue;
		if (buf[i] == ':' && buf[i + 1] == '[') continue;
		if (buf[i] == ':') {
			printf("ERROR :: Value에 해당하는 값이 잘못되었습니다.\n");
			goto EXIT_FAIL;
		}
	}

	//K 다음에는 : 만 올 수 있다.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == 'K' && buf[i + 1] == ':') continue;
		if (buf[i] == 'K') {
			printf("ERROR :: Key 이후 값이 잘못되었습니다.\n");
			goto EXIT_FAIL;
		}
	}

	//V 다음에는 , ] } 만 올 수 있다.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == 'V' && buf[i + 1] == ',') continue;
		if (buf[i] == 'V' && buf[i + 1] == ']') continue;
		if (buf[i] == 'V' && buf[i + 1] == '}') continue;
		if (buf[i] == 'V') {
			printf("ERROR :: Value 이후 값이 잘못되었습니다.\n");
			goto EXIT_FAIL;
		}
	}

	//{ 다음에는 K 만 올 수 있다.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == '{' && buf[i + 1] == 'K') continue;
		if (buf[i] == '{') {
			printf("ERROR :: Key 값이 잘못되었습니다.\n");
			goto EXIT_FAIL;
		}
	}

	//[ 다음에는 V { [ ] 만 올 수 있다.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == '[' && buf[i + 1] == 'V') continue;
		if (buf[i] == '[' && buf[i + 1] == '{') continue;
		if (buf[i] == '[' && buf[i + 1] == '[') continue;
		if (buf[i] == '[' && buf[i + 1] == ']') continue;
		if (buf[i] == '[') {
			printf("ERROR :: Array 값이 잘못되었습니다.\n");
			goto EXIT_FAIL;
		}
	}

	//} 다음에는 , } ] 만 올 수 있다.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == '}' && buf[i + 1] == ',') continue;
		if (buf[i] == '}' && buf[i + 1] == '}') continue;
		if (buf[i] == '}' && buf[i + 1] == ']') continue;
		if (buf[i] == '}') {
			printf("ERROR :: Object 이후의 값이 잘못되었습니다.\n");
			goto EXIT_FAIL;
		}
	}
	//] 다음에는 , } ] 만 올 수 있다.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == ']' && buf[i + 1] == ',') continue;
		if (buf[i] == ']' && buf[i + 1] == '}') continue;
		if (buf[i] == ']' && buf[i + 1] == ']') continue;
		if (buf[i] == ']') {
			printf("ERROR :: Array 이후의 값이 잘못되었습니다.\n");
			goto EXIT_FAIL;
		}
	}

	return 0;
EXIT_FAIL:
	return result;
}

int step15() {
	int result = 1;
	int sp = 0;

	memset(stack, 0, sizeof(stack));

	//{ [ { [ 순서대로 열렸다면, ] } ] } 순서대로 나와야 한다.	
	int size = strlen(buf);
	for (int i = 0; i < size; i++) {
		if (buf[i] == '}' && sp == 0) {
			printf("ERROR :: } 괄호 닫힘이 먼저 등장한 문법에러\n");
			goto EXIT_FAIL;
		}
		if (buf[i] == ']' && sp == 0) {
			printf("ERROR :: ] 괄호 닫힘이 먼저 등장한 문법에러\n");
			goto EXIT_FAIL;
		}

		if (buf[i] == '}' && stack[sp - 1] == '[') {
			printf("ERROR :: [ 가 열린 이후에 } 가 먼저 등장한 문법에러\n");
			goto EXIT_FAIL;
		}

		if (buf[i] == ']' && stack[sp - 1] == '{') {
			printf("ERROR :: { 가 열린 이후에 ] 가 먼저 등장한 문법에러\n");
			goto EXIT_FAIL;
		}

		if (buf[i] == '{') stack[sp++] = '{';
		if (buf[i] == '[') stack[sp++] = ']';
		if (buf[i] == '}' && stack[sp - 1] == '{') stack[--sp] = 0;
		if (buf[i] == ']' && stack[sp - 1] == '[') stack[--sp] = 0;
	}

	return 0;
EXIT_FAIL:
	return result;
}

void preprocessing(const char fileName[50]) {
	int result = 1;

	printf("[%s]\n", fileName);
	if (inputFile(fileName)) goto EXIT_FAIL;

	//{ } 개수가 맞는지 검사
	if (step1()) goto EXIT_FAIL;

	//[ ] 개수가 맞는지 검사
	if (step2()) goto EXIT_FAIL;

	//첫 시작이 { 이거나 [ 이어야하고, 맨 끝이 ] 이거나 } 이어야한다.
	if (step3()) goto EXIT_FAIL;

	// 따옴표의 개수가 맞는지 검사
	if (step4()) goto EXIT_FAIL;

	// String 문자열을 모두 S 이라는 문자로 변경
	if (step5()) goto EXIT_FAIL;

	// S를 제외한 다른 대문자가 존재하면 안된다.
	if (step6()) goto EXIT_FAIL;

	// true, false, null 글자를 V라는 글자로 변경
	if (step7()) goto EXIT_FAIL;

	// 소수점 앞과 뒤에는 반드시 숫자가 존재하는지 검사
	if (step8()) goto EXIT_FAIL;

	// 소수점을 제거한다.
	if (step9()) goto EXIT_FAIL;

	// 수를 찾으면 V라는 문자로 변경한다.
	if (step10()) goto EXIT_FAIL;

	// 화이트스페이스 없애기 (공백, /t, /n, /r)
	if (step11()) goto EXIT_FAIL;

	// 허용되지 않는 문자가 있는지 검사
	if (step12()) goto EXIT_FAIL;

	// String 이 Value 자리에 있다면, S를 V로 변경
	// String 이 Key 자리에 있다면, S를 K로 변경
	if (step13()) goto EXIT_FAIL;

	// 잘못된 순서 검사
	if (step14()) goto EXIT_FAIL;

	// 괄호 순서 검사
	if (step15()) goto EXIT_FAIL;

	printf("%s\n\n", buf);
	return 0;

EXIT_FAIL:
	printf("ERROR로 프로그램을 종료합니다.\n\n");
	return result;
}
