#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// структура дл€ хранени€ полей
typedef struct student_t {
	char id[17]; // номер зачЄтной книжки
	char lastname[17]; // фамили€
	char firstname[17]; // им€
	char patronumic[16]; // отчество
	char faculty[25]; // факультет
	char speciality[45]; // специальность
} student_t;

// база данных студентов
typedef struct students_database_t {
	student_t *students;
	int size;
} students_database_t;

student_t read_student(char *id); // считывание полей структуры

int find_student(students_database_t database, char *id); // получение индекса студента по номеру зачЄтной книжки
void add_student(students_database_t *database); // добавление новой записи
void remove_student(students_database_t *database); // удаление студента по номеру
void edit_student(students_database_t *database); // редактирование записи
void get_student(students_database_t database); // поиск студента по номеру

void save_students_database(students_database_t database, const char *path); // сохранение базы студентов в файл
students_database_t load_students_database(const char *path); // загрузка базы студентов из файла