#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <inttypes.h>

#define DEFAULT 0
#define SEX 1
#define ADUCATION 2
#define FAMILY 4
#define WORK 8

typedef struct {
	char name[20];
	uint8_t data : 4;
} THuman;


uint8_t setBit(uint8_t mask, uint8_t field) {
	return field | mask;
}

void humanInit(THuman* man) {
	strcpy(man->name, "");
	man->data &= DEFAULT;
}

uint8_t setData(THuman* human, const char* head, const char* one, const char* two, uint8_t flag) {
	uint8_t ch = 0;

	printf(head);
	printf("1 - for %s.\n", one);
	printf("2 - for %s.\n", two);
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return setBit(ch == 1 ? flag : 0, human->data);
}

void humanInput(THuman* man) {
	uint8_t ch = 0;
	
	printf("Input name: ");
	scanf("%s", man->name);

	man->data = setData(man, "Input sex:\n", "MALE", "FEMALE", SEX);
	man->data = setData(man, "Input aducation:\n", "YES", "NO", ADUCATION);
	man->data = setData(man, "Input family:\n", "YES", "NO", FAMILY);
	man->data = setData(man, "Input work:\n", "YES", "NO", WORK);
}

void humanPrint(THuman* man) {
	printf("Name: %s.\n", man->name);
	printf("SEX: %s.\n", man->data & SEX ? "MALE" : "FEMALE");
	printf("ADUCATION: %s.\n", man->data & ADUCATION ? "YES" : "NO");
	printf("FAMILY: %s.\n", man->data & FAMILY ? "YES" : "NO");
	printf("WORK: %s.\n", man->data & WORK ? "YES" : "NO");
}

void passInput() {
	while (getchar() != '\n')
		continue;
}

uint8_t menu(THuman* human) {
	uint8_t ch = 0;

	system("cls");
	humanPrint(human);

	printf("Menu:\n");
	printf("1 - Input human.\n");
	printf("2 - Print human.\n");
	printf("3 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

int main(void) {
	THuman human;
	humanInit(&human);

	uint8_t ch = 0;

	while ((ch = menu(&human)) != 3) {
		switch (ch) {
		case 1:
			system("cls");
			humanInput(&human);
			break;

		case 2:
			humanPrint(&human);
			break;

		default:
			printf("Wrong input.\n");
			passInput();
		}

		printf("Press any key.\n");
		_getch();
	}

	return 0;
}