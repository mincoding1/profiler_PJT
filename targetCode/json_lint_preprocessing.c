#include <stdio.h>
#include <string.h>

char buf[10'000'000] = { 0 };
char stack[10'000'000] = { 0 };
void preprocessing(const char fileName[50]);

int main() {
	
	//��θ� ���ο��� �°� ���� �ʿ�.
	preprocessing("C:\\Users\\user\\source\\repos\\Project22\\targetCode\\input1.json");
	preprocessing("C:\\Users\\user\\source\\repos\\Project22\\targetCode\\input2.json");
	preprocessing("C:\\Users\\user\\source\\repos\\Project22\\targetCode\\input3.json");
	preprocessing("C:\\Users\\user\\source\\repos\\Project22\\targetCode\\input4.json");
}

int inputFile(char* fileName) {
	int result = 1;

	FILE* fp;
	if (fopen_s(&fp, fileName, "r") != 0) {
		printf("ERROR :: ���� ��ΰ� �߸��Ǿ����ϴ�.\n");
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
			printf("ERROR :: { ������ ���� } �� �����ߴ�.\n");
			goto EXIT_FAIL;
		}
	}

	if (cnt != 0) {
		printf("ERROR :: { ���� } �� �� ����.\n");
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
			printf("ERROR :: [ ������ ���� ] �� �����ߴ�.\n");
			goto EXIT_FAIL;
		}
	}

	if (cnt != 0) {
		printf("ERROR :: [ ���� ] �� �� ����.\n");
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

	//���� ���� ã��
	for (int i = 0; i < size; i++) {
		if (buf[i] == ' ') continue;
		if (buf[i] == '\r') continue;
		if (buf[i] == '\t') continue;
		if (buf[i] == '\n') continue;
		start = i;
		break;
	}

	//������ ã��
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
		printf("ERROR :: ������ { �Ǵ� [ �� �ƴմϴ�.\n");
		goto EXIT_FAIL;
	}

	if (buf[size - 1] != '}' && buf[size - 1] != ']') {
		printf("ERROR :: ������ { �Ǵ� [ �� �ƴմϴ�.\n");
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
	//" ã��
	for (int i = 1; i < size; i++) {
		if (buf[i - 1] == '\\' && buf[i] == '"') continue;
		if (buf[i] == '"') cnt++;
	}

	if (cnt % 2 == 1) {
		printf("ERROR :: �ֵ���ǥ�� ���� �� ������ �ʾҽ��ϴ�.\n");
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

		//���� �� ����ǥ ã��
		for (int i = 1; i < size; i++) {
			if (buf[i - 1] == '\\' && buf[i] == '"') continue;
			if (buf[i] == '"') {
				start = i;
				break;
			}
		}

		if (start == 0) break;

		//�� �� ����ǥ ã��
		for (int i = start + 1; i < size; i++) {
			if (buf[i - 1] == '\\' && buf[i] == '"') continue;
			if (buf[i] == '"') {
				end = i;
				break;
			}
		}

		//���ڿ��� S ���ڷ� �ٲٱ�
		buf[start] = 'S';
		int a = start + 1;

		for (int i = end + 1; i < size; i++) {
			buf[a] = buf[i];
			a++;
		}

		for (int i = a; i < size; i++) {
			buf[i] = 0;
		}

		//���ڿ��� ���� ����
		strCnt++;
	}

	//���� üũ
	//�ֵ���ǥ ���ΰ� �ƴ�, ��򰡿� ���� S�� �����ϸ� �ȵȴ�.

	int size = strlen(buf);
	int cnt = 0;
	for (int i = 0; i < size; i++) {
		if (buf[i] == 'S') cnt++;
	}

	if (strCnt != cnt) {
		printf("ERROR :: S ���ڰ� �߸��� ��ġ�� �����մϴ�.\n");
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
			printf("ERROR :: �빮�ڰ� ������ �� �����ϴ�.\n");
			goto EXIT_FAIL;
		}
	}

	return 0;
EXIT_FAIL:
	return result;
}


