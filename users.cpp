#define _CRT_SECURE_NO_WARNINGS

#include "users.h"

// получение индекса пользовотеля по логину
int find_login(users_database_t database, char *id) {
	// ищем книгу по номеру
	for (int i = 0; i < database.size; i++)
		if (!strcmp(id, database.users[i].login))
			return i;

	return -1; // не нашли
}

// поиск меню для пользовотеля
int get_menu(users_database_t database, char *login, char *password) {
	if (find_login(database, login) == -1)
		return 0;
	else
	{
		if ((strcmp(login, database.users[find_login(database, login)].login) == 0) && (strcmp(password, database.users[find_login(database, login)].password) == 0))
		{
			if ((database.users[find_login(database, login)].books == true) && (database.users[find_login(database, login)].students == true))
				return 1; // полный доступ
			else
				if (database.users[find_login(database, login)].books == true)
					return 2; // меню книг
				else
					if (database.users[find_login(database, login)].students == true)
						return 3; // меню студентов
					else
						return 0;
		}
		else
			return 0; // ошибка ввода логина или пароля
	}
}

// загрузка базы пользователей из файла
users_database_t load_users_database(const char *path) {
	FILE *f = fopen(path, "r"); // открываем файл на чтение
	users_database_t database;
	database.size = 0; // обнуляем количество

	if (!f) { // если не удалось открыть файл
		database.users = NULL;
		return database; // возвращаем пустую базу
	}

	database.users = (users_t *)malloc(sizeof(users_t)); // выделяем память под один элемент

	while (!feof(f)) {
		fscanf(f, "%[^;]%*c", database.users[database.size].login);
		fscanf(f, "%[^;]%*c", database.users[database.size].password);
		fscanf(f, "%i%*c", &database.users[database.size].books);
		fscanf(f, "%i%*c", &database.users[database.size].students);

		database.size++; // увеличиваем размер
		database.users = (users_t *)realloc(database.users, (database.size + 1) * sizeof(users_t)); // перераспределяем память
	}

	fclose(f); // закрываем файл

	return database; // возвращаем считанный массив
}
