#include <iostream>

namespace CalculatorCLI
{
	constexpr char NUM = 'n';
	constexpr char QUIT = 'q';
	constexpr char CALC = ';';

	struct Token
	{
		char kind = NUM;
		double value = 0.0;
	} token;  // both definition and declaration here

	Token get_token()
	{
		char kind;
		std::cin >> kind;
		switch (kind)
		{
		case QUIT:
		case CALC:
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		{
			return Token{ kind, 0.0 };
		}
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			std::cin.unget();
			double value;
			std::cin >> value;
			return Token{ NUM, value };
		}
		default:
		{
			std::cout << "Bad input. Please try again.\n";
			return Token{ QUIT, 0.0 };
		}
		}  // end switch
	}

	double expression();

	double primary()
	{
		token.kind = NUM;
		for (double temp = 0.0; token.kind != QUIT;)
		{
			switch (token.kind)
			{
			case NUM:
			{
				temp = token.value;
				[[fallthrough]];
			}
			case ')':
			{
				token = get_token();
				break;
			}
			case '(':
			{
				return expression();
			}
			default:
			{
				return temp;
			}
			}  // end switch
		}
		return 0.0;
	}

	double term()
	{
		for (double temp = primary(); token.kind != QUIT;)
		{
			switch (token.kind)
			{
			case '*':
			{
				temp *= primary();
				break;
			}
			case '/':
			{
				double x = primary();
				if (fabs(x) > 1e-15)
				{
					temp /= x;
				}
				else
				{
					std::cout << "Can't be divided by zero!";
					token.kind = QUIT;
				}
				break;
			}
			default:
			{
				return temp;
			}
			}  // end switch
		}
		return 0.0;
	}

	double expression()
	{
		for (double temp = term(); token.kind != QUIT;)
		{
			switch (token.kind)
			{
			case '+':
			{
				temp += term();
				break;
			}
			case '-':
			{
				temp -= term();
				break;
			}
			default:
			{
				return temp;
			}
			}  // end switch
		}
		return 0.0;
	}

	void calculate()
	{
		std::cout
			<< "CalculatorCLI v0.1 by kongolou.\n"
			<< "\"That's when I read a book of Bjarne Stroustrup.\"\n\n"
			<< CALC
			<< " to end an expression to calculate and "
			<< QUIT
			<< " or any bug key to quit. :)\n\n"
			<< "\n[Grammar]\n\n"
			<< "Expression:\n"
			<< "  Term\n"
			<< "  Expression\"+\"Term\n"
			<< "  Expression\"-\"Term\n"
			<< "Term:\n"
			<< "  Primary\n"
			<< "  Term\"*\"Primary\n"
			<< "  Term\"/\"Primary\n"
			<< "Primary:\n"
			<< "  number\n"
			<< "  \"(\"Expression\")\""
			<< "\n\n[Example]\n\n"
			<< "> 2-(-3/5);\n"
			<< "= 2.6\n"
			<< "\n[Test]\n";
		for (double result = 0.0; token.kind != QUIT;)
		{
			std::cout << "\n> ";
			result = expression();
			if (token.kind == CALC)
			{
				std::cout << "= " << result;
			}
		}
	}
}

int main()
{
	CalculatorCLI::calculate();
	return 0;
}
