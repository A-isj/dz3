#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "books.h"
#include "students.h"
#include "users.h"

void book_menu();
void students_menu();
void books_students_menu();

// ���� ������ � ������
void users_menu(char *login, char *password) {
	users_database_t database = load_users_database("users.csv"); // ������ ��������


	int item; // ���������� ����� ����

	item = get_menu(database, login, password);

	switch (item) {
	case 0:
	{
		printf("�������� ������ ��� �����. \n");
		scanf("%*c");
		break;
	}
	case 1: 
		books_students_menu();
		break;
	case 2:
		book_menu();
		break;
	case 3:
		students_menu();
		break;
	}
	free(database.users); // ����������� ������������ ������
}

// ���� ��� ����
void book_menu() {
	books_database_t database = load_books_database("books.csv");
	int item; // ���������� ����� ����

	do {
		printf("�������� ��������\n");
		printf("0. ������� ��� �����\n");
		printf("1. �������� �����\n");
		printf("2. ������� ����� �� ������ ISBN\n");
		printf("3. �������� �����\n");
		printf("4. �������� ���������� ����\n");
		printf("5. �����\n");
		printf(">");
		scanf("%d%*c", &item); // ��������� ����� ����

		// ������������ ������������ ���� ������ ����
		while (item < 0 || item > 5) {
			printf("������������ ����� ����, ��������� ����: ");
			scanf("%i%*c", &item); // ��������� ����� ���� ��� ���
		}

		switch (item) {
		case 0:
			print_books(database); // ������� ��� �����
			break;

		case 1:
			add_book(&database); // ��������� ����� ������
			break;

		case 2:
			remove_book(&database); // ������� �����
			break;

		case 3:
			edit_book(&database);  // ����������� �����
			break;

		case 4:
			edit_book_count(&database); // ����������� ���������� ����
			break;
		}

		printf("\n");
	} while (item != 5); // ���������, ���� �� ����� �����

	save_books_database(database, "books.csv"); // ��������� ��������� ����������
	free(database.books); // ����������� ������
}

void students_menu() {
	students_database_t database = load_students_database("students.csv"); // ������ ��������
	int item; // ���������� ����� ����

	do {
		printf("�������� ��������\n");
		printf("1. �������� ��������\n");
		printf("2. ������� �� ������ �������\n");
		printf("3. ������������� �� ������ �������\n");
		printf("4. ����������� �� ������ �������\n");
		printf("5. �����\n");
		printf(">");
		scanf("%d%*c", &item); // ��������� ����� ����

		// ������������ ������������ ���� ������ ����
		while (item < 1 || item > 5) {
			printf("������������ ����� ����, ��������� ����: ");
			scanf("%d%*c", &item); // ��������� ����� ���� ��� ���
		}

		switch (item) {
		case 1:
			add_student(&database); // ��������� ����� ������
			break;

		case 2:
			remove_student(&database);
			break;

		case 3:
			edit_student(&database);  // ����������� ������
			break;

		case 4:
			get_student(database);
			break;
		}

		printf("\n");
	} while (item != 5); // ���������, ���� �� ����� �����

	save_students_database(database, "students.csv"); // ��������� ��������� � ����
	free(database.students); // ����������� ������������ ������
}

void books_students_menu() {
	char mode[100]; // ����� ������
	printf("�������� ����� ������ (book, students): ");
	scanf("%[^\n]", mode);

	while (strcmp(mode, "book") && strcmp(mode, "students")) {
		printf("�� ������� ������������ �����, ��������� ����: ");
		scanf("%s%*c", mode);
	}

	if (!strcmp(mode, "book")) {
		book_menu();
	}
	else {
		students_menu();
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	setlocale(LC_CTYPE, ".1251");
	setlocale(LC_MONETARY, ".1251");
	system("chcp .1251");

	char login[40];
	char password[40];

	printf("������� �����: ");
	scanf("%[^\n]%*c", login); // ��������� ������

	printf("������� ������: ");
	scanf("%[^\n]%*c", password); // ��������� ������

	users_menu(login, password);

	return 0;
}