int step7() {
	int result = 1;

	//false�� �ִ´ٸ� V�� ����
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

	//true / null�� �ִ´ٸ� V�� ����
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

			printf("ERROR :: �Ҽ��� �հ� �ڿ� ���ڰ� �����ؾ��Ѵ�.\n");
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

	//���� ã���� V�� ����
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

	//������ �ʴ� ����
	//: , V S { [ ] } �� ���ȴ�.	

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

		printf("ERROR :: ������ �ʴ� ���ڰ� �����ϰų�, ������ �߸��Ǿ����ϴ�.\n");
		goto EXIT_FAIL;
	}

	return 0;
EXIT_FAIL:
	return result;
}

int step13() {
	int result = 1;

	//�����ؾ� �� ��
	//Str �� Value�� �����ٸ�, V�� ����

	int size = strlen(buf);
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == ':' && buf[i + 1] == 'S') buf[i + 1] = 'V'; // {S:S} --> {S:V}
		if (buf[i] == '[' && buf[i + 1] == 'S') buf[i + 1] = 'V'; // [S] --> [V]
		if (buf[i] == 'S' && buf[i + 1] == ',') buf[i] = 'V'; // [V,S,V] --> [V,V,V]
		if (buf[i] == 'S' && buf[i + 1] == ']') buf[i] = 'V'; // [V,S] --> [V,V]
	}

	//������ S�� ��� K (Key)�� ����
	for (int i = 0; i < size; i++) {
		if (buf[i] == 'S') buf[i] = 'K';
	}

	return 0;
EXIT_FAIL:
	return result;
}


