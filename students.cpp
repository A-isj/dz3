#define _CRT_SECURE_NO_WARNINGS
#include "students.h"

// ���������� ����� ���������
student_t read_student(char *id) {
	student_t student; // ������ ���������

	// ��������� ����
	strcpy(student.id, id); // ��������� ����� �������� ������

	printf("������� �������: ");
	scanf("%[^\n]%*c", student.lastname); // ��������� �������

	printf("������� ���: ");
	scanf("%[^\n]%*c", student.firstname); // ��������� ���

	printf("������� ��������: ");
	scanf("%[^\n]%*c", student.patronumic); // ��������� ��������

	printf("������� �������� ����������: ");
	scanf("%[^\n]%*c", student.faculty); // ��������� ���������

	printf("������� �������������: ");
	scanf("%[^\n]%*c", student.speciality); // ��������� �������������

	return student; // ���������� ��������� ���������
}

// ���������� �������� � ����
void save_student(FILE *f, student_t student) {
	fprintf(f, "%s;", student.id);
	fprintf(f, "%s;", student.lastname);
	fprintf(f, "%s;", student.firstname);
	fprintf(f, "%s;", student.patronumic);
	fprintf(f, "%s;", student.faculty);
	fprintf(f, "%s", student.speciality);
}

// ��������� ������� �������� �� ������ �������� ������
int find_student(students_database_t database, char *id) {
	// ���� ����� �� ������
	for (int i = 0; i < database.size; i++)
		if (!strcmp(id, database.students[i].id))
			return i;

	return -1; // �� �����
}

// ���������� ����� ������
void add_student(students_database_t *database) {
	char id[17];
	printf("������� ����� �������: ");
	scanf("%[^\n]%*c", id);

	while (find_student(*database, id) != -1) { // ���� ������� � ����� ������� ��� ����
		printf("������� � ����� �������� ��� ����, ��������� ����: "); // �������� �� ����
		scanf("%[^\n]", id);
	}

	database->students = (student_t *)realloc(database->students, (database->size + 1) * sizeof(student_t)); // ���������������� ������
	printf("������� ���������� � ��������\n");
	database->students[database->size++] = read_student(id); // ��������� ����
}

// �������� �������� �� ������
void remove_student(students_database_t *database) {
	if (database->size == 0) { // ���� ��� ��� �������
		printf("��� �� ���� ��������� �� ������ ��������\n");
		return; // �������
	}

	char id[16];
	printf("������� ����� �������: ");
	scanf("%[^\n]%*c", id);

	int index = find_student(*database, id); // ���� ����� �� ������

	// ���� �� �����
	if (index == -1) {
		printf("��� �������� � ����� ������� �������\n"); // �������� �� ����
		return; // � �������
	}

	// �������� ����� �����
	for (database->size--; index < database->size; index++)
		database->students[index] = database->students[index + 1];
}

// �������������� ������
void edit_student(students_database_t *database) {
	if (database->size == 0) { // ���� ��� ��� �������
		printf("��� �� ���� ��������� �� ������ ��������\n");
		return; // �������
	}

	char id[16];
	printf("������� ����� �������: ");
	scanf("%[^\n]%*c", id);

	int index = find_student(*database, id); // ���� ��������

	if (index == -1) {
		printf("��� ������ ��������\n");
		return;
	}

	printf("������� ����� ���������� �� ���� ��������:\n");
	database->students[index] = read_student(id); // ��������� ����� ������
}

// ����� ��������
void get_student(students_database_t database) {
	if (database.size == 0) { // ���� ��� ��� �������
		printf("��� �� ���� ��������� �� ������ ��������\n");
		return; // �������
	}

	char id[16];
	printf("������� ����� �������: ");
	scanf("%[^\n]%*c", id);

	int index = find_student(database, id); // ���� ��������

	if (index == -1) {
		printf("��� ������ ��������\n");
		return;
	}

	printf("+-------------------+-------------------+-------------------+------------------+---------------------------+-----------------------------------------------+\n");
	printf("|   ����� �������   |      �������      |        ���        |     ��������     |         ���������         |                 �������������                 |\n");
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

// ���������� ���� ��������� � ����
void save_students_database(students_database_t database, const char *path) {
	FILE *f = fopen(path, "w"); // ��������� ���� �� ������

	for (int i = 0; i < database.size; i++) {
		save_student(f, database.students[i]);

		if (i < database.size - 1)
			fprintf(f, "\n");
	}

	fclose(f); // ��������� ����
}

// �������� ���� ��������� �� �����
students_database_t load_students_database(const char *path) {
	FILE *f = fopen(path, "r"); // ��������� ���� �� ������
	students_database_t database;
	database.size = 0; // �������� ����������

	if (!f) { // ���� �� ������� ������� ����
		database.students = NULL;
		return database; // ���������� ������ ����
	}

	database.students = (student_t *)malloc(sizeof(student_t)); // �������� ������ ��� ���� �������

	while (!feof(f)) {
		fscanf(f, "%[^;]%*c", database.students[database.size].id);
		fscanf(f, "%[^;]%*c", database.students[database.size].lastname);
		fscanf(f, "%[^;]%*c", database.students[database.size].firstname);
		fscanf(f, "%[^;]%*c", database.students[database.size].patronumic);
		fscanf(f, "%[^;]%*c", database.students[database.size].faculty);
		fscanf(f, "%[^\n]%*c", database.students[database.size].speciality);

		database.size++; // ����������� ������
		database.students = (student_t *)realloc(database.students, (database.size + 1) * sizeof(student_t)); // ���������������� ������
	}

	fclose(f); // ��������� ����

	return database; // ���������� ��������� ������
}