#include <stdio.h>
#include <stdlib.h>
#define CHAR_CNT 128
#define CHAR_LINES 6
#define CHAR_LEN 64

int main() {
	FILE* f = fopen("slash printer.txt", "r");
	char chars[CHAR_CNT];									//사용되는 문자 목록
	char slashes[CHAR_CNT][CHAR_LINES][CHAR_LEN] = {0, };	//슬래시 문양
	int charnum = 0;										//사용되는 문자의 개수

	if (f == NULL) {										//파일 읽기 실패
		printf("Failed to open file\n");
		fclose(f);
		return 0;
	}

	for (char c = fgetc(f); c != EOF; c = fgetc(f)) {	//파일 읽기
		if (c != '\n') {								//문자 감지
			printf("Detected character \'%c\'\n", c);
			chars[charnum] = c;
			fgetc(f);

			for (int i = 0; i < CHAR_LINES; i++) {
				int j = 0;

				for (c = fgetc(f); c != '\n'; c = fgetc(f)) {
					if (c != '.') {						//'.' 문자는 제외
						slashes[charnum][i][j] = c;
						j++;
					}
				}
				slashes[charnum][i][j] = '\n';
			}
			charnum++;
		}
	}
	
	printf("%d characters detected\n", charnum);
	printf("\n");

	/*
	//감지된 문양 출력
	for (int i = 0; i < charnum; i++) {
		printf("%c\n", chars[i]);
		for (int j = 0; j < CHAR_LINES; j++) {
			printf("%s", slashes[i][j]);
		}
	}
	*/

	char input[1024] = {0, };											//입력받은 문장
	char output[CHAR_LINES][CHAR_CNT * CHAR_LEN + CHAR_LINES] = {0, };	//출력할 문자
	int numout[CHAR_LINES] = {0, };										//output의 각 줄의 길이

	printf("Enter your message :");
	scanf("%[^\n]s", input);

	for (int i = 0; i < CHAR_LINES; i++) {								//출력 문장 앞에 공백 추가
		for (int j = 0; j < CHAR_LINES - i - 1; j++) {
			output[i][j] = ' ';
		}
		numout[i] = CHAR_LINES - i - 1;
	}

	for (int i = 0; input[i] != '\n'; i++) {		//출력할 문자
		int cur = 0;								//검사하는 문자가 chars의 몇 번째에 있는지

		if (input[i] >= 'a' && input[i] <= 'z') {	//소문자이면
			input[i] += 'A' - 'a';
		}

		for ( ; cur < charnum; cur++) {				//cur 설정
			if (chars[cur] == input[i]) {
				break;
			}
		}
		
		if (cur >= charnum) continue;				//검사하는 문자가 없으면 건너뜀

		for (int j = 0; j < CHAR_LINES; j++) {
			int k;
			for (k = 0; slashes[cur][j][k] != '\n'; k++) {	//output에 문자 추가
				output[j][numout[j]] = slashes[cur][j][k];
				numout[j]++;
			}

			if (input[i + 1] != '\0') {						//마지막 글자가 아니면
				output[j][numout[j]] = ' ';					//글자 간 간격 추가
				numout[j]++;
			}
		}
	}

	for (int i = 0; i < CHAR_LINES; i++) {
		printf("%s\n", output[i]);
	}

	fclose(f);
	
	system("pause");
	return 0;
}