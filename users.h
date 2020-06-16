#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// структура для хранения полей
typedef struct users_t {
	char login[40]; // логин
	char password[40]; // пароль
	bool books; // доступ к книгам
	bool students; // доступ к студентам
} users_t;

// база данных студентов
typedef struct users_database_t {
	users_t *users;
	int size;
} users_database_t;

int find_login(users_database_t database, char *id); // поиск номера пользователя по логину
int get_menu(users_database_t database, char *login, char *password); // получение меню пользовотеля

users_database_t load_users_database(const char *path); // загрузка базы студентов из файла