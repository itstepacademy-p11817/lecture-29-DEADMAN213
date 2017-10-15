#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <inttypes.h>

typedef union {
	int32_t integerValue;
	float floatValue;
	double doubleValue;
} TCollector;

typedef struct {
	uint8_t type;
	TCollector collector;
} TData;


void passInput() {
	while (getchar() != '\n') {
		continue;
	}
}

uint8_t subMenu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Input integer value.\n");
	printf("2 - Input float value.\n");
	printf("3 - Input double value.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void inputData(TData* data) {
	bool flag = false;

	while (!flag) {
		uint8_t ch = subMenu();
		switch (ch) {
		case 1:
			printf("Input integer value: ");
			scanf("%i", &(data->collector.integerValue));
			break;

		case 2:
			printf("Input float value: ");
			scanf("%f", &(data->collector.floatValue));
			break;

		case 3:
			printf("Input double value: ");
			scanf("%lf", &(data->collector.doubleValue));
			break;

		default:
			printf("Wrong input.\n");
			passInput();
			printf("Press any key.\n");
			_getch();
			continue;
		}

		flag = true;
	}

}

void printData(TData* data) {
	system("cls");

	printf("Integer value: %i.\n", data->collector.integerValue);
	printf("Float value: %f.\n", data->collector.floatValue);
	printf("Double value: %lf.\n", data->collector.doubleValue);
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Input data.\n");
	printf("2 - Print data.\n");
	printf("3 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

int main(void) {
	TData data = { 0 };
	uint8_t ch = 0;

	while ((ch = menu()) != 3) {
		switch (ch) {
		case 1:
			inputData(&data);
			break;

		case 2:
			printData(&data);
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