int step14() {
	int result = 1;

	//Key, Value, ��ȣ ������ �߸��� ���� �ִ��� �˻�

	//, �������� K, V { [ �� �� �� �ִ�.
	int size = strlen(buf);
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == ',' && buf[i + 1] == 'K') continue;
		if (buf[i] == ',' && buf[i + 1] == 'V') continue;
		if (buf[i] == ',' && buf[i + 1] == '{') continue;
		if (buf[i] == ',' && buf[i + 1] == '[') continue;
		if (buf[i] == ',') {
			printf("ERROR :: Value�� �ش��ϴ� ���� �߸��Ǿ����ϴ�.\n");
			goto EXIT_FAIL;
		}
	}

	//: �������� V { [ �� �� �� �ִ�.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == ':' && buf[i + 1] == 'V') continue;
		if (buf[i] == ':' && buf[i + 1] == '{') continue;
		if (buf[i] == ':' && buf[i + 1] == '[') continue;
		if (buf[i] == ':') {
			printf("ERROR :: Value�� �ش��ϴ� ���� �߸��Ǿ����ϴ�.\n");
			goto EXIT_FAIL;
		}
	}

	//K �������� : �� �� �� �ִ�.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == 'K' && buf[i + 1] == ':') continue;
		if (buf[i] == 'K') {
			printf("ERROR :: Key ���� ���� �߸��Ǿ����ϴ�.\n");
			goto EXIT_FAIL;
		}
	}

	//V �������� , ] } �� �� �� �ִ�.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == 'V' && buf[i + 1] == ',') continue;
		if (buf[i] == 'V' && buf[i + 1] == ']') continue;
		if (buf[i] == 'V' && buf[i + 1] == '}') continue;
		if (buf[i] == 'V') {
			printf("ERROR :: Value ���� ���� �߸��Ǿ����ϴ�.\n");
			goto EXIT_FAIL;
		}
	}

	//{ �������� K �� �� �� �ִ�.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == '{' && buf[i + 1] == 'K') continue;
		if (buf[i] == '{') {
			printf("ERROR :: Key ���� �߸��Ǿ����ϴ�.\n");
			goto EXIT_FAIL;
		}
	}

	//[ �������� V { [ ] �� �� �� �ִ�.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == '[' && buf[i + 1] == 'V') continue;
		if (buf[i] == '[' && buf[i + 1] == '{') continue;
		if (buf[i] == '[' && buf[i + 1] == '[') continue;
		if (buf[i] == '[' && buf[i + 1] == ']') continue;
		if (buf[i] == '[') {
			printf("ERROR :: Array ���� �߸��Ǿ����ϴ�.\n");
			goto EXIT_FAIL;
		}
	}

	//} �������� , } ] �� �� �� �ִ�.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == '}' && buf[i + 1] == ',') continue;
		if (buf[i] == '}' && buf[i + 1] == '}') continue;
		if (buf[i] == '}' && buf[i + 1] == ']') continue;
		if (buf[i] == '}') {
			printf("ERROR :: Object ������ ���� �߸��Ǿ����ϴ�.\n");
			goto EXIT_FAIL;
		}
	}
	//] �������� , } ] �� �� �� �ִ�.
	for (int i = 0; i < size - 1; i++) {
		if (buf[i] == ']' && buf[i + 1] == ',') continue;
		if (buf[i] == ']' && buf[i + 1] == '}') continue;
		if (buf[i] == ']' && buf[i + 1] == ']') continue;
		if (buf[i] == ']') {
			printf("ERROR :: Array ������ ���� �߸��Ǿ����ϴ�.\n");
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

	//{ [ { [ ������� ���ȴٸ�, ] } ] } ������� ���;� �Ѵ�.	
	int size = strlen(buf);
	for (int i = 0; i < size; i++) {
		if (buf[i] == '}' && sp == 0) {
			printf("ERROR :: } ��ȣ ������ ���� ������ ��������\n");
			goto EXIT_FAIL;
		}
		if (buf[i] == ']' && sp == 0) {
			printf("ERROR :: ] ��ȣ ������ ���� ������ ��������\n");
			goto EXIT_FAIL;
		}

		if (buf[i] == '}' && stack[sp - 1] == '[') {
			printf("ERROR :: [ �� ���� ���Ŀ� } �� ���� ������ ��������\n");
			goto EXIT_FAIL;
		}

		if (buf[i] == ']' && stack[sp - 1] == '{') {
			printf("ERROR :: { �� ���� ���Ŀ� ] �� ���� ������ ��������\n");
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

	//{ } ������ �´��� �˻�
	if (step1()) goto EXIT_FAIL;

	//[ ] ������ �´��� �˻�
	if (step2()) goto EXIT_FAIL;

	//ù ������ { �̰ų� [ �̾���ϰ�, �� ���� ] �̰ų� } �̾���Ѵ�.
	if (step3()) goto EXIT_FAIL;

	// ����ǥ�� ������ �´��� �˻�
	if (step4()) goto EXIT_FAIL;

	// String ���ڿ��� ��� S �̶�� ���ڷ� ����
	if (step5()) goto EXIT_FAIL;

	// S�� ������ �ٸ� �빮�ڰ� �����ϸ� �ȵȴ�.
	if (step6()) goto EXIT_FAIL;

	// true, false, null ���ڸ� V��� ���ڷ� ����
	if (step7()) goto EXIT_FAIL;

	// �Ҽ��� �հ� �ڿ��� �ݵ�� ���ڰ� �����ϴ��� �˻�
	if (step8()) goto EXIT_FAIL;

	// �Ҽ����� �����Ѵ�.
	if (step9()) goto EXIT_FAIL;

	// ���� ã���� V��� ���ڷ� �����Ѵ�.
	if (step10()) goto EXIT_FAIL;

	// ȭ��Ʈ�����̽� ���ֱ� (����, /t, /n, /r)
	if (step11()) goto EXIT_FAIL;

	// ������ �ʴ� ���ڰ� �ִ��� �˻�
	if (step12()) goto EXIT_FAIL;

	// String �� Value �ڸ��� �ִٸ�, S�� V�� ����
	// String �� Key �ڸ��� �ִٸ�, S�� K�� ����
	if (step13()) goto EXIT_FAIL;

	// �߸��� ���� �˻�
	if (step14()) goto EXIT_FAIL;

	// ��ȣ ���� �˻�
	if (step15()) goto EXIT_FAIL;

	printf("%s\n\n", buf);
	return 0;

EXIT_FAIL:
	printf("ERROR�� ���α׷��� �����մϴ�.\n\n");
	return result;
}
