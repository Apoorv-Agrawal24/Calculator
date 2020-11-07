#include "solve.h"


std::vector<Token> Solve::lexer(const std::string expression)
{
	std::vector<Token> tokens;
	Token addToken;
	std::string curNum;

	for (char character : expression)
	{

		switch(character)
		{
			case '+':
				if (curNum != "")
				{
					addToken.type = Type::NUM;
					addToken.value = std::stoll(curNum);
					std::cout << addToken.value << std::endl;
					tokens.push_back(addToken);
				}

				addToken.type = Type::ADD;
				addToken.value = 0;
				tokens.push_back(addToken);

				curNum = "";
				break;
			case '-':
				if (curNum != "")
				{
					addToken.type = Type::NUM;
					addToken.value = std::stoll(curNum);
					tokens.push_back(addToken);
				}

				addToken.type = Type::SUB;
				addToken.value = 0;
				tokens.push_back(addToken);

				curNum = "";
				break;
			case '/':
				if (curNum != "")
				{
					addToken.type = Type::NUM;
					addToken.value = std::stoll(curNum);
					tokens.push_back(addToken);
				}

				addToken.type = Type::DIV;
				addToken.value = 0;
				tokens.push_back(addToken);

				curNum = "";
				break;
			case '*':
				if (curNum != "")
				{
					addToken.type = Type::NUM;
					addToken.value = std::stoll(curNum);
					tokens.push_back(addToken);
				}

				addToken.type = Type::MUL;
				addToken.value = 0;
				tokens.push_back(addToken);

				curNum = "";				
				break;
			
			case '(':
				addToken.type = Type::LPAREN;
				addToken.value = 0;
				tokens.push_back(addToken);
				
				curNum = "";
				break;

			case ')':
				if (curNum != "")
				{
					addToken.type = Type::NUM;
					addToken.value = std::stoll(curNum);
					tokens.push_back(addToken);
				}	
				addToken.type = Type::RPAREN;
				addToken.value = 0;
				tokens.push_back(addToken);
				
				curNum = "";
				break;
		
			default:
				if (isNum(character))
				{
					curNum += character;
				}
		}

	}

	if (curNum != "")
	{
		addToken.type = Type::NUM;
		addToken.value = std::stoll(curNum);
		tokens.push_back(addToken);
	} 

	return tokens;
}

void Solve::show(std::vector<Token> tokens)
{
	for (Token tok : tokens)
		{
			std::cout << '\'' << tok.value << '\'' << std::endl;
		}
}

std::vector<Token> Solve::infix(std::vector<Token> tokens)
{
	std::vector<Token> queue;
	std::stack<Token> stack;

	for (Token token : tokens)
	{
		std::cout << token.value << " ";
		if (token.type == Type::LPAREN)
		{
			stack.push(token);
		}

		else if (token.type == Type::RPAREN)
		{
			while (stack.top().type != Type::LPAREN)
			{
				queue.push_back(stack.top());
				stack.pop();
			}
			stack.pop();
		}

		else if (token.type == Type::ADD || token.type == Type::SUB || token.type == Type::MUL || token.type == Type::DIV)
		{
			if (stack.empty())
			{
				stack.push(token);
			} 
	        else
	        {
	            //if literal is operand, put it on to f
				{
					if (precedence(stack.top().type) >= precedence(token.type))
					{
						queue.push_back(stack.top());
						stack.pop();
						stack.push(token);
					}
					else 
					{
						stack.push(token);
					}
				}
			}
		}
		else
		{
			queue.push_back(token);	
		}
	}

    if(!stack.empty())
    {
        while(!stack.empty())
        {
            queue.push_back(stack.top());
            stack.pop();
        }
    }

    show(queue);
	return queue;
}

std::stack<Token> Solve::eval(const std::vector<Token> tokens)
{
	std::stack<Token> nums;
	Token num1;
	Token num2;
	Token num3;

	for (Token token : tokens)
	{
		if (token.type == Type::NUM)
		{
			nums.push(token);
		}

		else if (token.type == Type::ADD)
		{
			num1 = nums.top();
			nums.pop();
			num2 = nums.top();
			nums.pop();
			num3 = num1 + num2;
			nums.push(num3);
		}

		else if (token.type == Type::SUB)
		{
			num1 = nums.top();
			nums.pop();
			num2 = nums.top();
			nums.pop();
			num3 = num1 - num2;
			nums.push(num3);
		}

		else if (token.type == Type::MUL)
		{
			num1 = nums.top();
			nums.pop();
			num2 = nums.top();
			nums.pop();
			num3 = num1 * num2;
			nums.push(num3);
		}

		else if (token.type == Type::DIV)
		{
			num1 = nums.top();
			nums.pop();
			num2 = nums.top();
			nums.pop();
			num3 = num1 / num2;
			nums.push(num3);
		}

	}
	std::cout << nums.top().value << std::endl;
	return nums;
}


bool Solve::isNum(const char testNum)
{
	const std::string nums = "1234567890";

	for (char num : nums)
	{
		if (testNum == num)
		{
			return true;
		}
	}

	return false;
}

int Solve::precedence(Type symbol)
{
	if(symbol == Type::MUL || symbol == Type::DIV)
	{
		return(2);
	}
	else if(symbol == Type::ADD || symbol == Type::SUB)          /* lowest precedence */
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

