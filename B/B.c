#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <inttypes.h>

#define CREATURES 10

typedef enum { HUMAN, CAT, VEHICLE } TType;
const char* types[3] = { "HUMAN", "CAT", "VEHICLE" };

typedef enum { MALE, FEMALE } TGender;
const char* genders[2] = { "MALE", "FEMALE" };

typedef struct {
	char name[10];
	TGender gender;
	uint8_t age;
	float height;
}THuman;

typedef struct {
	char nickname[10];
	TGender gender;
	char breed[10];
	uint8_t age;
} TCat;

typedef struct {
	char firm[10];
	char model[10];
	uint16_t year;
} TVehicle;

typedef struct{
	TType type;
	union {
		THuman human;
		TCat cat;
		TVehicle vehicle;
	};
} TCreature;


//печать инфы человека
void printHumanHead() {
	printf("%10s", "Name");
	printf("%10s", "Gender");
	printf("%10s", "Age");
	printf("%10s", "Height\n");
}

void printHuman(TCreature* creature) {
	printf("%s: ", types[creature->type]);

	printf("%s, ", creature->human.name);
	printf("Gender: %s, ", genders[creature->human.gender]);
	printf("Age: %hhu, ", creature->human.age);
	printf("Height: %.2f.\n", creature->human.height);
}


//печать инфы кiта
void printCatHead() {
	printf("%10s", "Nickname");
	printf("%10s", "Gender");
	printf("%10s", "Breed");
	printf("%10s", "Age\n");
}

void printCat(TCreature* creature) {
	printf("%s: ", types[creature->type]);

	printf("Nickname: %s, ", creature->cat.nickname);
	printf("Gender: %s, ", genders[creature->cat.gender]);
	printf("Breed: %s, ", creature->cat.breed);
	printf("Age: %hhu.\n", creature->cat.age);
}


//печать инфы машины
void printVehicleHead() {
	printf("%10s", "Firm");
	printf("%10s", "Model");
	printf("%10s", "Year\n");
}

void printVehicle(TCreature* creature) {
	printf("%s: ", types[creature->type]);

	printf("Firm: %s, ", creature->vehicle.firm);
	printf("Model: %s, ", creature->vehicle.model);
	printf("Year: %hu.\n", creature->vehicle.year);
}

void printCreature(TCreature* creature) {
	void(*print[3])(TCreature*) = { printHuman, printCat, printVehicle };

	for (uint8_t i = 0; i < CREATURES; i++) {
		(*print[(creature + i)->type])(creature + i);
	}
}

//ввод человека
TCreature inputHuman() {
	TCreature temp = { 0 };

	printf("Input name: ");
	scanf("%s", temp.human.name);

	printf("Input gender (0 - MALE, 1 - Female): ");
	scanf("%i", &temp.human.gender);

	printf("Input age: ");
	scanf("%hhu", &temp.human.age);

	printf("Input height: ");
	scanf("%f", &temp.human.height);

	return temp;
}

//ввод кiта
TCreature inputCat() {
	TCreature temp = { 1 };

	printf("Input nickname: ");
	scanf("%s", temp.cat.nickname);

	printf("Input gender (0 - MALE, 1 - Female): ");
	scanf("%i", &temp.cat.gender);

	printf("Input breed: ");
	scanf("%s", temp.cat.breed);

	printf("Input age: ");
	scanf("%hhu", &temp.cat.age);

	return temp;
}

//ввод машины
TCreature inputVehicle() {
	TCreature temp = { 2 };

	printf("Input firm: ");
	scanf("%s", temp.vehicle.firm);

	printf("Input model: ");
	scanf("%s", temp.vehicle.model);

	printf("Input year: ");
	scanf("%hu", &temp.vehicle.year);

	return temp;
}

uint8_t typeCreature() {
	uint8_t ch = 0;

	printf("Creature type:\n");
	for (uint8_t i = 0; i < 3; i++) {
		printf("%hhu - %s.\n", i + 1, types[i]);
	}
	printf("Input type: ");
	scanf("%hhu", &ch);

	return ch - 1;
}

void inputCreatures(TCreature* creatures) {
	uint8_t ch = 0;
	TCreature(*input[3])() = { inputHuman, inputCat, inputVehicle };

	for (uint8_t i = 0; i < CREATURES; i++) {
		system("cls");
		ch = typeCreature();
		*(creatures + i) = (*input[ch])();
	}
}

bool printCreatureType(TCreature* creatures, uint8_t num) {
	bool flag = false;
	void(*print[3])(TCreature*) = { printHuman, printCat, printVehicle };

	printf("All %ss:\n", types[num]);
	for (uint8_t i = 0; i < CREATURES; i++) {
		if ((creatures + i)->type == num) {
			flag = true;
			(*print[(creatures + i)->type])(creatures + i);
		}
	}

	return flag;
}

void passInput() {
	while (getchar() != '\n')
		continue;
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Input creature.\n");
	printf("2 - Print creature.\n");
	printf("3 - Find creature.\n");
	printf("4 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

int main(void) {
	TCreature creatures[CREATURES];
	uint8_t ch = 0;

	while ((ch = menu()) != 4) {
		switch (ch) {
		case 1:
			inputCreatures(creatures);
			break;

		case 2:
			system("cls");
			printCreature(creatures);
			break;

		case 3: 
			if (!printCreatureType(creatures, typeCreature())) {
				printf("No much found.\n");
			}
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