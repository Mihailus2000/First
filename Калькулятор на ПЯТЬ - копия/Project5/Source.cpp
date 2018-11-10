#define _USE_MATH_DEFINES 

#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <algorithm>

 

using namespace std;

double calc(stack<string>*, int*);
bool reform(stack <string>*, stack <string>*, string);

int main()
{
	stack <string> out;
	stack <string> op;
    string expr, mod_expr = "";
	int check = true ;
	cout << "Hellow. Calculator works with degrees and unknown variable \"x\"\n\n";
    cout << "Enter the mathematical expression without \"=\"" << endl;
	getline(std::cin, expr);
	
	if (reform(&out, &op, expr)) { //разбираем строку и заполняем стек
		while (!out.empty())
		{
			op.emplace(out.top());
			out.pop();
		}
		double res = calc(&op, &check);
		if(check==1)
			cout << endl << "Result: " << res << endl;
	}
	system("pause");
    return 0;
}
 

double calc(stack<string>* out, int *check)
{
	stack <string> plus; plus.emplace("+");
	stack <string> minus; minus.emplace("-");
	stack <string> mul; mul.emplace("*");
	stack <string> dev; dev.emplace("/");
	stack <string> open; open.emplace("(");
	stack <string> close; close.emplace(")");
	stack <string> expa; expa.emplace("exp");
	stack <string> tang; tang.emplace("tg");
	stack <string> cotan; cotan.emplace("ctg");
	stack <string> sinus; sinus.emplace("sin");
	stack <string> cosin; cosin.emplace("cos");
	stack <string> ix; ix.emplace("x");

	stack <double> tmp;
	double res = 0, x = 0;
	double tmp_res=0;
	bool check_ix = false;
	*check = 1;
		while (!out->empty()) {

		if (out->top() != plus.top() && out->top() != minus.top() && out->top() != dev.top() && out->top() != mul.top()  && out->top() != expa.top() && out->top() != cosin.top() && out->top() != sinus.top() && out->top() != tang.top() && out->top() != cotan.top() && out->top() != ix.top())
		{
			tmp.emplace(atof(out->top().c_str()));
			out->pop();
			continue;
			
		}
		if (out->top() == expa.top()) {
			double tmp1 = tmp.top();
			tmp.pop();
			tmp.emplace(exp(tmp1));
			out->pop();
			continue;
		}
		if (out->top() == tang.top()) {
				double tmp1 = tmp.top();
				tmp.pop();
				if ((int)(tmp1) % 90 == 0) {
					cout << "Error: Division by zero" << endl;
					*check = 0;
					return 0;
				}
				else
					tmp.emplace(/*tan(M_PI / 180 * tmp1)*/tan(tmp1));
				out->pop();
				continue;
			}
			if (out->top() == sinus.top()) {
				double tmp1 = tmp.top();
				tmp.pop();
				tmp.emplace(/*sin(M_PI / 180 * tmp1)*/sin(tmp1));
				out->pop();
				continue;
			}
			if (out->top() == cosin.top()) {
				double tmp1 = tmp.top();
				tmp.pop();
				tmp.emplace(/*cos(M_PI) / 180 * tmp1*/ cos(tmp1));
				out->pop();
				continue;
			}
			if (out->top() == cotan.top()) {
				double tmp1 = tmp.top();
				tmp.pop();
				if ((int)(tmp1) % 180 == 0) {
					cout << "Error: Division by zero" << endl;
					*check = 0;
					return 0;
				}
				else
					tmp.emplace(pow(/*tan(M_PI / 180 * tmp1)*/tan(tmp1), -1));
				out->pop();
				continue;
			}
			if (out->top() == plus.top())
			{
				tmp_res = 0;
				if (!tmp.empty()) {
					/*if(abs(double(tmp.top()) < 1.0*pow(10,-8)))
						tmp_res = 0.;
					else*/
						tmp_res = (double)tmp.top();
					tmp.pop();
				}
				if (!tmp.empty()) {
					/*if (abs(double(tmp_res + (double)tmp.top()) < 1.0*pow(10, -8)))
						tmp_res = 0.;
					else*/
						tmp_res = tmp_res + (double)tmp.top();
						tmp.pop();
				}
				else {
					cout << "Error: No second operand" << endl;
					*check = 0;
					return 0;
				}
				tmp.emplace(tmp_res);
				out->pop();
				continue;
			}

			if (out->top() == minus.top())
			{
				tmp_res = 0;
				if (!tmp.empty()) {
					tmp_res = -(double)tmp.top();
					tmp.pop();
				}
				if (!tmp.empty()) {
					if(abs((double)tmp.top() + tmp_res) < 1.0*pow(10, -8))
						tmp_res = 0.0;
					else
						tmp_res = (double)tmp.top() + tmp_res;
					tmp.pop();
				}
				tmp.emplace(tmp_res);
				out->pop();
				continue;
			}

			if (out->top() == mul.top())
			{
				tmp_res = 0;
				if (!tmp.empty()) {
					tmp_res = (double)tmp.top();
					tmp.pop();
				}
				if (!tmp.empty()) {
					tmp_res = tmp_res * (double)tmp.top();
					tmp.pop();
				}
				else {
					cout << "Error: No second operand" << endl;
					*check = 0;
					return 0;
				}
				tmp.emplace(tmp_res);
				out->pop();
				continue;
			}
			if (out->top() == dev.top()) {
				tmp_res = 0;
				if (!tmp.empty()) {
					if (tmp.top())
						tmp_res = (double)tmp.top();
					tmp.pop();
				}
				if (!tmp.empty()) {
					if (tmp.top())
						if (tmp_res != 0) {
							tmp_res = (double)tmp.top() / tmp_res;
							tmp.pop();
							tmp.emplace(tmp_res);
						}
						else {
							cout << "Error: Division by zero" << endl;
							*check = 0;
							return 0;
						}
				}
				else {
					cout << "Error: no second operand" << endl;
					*check = 0;
					return 0;
				}
				out->pop();
				continue;
			}
			if (out->top() == "x") {
				if (check_ix == false) {
					cout << "Enter value of \'x\' : ";
					cin >> x;
					check_ix = true;
				}
				tmp.emplace(x);
				out->pop();
			}
		

	}
	if(!tmp.empty())
		return (double)tmp.top();
	else {
		cout << "Error: empty calculation" << endl;
		*check = 0;
		return 0;
	}
}
 
 
bool reform(stack<string>* out, stack<string>* op, string str)
{
	stack <string> plus; plus.emplace("+");
	stack <string> minus; minus.emplace("-");
	stack <string> mul; mul.emplace("*");
	stack <string> dev; dev.emplace("/");
	stack <string> open; open.emplace("(");
	stack <string> close; close.emplace(")");
	stack <string> expa; expa.emplace("exp"); 
	stack <string> tang; tang.emplace("tg");
	stack <string> cotan; cotan.emplace("ctg");
	stack <string> sinus; sinus.emplace("sin");
	stack <string> cosin; cosin.emplace("cos");

	bool brackets = false;
	int k = 0, num_brackets = 0;
	bool fl = false, flNum = false, fl_total = false;
	transform(str.begin(), str.end(), str.begin(), ::tolower); //!!!!!!!!!!!!!!!!!!!!!!!преобразуем к нижнему регистру
	while(k < str.length())
	{
	
		fl = false;
		flNum = false;
		string chislo = "";
		int num_point = 0;
		
		if (str[k] == '=') {
			if (fl_total == false) {
				fl_total = true;
				k++;
				fl = true;
				continue;
			}
			else {
				cout << endl << "Error found: to many equeal sign" << endl;
				return false;
			}
		}

		if (str[k] == ' ' || str[k] == '	')
		{
			str = str.erase(k, 1);
			fl = true;
			continue;
		}
		else {
			if (fl_total == true) {
				cout << endl << "Error found: equeal sign in wrong position" << endl;
				return false;
			}
			else {
				while ((str[k] >= '0' && str[k] <= '9') || str[k] == '.') {

					if (str[k] == '.')
						if (num_point == 0)
							num_point++;
						else {
							cout << "Error: more than one point per number" << endl;
							return false;
						}
					chislo += str[k];
					flNum = true;
					fl = true;
					k++;
				}

					if (flNum) {
					out->emplace(chislo);
					continue;
				}

				
				if (str[k] == 'x') {
					out->emplace("x");
					fl = true;
					k++;
					continue;
				}
				if (str[k] == 't' && str.substr(k, 3) == "tg(") {
					k += 2;
					fl = true;
					op->emplace("tg");
					continue;
				}

				if (str[k] == 's' && str.substr(k, 4) == "sin(") {
					k += 3;
					fl = true;
					op->emplace("sin");
					continue;
				}
					if (str[k] == 'c' && str.substr(k, 4) == "cos(") {
					k += 3;
					fl = true;
					op->emplace("cos");
					continue;
				}
				if (str[k] == 'c' && str.substr(k, 4) == "ctg(") {
					k += 3;
					fl = true;
					op->emplace("ctg");
					continue;
				}
				if (str[k] == 'e' && str.substr(k, 4) == "exp(") {
					k += 3;
					fl = true;
					op->emplace("exp");
					continue;
				}

				if (str[k] == '*' || str[k] == '/')
				{

					while (!op->empty() && (op->top() == dev.top() || op->top() == mul.top() || op->top() == expa.top() || op->top() == cosin.top() || op->top() == sinus.top() || op->top() == tang.top() || op->top() == cotan.top())) {
						out->emplace(op->top());
						op->pop();
					}


					string tmp = str.substr(k, 1);
					op->emplace(tmp);
					fl = true;
					k++;
					continue;
				}



				if (str[k] == '+' || str[k] == '-') {
					if (k>=1 && (str[k - 1] == '*' || str[k - 1] == '+' || str[k - 1] == '-' || str[k - 1] == '/' || str[k - 1] == '(')) {
						str.erase(k, 1);
						str.insert(k, "(0-1)*");
						num_brackets++;
					}
				while (!op->empty() && (op->top() == plus.top() || op->top() == minus.top() || op->top() == dev.top() || op->top() == mul.top() || op->top() == expa.top() || op->top() == cosin.top() || op->top() == sinus.top() || op->top() == tang.top() || op->top() == cotan.top())) {
						out->emplace(op->top());
						op->pop();
					}
					string tmp = str.substr(k, 1);
					op->emplace(tmp);
					fl = true;
					k++;
					continue;
				}



				if (str[k] == '(' ){
					if (k > 0) {
						if (k >= 3) {
							if (str[k - 1] == '*' || str[k - 1] == '-' || str[k - 1] == '/' || str[k - 1] == '+' || (str.substr(k - 3, 4) == "exp(") || (str.substr(k - 2, 3) == "tg(") || (str.substr(k - 3, 4) == "sin(") || (str.substr(k - 3, 4) == "cos(") || (str.substr(k - 3, 4) == "ctg(")) {
								brackets = true;
								num_brackets++;
								op->emplace(open.top());
								k++;
								fl = true;
								continue;
							}
							else {
								cout << "Error: syntax erroR" << endl;
								return false;
							}
						}
						if (k >= 2) {
							if (str[k - 1] == '*' || str[k - 1] == '-' || str[k - 1] == '/' || str[k - 1] == '+' || (str.substr(k - 2, 3) == "tg(")) {
								brackets = true;
								num_brackets++;
								op->emplace(open.top());
								k++;
								fl = true;
								continue;
							}
							else {
								cout << "Error: syntax erroR" << endl;
								return false;
							}
						}
						else {
								if (str[k - 1] == '*' || str[k - 1] == '-' || str[k - 1] == '/' || str[k - 1] == '+') {
									brackets = true;
									num_brackets++;
									op->emplace(open.top());
									k++;
									fl = true;
									continue;
								}
								else {
									cout << "Error: syntax erroR" << endl;
									return false;
								}
						}
					}
					else {
						brackets = true;
						num_brackets++;
						op->emplace(open.top());
						k++;
						fl = true;
						continue;
					}
				}

				if (str[k] == ')')
				{ 
					num_brackets--;
					while (!op->empty() && op->top() != open.top())
					{
						out->emplace(op->top());
						op->pop();

					}

					if (op->empty()) {
						cout << endl << "Error found: Mismatched open brackets. No open bracket" << endl;
						return false;
					}
					op->pop(); // удаление скобки
					k++;
					fl = true;
					brackets = false;
					continue;
				}
			}
		}
		k++; 
		if (fl == false) break;

	}


	if (k == 0) {
		cout << endl << "Syntax error found: Empty input" << endl;
		return false;
	}
	else
		if (fl == false) {
			cout << endl << "Syntax error found: Unknown symbols" << endl;
			return false;
		}
		
	if(!brackets && num_brackets==0)
		return true;
	else {
		cout << endl << "Syntax error found: Mismatched brackets. No close bracket"<< endl;
		return false;
	}

	
			
}