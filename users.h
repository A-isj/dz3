#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������� ��� �������� �����
typedef struct users_t {
	char login[40]; // �����
	char password[40]; // ������
	bool books; // ������ � ������
	bool students; // ������ � ���������
} users_t;

// ���� ������ ���������
typedef struct users_database_t {
	users_t *users;
	int size;
} users_database_t;

int find_login(users_database_t database, char *id); // ����� ������ ������������ �� ������
int get_menu(users_database_t database, char *login, char *password); // ��������� ���� ������������

users_database_t load_users_database(const char *path); // �������� ���� ��������� �� �����