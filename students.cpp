#define _CRT_SECURE_NO_WARNINGS
#include "students.h"

// считывание полей структуры
student_t read_student(char *id) {
	student_t student; // создаём структуру

	// считываем поля
	strcpy(student.id, id); // считываем номер зачётной книжки

	printf("Введите фамилию: ");
	scanf("%[^\n]%*c", student.lastname); // считываем фамилия

	printf("Введите имя: ");
	scanf("%[^\n]%*c", student.firstname); // считываем имя

	printf("Введите отчество: ");
	scanf("%[^\n]%*c", student.patronumic); // считываем отчество

	printf("Введите название факультета: ");
	scanf("%[^\n]%*c", student.faculty); // считываем факультет

	printf("Введите специальность: ");
	scanf("%[^\n]%*c", student.speciality); // считываем специальность

	return student; // возвращаем считанную структуру
}

// сохранение студента в файл
void save_student(FILE *f, student_t student) {
	fprintf(f, "%s;", student.id);
	fprintf(f, "%s;", student.lastname);
	fprintf(f, "%s;", student.firstname);
	fprintf(f, "%s;", student.patronumic);
	fprintf(f, "%s;", student.faculty);
	fprintf(f, "%s", student.speciality);
}

// получение индекса студента по номеру зачётной книжки
int find_student(students_database_t database, char *id) {
	// ищем книгу по номеру
	for (int i = 0; i < database.size; i++)
		if (!strcmp(id, database.students[i].id))
			return i;

	return -1; // не нашли
}

// добавление новой записи
void add_student(students_database_t *database) {
	char id[17];
	printf("Введите номер зачётки: ");
	scanf("%[^\n]%*c", id);

	while (find_student(*database, id) != -1) { // если студент с таким номером уже есть
		printf("Студент с такой зачёткой уже есть, повторите ввод: "); // сообщаем об этом
		scanf("%[^\n]", id);
	}

	database->students = (student_t *)realloc(database->students, (database->size + 1) * sizeof(student_t)); // перераспределяем память
	printf("Введите информацию о студенте\n");
	database->students[database->size++] = read_student(id); // считываем поля
}

// удаление студента по номеру
void remove_student(students_database_t *database) {
	if (database->size == 0) { // если ещё нет записей
		printf("Ещё не было добавлено ни одного студента\n");
		return; // выходим
	}

	char id[16];
	printf("Введите номер зачётки: ");
	scanf("%[^\n]%*c", id);

	int index = find_student(*database, id); // ищем книгу по номеру

	// если не нашли
	if (index == -1) {
		printf("Нет студента с таким номерор зачётки\n"); // сообщаем об этом
		return; // и выходим
	}

	// сдвигаем книги влево
	for (database->size--; index < database->size; index++)
		database->students[index] = database->students[index + 1];
}

// редактирование записи
void edit_student(students_database_t *database) {
	if (database->size == 0) { // если ещё нет записей
		printf("Ещё не было добавлено ни одного студента\n");
		return; // выходим
	}

	char id[16];
	printf("Введите номер зачётки: ");
	scanf("%[^\n]%*c", id);

	int index = find_student(*database, id); // ищем студента

	if (index == -1) {
		printf("Нет такого студента\n");
		return;
	}

	printf("Введите новую информацию об этом студенте:\n");
	database->students[index] = read_student(id); // считываем новые данные
}

// поиск студента
void get_student(students_database_t database) {
	if (database.size == 0) { // если ещё нет записей
		printf("Ещё не было добавлено ни одного студента\n");
		return; // выходим
	}

	char id[16];
	printf("Введите номер зачётки: ");
	scanf("%[^\n]%*c", id);

	int index = find_student(database, id); // ищем студента

	if (index == -1) {
		printf("Нет такого студента\n");
		return;
	}

	printf("+-------------------+-------------------+-------------------+------------------+---------------------------+-----------------------------------------------+\n");
	printf("|   Номер зачётки   |      Фамилия      |        Имя        |     Отчество     |         Факультет         |                 Специальность                 |\n");
	printf("+-------------------+-------------------+-------------------+------------------+---------------------------+-----------------------------------------------+\n");
	printf("| %17s ", database.students[index].id);
	printf("| %17s ", database.students[index].lastname);
	printf("| %17s ", database.students[index].firstname);
	printf("| %16s ", database.students[index].patronumic);
	printf("| %25s ", database.students[index].faculty);
	printf("| %45s ", database.students[index].speciality);
	printf("|\n");
	printf("+-------------------+-------------------+-------------------+------------------+---------------------------+-----------------------------------------------+\n");
}

// сохранение базы студентов в файл
void save_students_database(students_database_t database, const char *path) {
	FILE *f = fopen(path, "w"); // открываем файл на запись

	for (int i = 0; i < database.size; i++) {
		save_student(f, database.students[i]);

		if (i < database.size - 1)
			fprintf(f, "\n");
	}

	fclose(f); // закрываем файл
}

// загрузка базы студентов из файла
students_database_t load_students_database(const char *path) {
	FILE *f = fopen(path, "r"); // открываем файл на чтение
	students_database_t database;
	database.size = 0; // обнуляем количество

	if (!f) { // если не удалось открыть файл
		database.students = NULL;
		return database; // возвращаем пустую базу
	}

	database.students = (student_t *)malloc(sizeof(student_t)); // выделяем память под один элемент

	while (!feof(f)) {
		fscanf(f, "%[^;]%*c", database.students[database.size].id);
		fscanf(f, "%[^;]%*c", database.students[database.size].lastname);
		fscanf(f, "%[^;]%*c", database.students[database.size].firstname);
		fscanf(f, "%[^;]%*c", database.students[database.size].patronumic);
		fscanf(f, "%[^;]%*c", database.students[database.size].faculty);
		fscanf(f, "%[^\n]%*c", database.students[database.size].speciality);

		database.size++; // увеличиваем размер
		database.students = (student_t *)realloc(database.students, (database.size + 1) * sizeof(student_t)); // перераспределяем память
	}

	fclose(f); // закрываем файл

	return database; // возвращаем считанный массив
}