#define _CRT_SECURE_NO_WARNINGS
#include "books.h"

// считывание полей структуры
book_t read_book(char *isbn) {
	book_t book; // создаём структуру

	strcpy(book.isbn, isbn); // запоминаем номер

	printf("Введите авторов: ");
	scanf("%[^\n]%*c", book.authors); // считываем фио авторов

	printf("Введите название книги: ");
	scanf("%[^\n]%*c", book.title); // считываем название книги

	printf("Введите количество книг всего: ");
	scanf("%d%*c", &book.count); // считываем количество всего

	printf("Введите количество доступных книг: ");
	scanf("%d%*c", &book.available); // считываем сколько всего доступно книг

	return book; // возвращаем книгу
}

// вывод структуры
void print_book(book_t book) {
	printf("| %16s ", book.isbn);
	printf("| %40s ", book.authors);
	printf("| %24s ", book.title);
	printf("| %10d ", book.count);
	printf("| %10d ", book.available);
	printf("|\n");
}

// сохранение книги в файл
void save_book(FILE *f, book_t book) {
	fprintf(f, "%s;", book.isbn);
	fprintf(f, "%s;", book.authors);
	fprintf(f, "%s;", book.title);
	fprintf(f, "%d;", book.count);
	fprintf(f, "%d", book.available);
}

// вывод базы данных
void print_books(books_database_t database) {
	if (database.size == 0) { // если ещё нет записей
		printf("No book was added yet\n"); // сообщаем об этом
		return; // выходим
	}

	printf("+------------------+------------------------------------------+--------------------------+------------+------------+\n");
	printf("|       ISBN       |                  Авторы                  |         Название         | Количество |  Доступно  |\n");
	printf("+------------------+------------------------------------------+--------------------------+------------+------------+\n");

	for (int i = 0; i < database.size; i++)
		print_book(database.books[i]);

	printf("+------------------+------------------------------------------+--------------------------+------------+------------+\n");
}

// получение индекса книги по номеру
int find_book(books_database_t database, char *isbn) {
	// ищем книгу по номеру
	for (int i = 0; i < database.size; i++)
		if (!strcmp(isbn, database.books[i].isbn))
			return i;

	return -1; // не нашли
}

// добавление новой книги
void add_book(books_database_t *database) {
	char isbn[16];
	printf("Введите ISBN: ");
	scanf("%[^\n]%*c", isbn); // считываем поле для поиска

	while (find_book(*database, isbn) != -1) { // если книга с таким номером уже есть
		printf("Книга с таким ISBN уже есть, введите другой ISBN: "); // сообщаем об этом
		scanf("%[^\n]", isbn); // считываем поле для поиска
	}

	database->books = (book_t *)realloc(database->books, (database->size + 1) * sizeof(book_t)); // перераспределяем память
	printf("Введите информацию о новой книге\n");
	database->books[database->size++] = read_book(isbn); // записываем книгу в массив
}

// удаление книги по isbn
void remove_book(books_database_t *database) {
	char isbn[16];
	printf("Введите ISBN: ");
	scanf("%[^\n]%*c", isbn); // считываем поле для поиска

	int index = find_book(*database, isbn); // ищем книгу по номеру

	// если не нашли
	if (index == -1) {
		printf("Нет книги с таким номером\n"); // сообщаем об этом
		return; // и выходим
	}

	// сдвигаем книги влево
	for (database->size--; index < database->size; index++)
		database->books[index] = database->books[index + 1];
}

// редактирование книги по isbn
void edit_book(books_database_t *database) {
	char isbn[16];
	printf("Введите ISBN: ");
	scanf("%[^\n]%*c", isbn); // считываем поле для поиска

	int index = find_book(*database, isbn); // ищем книгу по номеру

	// если не нашли
	if (index == -1) {
		printf("Нет книги с таким номером\n"); // сообщаем об этом
		return; // и выходим
	}

	printf("Введите новые данные об этой книге\n");
	database->books[index] = read_book(isbn); // редактируем запись
}

// редактирование количество книг по isbn
void edit_book_count(books_database_t *database) {
	char isbn[16];
	printf("Введите ISBN: ");
	scanf("%[^\n]%*c", isbn); // считываем поле для поиска

	int index = find_book(*database, isbn); // ищем книгу по номеру

	// если не нашли
	if (index == -1) {
		printf("Нет книги с таким номером\n"); // сообщаем об этом
		return; // и выходим
	}

	printf("Введите новое количество книг: ");
	scanf("%d%*c", &database->books[index].count);

	if (database->books[index].count < database->books[index].available)
		database->books[index].available = database->books[index].count;
}

// сохранение базы данных в файл
void save_books_database(books_database_t database, const char *path) {
	FILE *f = fopen(path, "w"); // открываем файл на запись

	for (int i = 0; i < database.size; i++) {
		save_book(f, database.books[i]);

		if (i < database.size - 1)
			fprintf(f, "\n");
	}

	fclose(f); // закрываем файл
}

// загрузка базы данных из файла
books_database_t load_books_database(const char *path) {
	FILE *f = fopen(path, "r"); // открываем файл на чтение
	books_database_t database;

	if (!f) { // если не удалось открыть файл
		database.size = 0; // обнуляем количество
		database.books = NULL;
		return database;
	}

	database.books = (book_t *)malloc(sizeof(book_t)); // выделяем память под один элемент
	database.size = 0; // изначально элементов нет

	while (!feof(f)) {
		fscanf(f, "%[^;]%*c", database.books[database.size].isbn);
		fscanf(f, "%[^;]%*c", database.books[database.size].authors);
		fscanf(f, "%[^;]%*c", database.books[database.size].title);
		fscanf(f, "%d%*c", &database.books[database.size].count);
		fscanf(f, "%d%*c", &database.books[database.size].available);

		database.size++; // увеличиваем размер
		database.books = (book_t *)realloc(database.books, (database.size + 1) * sizeof(book_t)); // перераспределяем память
	}

	fclose(f); // закрываем файл
	return database; // возвращаем базу данных
}