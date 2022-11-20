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
	int exitprog = 1; // Проверка на выход из программы
	while (exitprog != 2)
	{

		cout << "\t Подерживаемые операции:\n\t" << Operations::str_op() << "\n\n";
		try
		{
			string expression;
			cout << "Введите арифметическое выражение: ";
			getline(cin, expression);
			TPostfix postfix(expression);
			cout << "\nАрифметическое выражение:\n" << postfix.GetStringInfix() << endl;
			cout << "\nПостфиксная форма:\n" << postfix.GetStringPostfix() << endl;
			int exitloop = 1;
			while (exitloop != 2)
			{
				double res = postfix.Calculate();
				cout << "\nРезультат:\n" << res << endl;
				cout << "\nПродолжить обработку текущей постфиксной формы ?\n(специальная функция для работы с другими значениями переменных)\n\t1 - да\n\t2 - Нет\n\t";
				cin >> exitloop;
				cleaner();
			}
			cout << "\nПродолжить использование программы?\n\t1 - Да\n\t2 - Нет\n\t";
			cin >> exitprog;
			cleaner();
			system("cls");
		}
		catch (string exc)
		{
			cout << '\n' << exc << '\n';
		}
	}
	system("Пауза");
	return 0;
}