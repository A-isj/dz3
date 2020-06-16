#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// структура для хранения полей
typedef struct book_t {
	char isbn[16]; // номер книги
	char authors[40]; // фио авторов
	char title[25]; // название книги
	int count; // количество всего
	int available; // доступно книг
} book_t;

typedef struct books_database_t {
	book_t *books; // массив книг
	int size; // количество книг
} books_database_t;

book_t read_book(char *isbn); // считывание книги
void print_book(book_t book); // вывод книги
void save_book(FILE *f, book_t book);

void print_books(books_database_t database); // вывод книг в виде таблицы
void print_book_by_isbn(book_t *books, int n); // вывод книги по номеру

int find_book(books_database_t database, char *isbn); // получение индекса книги по номеру
void add_book(books_database_t *database); // добавление новой записи
void remove_book(books_database_t *database); // удаление книги по isbn
void edit_book(books_database_t *database); // редактирование книги по isbn
void edit_book_count(books_database_t *database); // редактирование количество книг по isbn

void save_books_database(books_database_t, const char *path); // сохранение базы данных в файл
books_database_t load_books_database(const char *path); // загрузка базы данных из файла