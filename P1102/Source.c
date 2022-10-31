/*
A. Linear Search
1. n���� ������ ������ �߻����� �迭�� ����
2. ������ ���� r���� �߻���Ű��, �� ���� 1������ ������ �迭���� ���� Ž��
3. ���� Ž���� �ɸ� �ð� ����
4. �� ������ n�� 500,000���� 500,000�� ������Ű�鼭 10,000,000�� ���� �ݺ�, r�� 50�� �߻�

B. BST
A�� ������ �ݺ��ϵ�, n���� ������ ������ �߻��� �� �����ϴ� ������ �ð��� ����
n�� 500,000���� 500,000�� ������Ű�鼭 10,000,000�� ���� �ݺ�, r�� 100,000�� �߻�

C. AVL
B�� ������ ����
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "Structure.h"
#include "TickTime.h"
#include "ArrayFunction.h"
#include "BSTFunction.h"
#include "AVLFunction.h"

element random()
{
	srand(time(0) + rand());

	return rand() * rand();
}

void linear_mode(size_t count, int r, TSaver* saver)
{
	Tick insert;
	Tick find;

	// insert start
	start(&insert);

	Array* arr = create_array(count);
	for (int i = 0; i < count; i++)
	{
		write_array(arr, i, random());
	}

	// insert end
	end(&insert);

	// start timer
	start(&find);

	for (int i = 0; i < r; i++)
	{
		element num = random();

		find_array(arr, num);
	}

	// end timer
	end(&find);

	printf("Array %8d���� ������ ����: %.6llf ��, %2dȸ ���� Ž��: %.6llf ��, �� %.6llf ��\n",
		count, get_term(&insert) / (double)1000, r, get_term(&find) / (double)1000,
		(get_term(&find) + get_term(&insert)) / (double)1000);

	saver->insert = get_term(&insert);
	saver->find = get_term(&find);
}

void bst_mode(size_t count, int r, TSaver* saver)
{
	Tick insert;
	Tick search;

	// insert start
	start(&insert);

	BSTN* bst = create_BST();
	for (int i = 0; i < count; i++)
	{
		insert_BST(bst, random());
	}

	// insert end
	end(&insert);

	// start timer
	start(&search);

	for (int i = 0; i < r; i++)
	{
		element num = random();

		search_BST(bst, num);
	}

	// end timer
	end(&search);

	printf("BST %8d���� ������ ����: %.6llf ��, %6dȸ ���� Ž��: %.6llf ��, �� %.6llf ��\n",
		count, get_term(&insert) / (double)1000, r, get_term(&search) / (double)1000,
		(get_term(&search) + get_term(&insert)) / (double)1000);

	saver->insert = get_term(&insert);
	saver->find = get_term(&search);
}

void avl_mode(size_t count, int r, TSaver* saver)
{
	Tick insert;
	Tick search;

	// insert start
	start(&insert);

	AVLN* avl = create_AVL();
	for (int i = 0; i < count; i++)
	{
		insert_AVL(avl, random());
	}

	// insert end
	end(&insert);

	// start timer
	start(&search);

	for (int i = 0; i < r; i++)
	{
		element num = random();

		search_AVL(avl, num);
	}

	// end timer
	end(&search);

	printf("AVL %8d���� ������ ����: %.6llf ��, %6dȸ ���� Ž��: %.6llf ��, �� %.6llf ��\n",
		count, get_term(&insert) / (double)1000, r, get_term(&search) / (double)1000,
		(get_term(&search) + get_term(&insert)) / (double)1000);

	saver->insert = get_term(&insert);
	saver->find = get_term(&search);
}

void create_file(TSaver* data, size_t count,int mode)
{
	FILE* fp = NULL;
	char str[255] = "";
	char title[255] = "TEST-";
	
	sprintf(str, "%lld", time(0));
	strcat(title, str);
	strcat(title, ".txt");
	
	fp = fopen(title, "w");

	switch (mode)
	{
	case 1: fputs("Linear(array) mode\n", fp); break;
	case 2: fputs("BST mode\n", fp); break;
	case 3: fputs("AVL mode\n", fp); break;
	}

	for (int i = 0; i < count; i++)
	{
		sprintf(str, "%ld : %ld\n", data[i].insert, data[i].find);
		fputs(str, fp);
	}

	fclose(fp);
}

#define COUNT 20

int main()
{
	while (1)
	{
		printf("Select search mode\n 1) Linear(array)\n 2) BST\n 3) AVL\n 4) exit\n>> ");
		switch (getchar())
		{
		case '1': 
		{
			TSaver s[COUNT] = { 0 };
			
			for (int i = 1; i <= COUNT; i++)
			{
				linear_mode(i * 500000, 50, s + i - 1);
			}

			create_file(s, COUNT, 1);
			break;
		}
		case '2':
		{
			TSaver s[COUNT] = { 0 };

			for (int i = 1; i <= COUNT; i++)
			{
				bst_mode(i * 500000, 100000, s + i - 1);
			}

			create_file(s, COUNT, 2);
			break; 
		}
		case '3':
		{
			TSaver s[COUNT] = { 0 };

			for (int i = 1; i <= COUNT; i++)
			{
				avl_mode(i * 500000, 100000, s + i - 1);
			}

			create_file(s, COUNT, 3);
			break; 
		}
		case '4': return;
		}
	}
}