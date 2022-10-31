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

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
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

void linear_mode(size_t count, int r, long* find)
{
	// insert
	Array* arr = create_array(count);
	for (int i = 0; i < count; i++)
	{
		write_array(arr, i, random());
	}

	Tick tick;
	
	// start timer
	start(&tick);

	for (int i = 0; i < r; i++)
	{
		element num = random();

		find_array(arr, num);
	}

	// end timer
	end(&tick);

	printf("�迭 %8d���� �����Ϳ��� %2dȸ ���� Ž��: %.6llf ��\n", count, r, get_term(&tick) / (double)1000);

	*find = get_term(&tick) / r;
}

void bst_mode(size_t count, int r, long* create, long* find)
{
	Tick insert;
	Tick tick;

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
	start(&tick);

	for (int i = 0; i < r; i++)
	{
		element num = random();

		search_BST(bst, num);
	}

	// end timer
	end(&tick);

	printf("BST %8d���� ������ ����: %.6llf ��, %6dȸ ���� Ž��: %.6llf ��, �� %.6llf ��\n",
		count, get_term(&insert) / (double)1000, r, get_term(&tick) / (double)1000,
		(get_term(&tick) + get_term(&insert)) / (double)1000);

	*create = get_term(&insert);
	*find = get_term(&tick);
}

void avl_mode(size_t count, int r, long* create, long* find)
{
	Tick insert;
	Tick tick;

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
	start(&tick);

	for (int i = 0; i < r; i++)
	{
		element num = random();

		search_AVL(avl, num);
	}

	// end timer
	end(&tick);

	printf("AVL %8d���� ������ ����: %.6llf ��, %6dȸ ���� Ž��: %.6llf ��, �� %.6llf ��\n",
		count, get_term(&insert) / (double)1000, r, get_term(&tick) / (double)1000,
		(get_term(&tick) + get_term(&insert)) / (double)1000);

	*create = get_term(&insert);
	*find = get_term(&tick);
}

int main()
{
	while (1)
	{
		printf("Select search mode\n 1) Linear(array)\n 2) BST\n 3) AVL\n 4) exit\n>> ");
		switch (getchar())
		{
		case '1': 
		{
			long find[20] = {0};
			
			for (int i = 1; i <= 20; i++)
			{
				linear_mode(i * 500000, 50, find + i - 1);
			}

			break;
		}
		case '2':
		{
			long create[20] = { 0 };
			long find[20] = { 0 };

			for (int i = 1; i <= 20; i++)
			{
				bst_mode(i * 500000, 100000, create + i - 1, find + i - 1);
			}

			break;
		}
		case '3':
		{
			long create[20] = { 0 };
			long find[20] = { 0 };

			for (int i = 1; i <= 20; i++)
			{
				avl_mode(i * 500000, 100000, create + i - 1, find + i - 1);
			}

			break;
		}
		case '4': return;
		}
	}
}