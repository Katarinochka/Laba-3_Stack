#include <iostream>
#include <string>
#include "postfix.h"
#include "operations.h"
#include <locale>

using namespace std;

void cleaner()
{
	while (getchar() != '\n');
	cin.clear();
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int exitprog = 1; // �������� �� ����� �� ���������
	while (exitprog != 2)
	{

		cout << "\t ������������� ��������:\n\t" << Operations::str_op() << "\n\n";
		try
		{
			string expression;
			cout << "������� �������������� ���������: ";
			getline(cin, expression);
			TPostfix postfix(expression);
			cout << "\n�������������� ���������:\n" << postfix.GetStringInfix() << endl;
			cout << "\n����������� �����:\n" << postfix.GetStringPostfix() << endl;
			int exitloop = 1;
			while (exitloop != 2)
			{
				double res = postfix.Calculate();
				cout << "\n���������:\n" << res << endl;
				cout << "\n���������� ��������� ������� ����������� ����� ?\n(����������� ������� ��� ������ � ������� ���������� ����������)\n\t1 - ��\n\t2 - ���\n\t";
				cin >> exitloop;
				cleaner();
			}
			cout << "\n���������� ������������� ���������?\n\t1 - ��\n\t2 - ���\n\t";
			cin >> exitprog;
			cleaner();
			system("cls");
		}
		catch (string exc)
		{
			cout << '\n' << exc << '\n';
		}
	}
	system("�����");
	return 0;
}