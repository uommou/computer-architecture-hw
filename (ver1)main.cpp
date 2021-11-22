
#include <stdio.h>

//null ������ 1�� �߰���
const int MAX = 101;
const int RESULT_MAX = 201;

const char *inputFileName = "input.txt";
const char *outputFileName = "hw03_output.txt";

char numberA[MAX] = {};
char numberB[MAX] = {};
char resultArray[RESULT_MAX] = {};//���� ����
int result;//less equal greater
int mul_Array[RESULT_MAX] = { 0, };

int operation_count = 0;//���� Ƚ�� ����
char tempArray[202] = {'\0', };//�� �� �� �ӽ�����
char operationType;//������
int start_numberB_from_here;//numberB ����� �ε���

int i = 0;
int j = 0;
int count_digits_A = 0;
int count_digits_B = 0;
char temp;
int value;

int print_index = 0;


//����Ƚ���� �д� �Լ�(��)
void read_operation_count(FILE* inputfile) {
	fscanf(inputfile, "%d", &operation_count);
}

//less �Լ�(��)
void less_operation(char numberA[MAX], char numberB[MAX]) {
	for (i = 0; i < MAX; i++) {
		if (numberA[i] < numberB[i]) {
			result = 1;
			break;
		}
		else if (i == MAX - 1)
			result = 0;
	}
}

//equal �Լ�(��)
void equal_operation(char numberA[MAX], char numberB[MAX]) {
	for (i = 0; i < MAX; i++) {
		if (numberA[i] != numberB[i]) {
			result=0;
			break;
		}
		else if (i == MAX - 1)
			result=1;
	}
}

//greater �Լ�(��)
void greater_operation(char numberA[MAX], char numberB[MAX]) {
	for (i = 0; i < MAX; i++) {
		if (numberA[i] > numberB[i]) {
			result = 1;
			break;
		}
		else if (i == MAX - 1)
			result = 0;
	}
}

//���ϱ� �Լ�(��)
void add_operation(char numberA[MAX], char numberB[MAX]) {
	//resultArray �ʱ�ȭ
	for (i = 0; i < RESULT_MAX - 1; i++) {
		resultArray[i] = '0';
	}
	//����
	for (i = MAX - 2; i >= 0; i--) {
		value = (numberA[i] - 48) + (numberB[i] - 48);
		if (value >= 10) {
			resultArray[100 + i - 1] += 1;
			value -= 10;
		}
		resultArray[100 + i] += value;
	}
}

//���� �Լ�(��)
void sub_operation(char numberA[MAX], char numberB[MAX]) {
	//resultArray �ʱ�ȭ
	for (i = 0; i < RESULT_MAX - 1; i++) {
		resultArray[i] = '0';
	}
	//less�� ��ȯ���� 1(true)�̸� ����� ����
	less_operation(numberA, numberB);
	//����� 0�Ǵ� ����� ��� : A-B
	if (result == 0) {
		for (i = MAX - 2; i >= 0; i--) {
			value = (numberA[i] - 48) - (numberB[i] - 48);
			if (value < 0) {
				resultArray[100 + i - 1] -= 1;
				value += 10;
			}
			resultArray[100 + i] += value;
		}
	}
	//����� ������ ��� : B-A
	else if (result == 1) {
		for (i = MAX - 2; i >= 0; i--) {
			value = (numberB[i] - 48) - (numberA[i] - 48);
			if (value < 0) {
				resultArray[100 + i - 1] -= 1;
				value += 10;
			}
			resultArray[100 + i] += value;
		}
	}
}

//���ϱ� �Լ�(��)
void multiply_operation(char numberA[MAX], char numberB[MAX]) {
	
	for (i = MAX - 2; i >= 0; i--) {
		//numberA[0~MAX-2]*numberB[i]
		for (j = MAX - 2; j >= 0; j--) {
			value = (numberA[j] - 48) * (numberB[i] - 48);
			mul_Array[i + j + 1] += value % 10;
			mul_Array[i + j] += value / 10;
			mul_Array[i + j] += mul_Array[i + j + 1] / 10;
			mul_Array[i + j + 1] = mul_Array[i + j + 1] % 10;
		}
	}
	for (i = 0; i < RESULT_MAX - 1; i++) {
		resultArray[i] = mul_Array[i] + 48;
	}
}



