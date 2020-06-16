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

// меню логина и пароля
void users_menu(char *login, char *password) {
	users_database_t database = load_users_database("users.csv"); // массив структур


	int item; // выбираемый пункт меню

	item = get_menu(database, login, password);

	switch (item) {
	case 0:
	{
		printf("Неверный пароль или логин. \n");
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
	free(database.users); // освобождаем динамическую память
}

// меню для книг
void book_menu() {
	books_database_t database = load_books_database("books.csv");
	int item; // выбираемый пункт меню

	do {
		printf("Выберите действие\n");
		printf("0. Вывести все книги\n");
		printf("1. Добавить книгу\n");
		printf("2. Удалить книгу по номеру ISBN\n");
		printf("3. Изменить книгу\n");
		printf("4. Изменить количество книг\n");
		printf("5. Выйти\n");
		printf(">");
		scanf("%d%*c", &item); // считываем пункт меню

		// обрабатываем некорректный ввод пункта меню
		while (item < 0 || item > 5) {
			printf("Некорректный пункт меню, повторите ввод: ");
			scanf("%i%*c", &item); // считываем пункт меню ещё раз
		}

		switch (item) {
		case 0:
			print_books(database); // выводим все книги
			break;

		case 1:
			add_book(&database); // добавляем новую запись
			break;

		case 2:
			remove_book(&database); // удаляем книгу
			break;

		case 3:
			edit_book(&database);  // редактируем книгу
			break;

		case 4:
			edit_book_count(&database); // редактируем количество книг
			break;
		}

		printf("\n");
	} while (item != 5); // повторяем, пока не решим выйти

	save_books_database(database, "books.csv"); // сохраняем состояние библиотеки
	free(database.books); // освобождаем память
}

void students_menu() {
	students_database_t database = load_students_database("students.csv"); // массив структур
	int item; // выбираемый пункт меню

	do {
		printf("Выберите действие\n");
		printf("1. Добавить студента\n");
		printf("2. Удалить по номеру зачётки\n");
		printf("3. Редактировать по номеру зачётки\n");
		printf("4. Просмотреть по номеру зачётки\n");
		printf("5. Выйти\n");
		printf(">");
		scanf("%d%*c", &item); // считываем пункт меню

		// обрабатываем некорректный ввод пункта меню
		while (item < 1 || item > 5) {
			printf("Некорректный пункт меню, повторите ввод: ");
			scanf("%d%*c", &item); // считываем пункт меню ещё раз
		}

		switch (item) {
		case 1:
			add_student(&database); // добавляем новую запись
			break;

		case 2:
			remove_student(&database);
			break;

		case 3:
			edit_student(&database);  // редактируем запись
			break;

		case 4:
			get_student(database);
			break;
		}

		printf("\n");
	} while (item != 5); // повторяем, пока не решим выйти

	save_students_database(database, "students.csv"); // сохраняем студентов в файл
	free(database.students); // освобождаем динамическую память
}

void books_students_menu() {
	char mode[100]; // режим работы
	printf("Выберите режим работы (book, students): ");
	scanf("%[^\n]", mode);

	while (strcmp(mode, "book") && strcmp(mode, "students")) {
		printf("Вы выбрали некорректный режим, повторите ввод: ");
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

	printf("Введите логин: ");
	scanf("%[^\n]%*c", login); // считываем логина

	printf("Введите пароль: ");
	scanf("%[^\n]%*c", password); // считываем пароль

	users_menu(login, password);

	return 0;
}