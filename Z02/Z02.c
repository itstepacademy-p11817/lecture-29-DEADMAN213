#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <inttypes.h>

#define DEFAULT 0
#define CLASS 10

const char letters[3] = { 'Ä', 'Å' ,'Ç' };

typedef struct {
	char name[10];
	uint8_t year : 4;
	uint8_t letter : 3;
	uint8_t age : 5;
	uint8_t mark : 4;
} TPupil;


void passInput() {
	while (getchar() != '\n')
		continue;
}

TPupil pupilInit() {
	TPupil temp;

	memset(temp.name, '\0', 10);

	temp.year &= DEFAULT;
	temp.letter &= DEFAULT;
	temp.age &= DEFAULT;
	temp.mark &= DEFAULT;

	return temp;
}

void pupilsInit(TPupil* pupils) {
	for (uint8_t i = 0; i < CLASS; i++) {
		*(pupils + i) = pupilInit();
	}
}

uint8_t letterIndex() {
	char ch = 0;

	passInput();
	scanf("%c", &ch);

	for (uint8_t i = 0; i < 3; i++) {
		if (ch == letters[i]) {
			return i + 1;
		}
	}

	return 0;
}

uint8_t simpleInput() {
	uint8_t mask = 0;

	scanf("%hhu", &mask);

	return mask;
}

uint8_t setMask(uint8_t mask, uint8_t field) {
	return mask | field;
}

uint8_t setData(uint8_t pupil, const char* head, uint8_t (*pf)()) {
	uint8_t mask = 0;

	printf(head);
	mask = pf();

	return setMask(mask, pupil);
}

TPupil pupilInput() {
	uint8_t mask = 0;
	TPupil temp = pupilInit();

	printf("Input name: ");
	scanf("%s", temp.name);

	temp.year = setData(temp.year, "Input year (1-11): ", simpleInput);
	temp.letter = setData(temp.letter, "Input letter (Ä-Ç): ", letterIndex);
	temp.age = setData(temp.age, "Input age (7-18): ", simpleInput);
	temp.mark = setData(temp.mark, "Input mark (3-10): ", simpleInput);

	return temp;
}

void pupilsInput(TPupil* pupil) {
	for (uint8_t i = 0; i < CLASS; i++) {
		system("cls");
		printf("Input %hhu pupil:\n", i + 1);
		*(pupil + i) = pupilInput();
	}
}

void printHead() {
	printf("%10s", "Name");
	printf("%10s", "Year");
	printf("%10s", "Letter");
	printf("%10s", "Age");
	printf("%10s", "Mark\n");
}

void pupilPrint(TPupil* pupil) {
	printf("%10s", pupil->name);
	printf("%10hhu", pupil->year);
	printf("%10c", letters[pupil->letter - 1]);
	printf("%10hhu", pupil->age);
	printf("%9hhu\n", pupil->mark);
}

void findPupils(TPupil* pupil, uint8_t bgn, uint8_t end) {
	for (uint8_t i = 0; i < CLASS; i++) {
		if ((pupil + i)->year >= bgn && (pupil + i)->year <= end) {
			pupilPrint(pupil + i);
		}
	}
}

void pupilsPrint(TPupil* pupil) {
	for (uint8_t i = 0; i < CLASS; i++) {
		pupilPrint(pupil + i);
	}
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Input class.\n");
	printf("2 - Print class.\n");
	printf("3 - Find pupil.\n");
	printf("4 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

int main(void) {
	uint8_t ch = 0;
	TPupil pupils[CLASS];
	pupilsInit(pupils);

	while ((ch = menu()) != 4) {
		switch (ch) {
		case 1:
			pupilsInput(pupils);
			break;

		case 2:
			system("cls");
			printHead();
			pupilsPrint(pupils);
			break;

		case 3:
			system("cls");
			printHead();
			findPupils(pupils, 4, 7);
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