int main(){

	FILE* inputfile = fopen(inputFileName , "r");
	FILE* outputfile = fopen(outputFileName, "w");

	//����Ƚ�� �о����
	read_operation_count(inputfile);
	
	//���� /nó��
	fgets(tempArray, sizeof(tempArray), inputfile);


	//���⼭���� �ݺ����� �־��ֱ�
	for (int count = 0; count < operation_count; count++) {

		//ù��° �� �а� �ӽ� �迭�� ����
		fgets(tempArray, sizeof(tempArray), inputfile);

		//ù��° �ǿ����� �ӽ�����
		for (i = 0; ; i++) {
			if (tempArray[i] == '+' ||
				tempArray[i] == '-' ||
				tempArray[i] == '*' ||
				tempArray[i] == '>' ||
				tempArray[i] == '=' ||
				tempArray[i] == '<') {
				//����������
				operationType = tempArray[i];
				start_numberB_from_here = i + 1;
				break;
			}
			numberA[i] = tempArray[i];
		}
		//printf("%s\n", numberA);
		//printf("%c\n", operationType);

		//�ι�° �ǿ����� �ӽ�����
		for (i = start_numberB_from_here; ; i++) {
			if (tempArray[i] == '\n')
				break;
			numberB[j] = tempArray[i];
			j++;
		}
		//printf("%s\n", numberB);

		//�ǿ����� digit ���� �� �ڷ� �о��ֱ�
		for (i = 0; i < MAX - 1; i++) {
			if (numberA[i] != '\0')
				count_digits_A++;
			else
				numberA[i] = '0';
		}
		//printf("%s\n", numberA);

		for (i = count_digits_A; i > 0; i--) {
			temp = numberA[(MAX - count_digits_A - 1) + (i - 1)];
			numberA[(MAX - count_digits_A - 1) + (i - 1)] = numberA[i - 1];
			numberA[i - 1] = temp;
		}
		//printf("%s\n", numberA);

		//�ʱ�ȭ
		temp = 0;
		for (i = 0; i < MAX - 1; i++) {
			if (numberB[i] != '\0')
				count_digits_B++;
			else
				numberB[i] = '0';
		}
		//printf("%s\n", numberB);

		for (i = count_digits_B; i > 0; i--) {
			temp = numberB[(MAX - count_digits_B - 1) + (i - 1)];
			numberB[(MAX - count_digits_B - 1) + (i - 1)] = numberB[i - 1];
			numberB[i - 1] = temp;
		}
		//printf("%s\n", numberB);

		//�������
		if (operationType == '+') {
			//���ϱ� ���� �Լ�
			add_operation(numberA, numberB);

			//resultArray�� 0�� ����
			for (i = 0; i < RESULT_MAX; i++) {
				if (resultArray[i] == '0') {
					print_index++;
					continue;
				}
				else
					break;
			}
			//������� 0�� ���
			if (print_index == RESULT_MAX - 1) {
				fprintf(outputfile, "%c", '0');
			}
			//0 �ƴ� ���
			for (i = print_index; i < RESULT_MAX; i++) {
				fprintf(outputfile, "%c", resultArray[i]);
			}
			fprintf(outputfile, "\n");
		}
		else if (operationType == '-') {
			//���� ���� �Լ�
			sub_operation(numberA, numberB);
			//resultArray�� 0�� �ǳʶٱ�
			for (i = 0; i < RESULT_MAX; i++) {
				if (resultArray[i] == '0') {
					print_index++;
					continue;
				}
				else
					break;
			}
			//������� 0�� ���
			if (print_index == RESULT_MAX - 1) {
				fprintf(outputfile, "%c", '0');
			}
			//������ ��� ��ȣ �߰�
			less_operation(numberA, numberB);
			if (result == 1) {
				resultArray[print_index - 1] = '-';
				for (i = print_index - 1; i < RESULT_MAX; i++) {
					fprintf(outputfile, "%c", resultArray[i]);
				}
			}
			//����� ���
			else {
				for (i = print_index; i < RESULT_MAX; i++) {
					fprintf(outputfile, "%c", resultArray[i]);
				}
			}
			fprintf(outputfile, "\n");
		}
		else if (operationType == '*') {
			//���ϱ� ���� �Լ�
			multiply_operation(numberA, numberB);
			//resultArray�� 0�� �����ϰ� ���
			for (i = 0; i < RESULT_MAX; i++) {
				if (resultArray[i] == '0') {
					print_index++;
					continue;
				}
				else
					break;
			}
			//������� 0�� ���
			if (print_index == RESULT_MAX - 1) {
				fprintf(outputfile, "%c", '0');
			}
			//0 �ƴ� ���
			for (i = print_index; i < RESULT_MAX; i++) {
				fprintf(outputfile, "%c", resultArray[i]);
			}
			fprintf(outputfile, "\n");
		}
		else if (operationType == '<') {
			//less ���� �Լ�
			less_operation(numberA, numberB);
			fprintf(outputfile, "%d", result);
			fprintf(outputfile, "\n");
		}
		else if (operationType == '=') {
			//equal ���� �Լ�
			equal_operation(numberA, numberB);
			fprintf(outputfile, "%d", result);
			fprintf(outputfile, "\n");
		}
		else if (operationType == '>') {
			//greater ���� �Լ�
			greater_operation(numberA, numberB);
			fprintf(outputfile, "%d", result);
			fprintf(outputfile, "\n");
		}
		else {
			printf("operationType error!");
		}

		//�ʱ�ȭ
		for (i = 0; i < 202; i++) {
			tempArray[i] = '\0';
		}
		for (i = 0; i < MAX; i++) {
			numberA[i] = '\0';
		}
		for (i = 0; i < MAX; i++) {
			numberB[i] = '\0';
		}
		for (i = 0; i < RESULT_MAX; i++) {
			resultArray[i] = '\0';
		}
		for (i = 0; i < RESULT_MAX; i++) {
			mul_Array[i] = 0;
		}
		i = 0;
		j = 0;

		result = 0;
		start_numberB_from_here = 0;
		count_digits_A = 0;
		count_digits_B = 0;
		value = 0;
		print_index = 0;
	}
	fclose(inputfile);
	fclose(outputfile);
	return 1;
}


