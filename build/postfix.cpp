#include <iostream>
#include <string>
#include "postfix.h"
#include "stack.h"
#include "operations.h"
#include <locale>

using namespace std;

bool TPostfix::BracketsCorrect(string& str) const
{
	TStack<bool> stack; // ���� ��� �������� ������� '('
	for (const char& elem : str)
	{
		if (elem == '(')
		{
			stack.push(true);
			continue;
		}
		if (elem == ')')
		{
			if (stack.empty()) // ���� ���� ����, �� ��� ���� ��� ')' -> ������
				return false;
			stack.pop();
			continue;
		}
	}
	if (!stack.empty()) // ���� ���� �� ����, �� ������� ���� ')' -> ������
		return false;
	return true;
}

void TPostfix::ToInfix(string& str)
{
	string elem;
	Operations op;
	for (int i = 0; i < str.size();)
	{
		string tmp;
		elem = str[i];

		if (op.IsOperation(elem))
		{
			tmp = elem;
			i++;
		}
		else
		{
			while (!op.IsOperation(elem) && i < str.size())
			{
				if (elem != " ")
					tmp += elem;
				elem = str[++i];
			}
		}

		if ((tmp == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // ����������� �������� ������ � ��������
			infix.push_back("0");

		if (tmp.find_first_of("0123456789") == 0 && tmp.find_first_not_of("0123456789.") != string::npos) // �������� �� ������������ ����� ����������, ���� ��� ����������
		{
			string exc = "Invalid format of variable: " + tmp;
			throw exc;
		}

		if (tmp.size() != 0)
			infix.push_back(tmp);
	}
}

void TPostfix::ToPostfix()
{
	Operations op;
	TStack<string> opstack;

	for (int i = 0; i < infix.size(); i++)
	{
		string tmp = infix[i];
		if (!op.IsOperation(tmp))
		{
			postfix.push_back(tmp);
			continue;
		}
		else
		{
			if (tmp == "(")
			{
				opstack.push(tmp);
				continue;
			}

			if (tmp == ")")
			{
				while (opstack.tos() != "(")
					postfix.push_back(opstack.pop());
				opstack.pop();
				continue;
			}

			while (!opstack.empty() && op.GetPriority(opstack.tos()) >= op.GetPriority(tmp))
				postfix.push_back(opstack.pop());

			if (opstack.empty())
			{
				opstack.push(tmp);
				continue;
			}
			else
			{
				if (op.GetPriority(opstack.tos()) < op.GetPriority(tmp))
				{
					opstack.push(tmp);
					continue;
				}
			}
		}
	}
	while (!opstack.empty())
		postfix.push_back(opstack.pop());
}

vector<string> TPostfix::GetVecOfVariables() const
{
	Operations op;
	vector<string> tmp;
	for (const string& elem : postfix)
	{
		if (elem.find_first_not_of("0123456789") == 0 && !op.IsOperation(elem))
		{
			int different = 0;
			for (const string& element : tmp) // ���� tmp.size() == 0, �� �� ��������� �� ����� �������� � ��������� different == 0 -> ��������� ������ �������
				if (element != elem)
					different++;
			if (different == tmp.size())
				tmp.push_back(elem);
		}
	}
	return tmp;
}

double TPostfix::Calculate(bool interface, vector<double> vecofvalues) const // �� ��������� interface == true, vecofvalues == {}
{
	map<string, double> values;
	vector<string> variables = GetVecOfVariables();
	if (interface)
	{
		if (variables.size() > 0)
		{
			cout << "\nEnter the values of the undefined variables:\n";
			for (string& elem : variables)
			{
				double value;
				cout << "\t" << elem << " = ";
				cin >> value;
				values.emplace(elem, value);
			}
		}
	}
	else
	{
		if (variables.size() != vecofvalues.size())
			throw string("Arrays of names and values have different sizes");
		for (int i = 0; i < variables.size(); i++)
			values.emplace(variables[i], vecofvalues[i]);
	}

	double res = 0;
	TStack<double> arguments;
	Operations op;
	for (const string& elem : postfix)
	{
		if (!op.IsOperation(elem))
		{
			if (find(variables.begin(), variables.end(), elem) != variables.end()) // ���� elem - ����������
				arguments.push(values[elem]);
			else
				arguments.push(stod(elem));
		}
		else
		{
			if (op.GetArity(elem) == 1)
				arguments.push(op.Calc(elem, arguments.pop())); // ������� ��� ���������� ��������� ��������
			else // if (op.GetArity(elem) == 2), �.�. � postfix ��� ������
				arguments.push(op.Calc(elem, arguments.pop(), arguments.pop())); // ������� ��� ���������� ��������� ��� ��������
		}
	}
	res = arguments.pop(); // ��������� ������� � ����� - �����
	return res;
}