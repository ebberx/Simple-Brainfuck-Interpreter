#include <iostream>
#include <stack>
#include <string>

void increment_pointer();
void decrement_pointer();
void increment_cell();
void decrement_cell();
void input();
void output();

unsigned char cells[255];
int cp_pos = 0;

int main(int argc, char* argv[]) {

	std::string code = ">++++++++[<+++++++++>-]<.>++++[<++++++ + >-]<+.++++++ + ..+++.>> ++++++[<++++++ + >-]<++.------------.>++++++[<++++++++ + >-]<+.<.++ + .------.--------.>>>++++[<++++++++>-]<+.";

	// initialize cells to zero
	for (int i = 0; i < sizeof(cells); i++) {
		cells[i] = 0;
	}

	int ip = 0;
	std::stack<int> stack;
	printf("ip: %d size: %d\n", ip, code.size());
	while (ip < code.size()) {
		char c = code[ip];
		//printf("C: %c\n", c);
		switch (c) {
		case '>':
			increment_pointer();
			break;
		case '<':
			decrement_pointer();
			break;
		case '+':
			increment_cell();
			break;
		case '-':
			decrement_cell();
			break;
		case '[':
			stack.push(ip);
			//printf("Stack size: %d\n", stack.size());
			break;
		case ']':
			if (stack.empty()) { printf("Syntax error\n"); return -1; }
			if (cells[cp_pos] != 0)	
				ip = stack.top();
			else 
				stack.pop();
			break;
		case ',':
			input();
			break;
		case '.':
			output();
			break;
		default:
			break;
		}
		ip++;
	}
	return 0;
}

void increment_pointer() {
	if (cp_pos == sizeof(cells) - 1) {
		cp_pos = 0;
		return;
	}
	cp_pos++;
}

void decrement_pointer() {
	if (cp_pos == 0) {
		cp_pos = sizeof(cells)-1;
		return;
	}
	cp_pos--;
}

void increment_cell() {
	cells[cp_pos]++;
}

void decrement_cell() {
	cells[cp_pos]--;
}

void input() {
	cells[cp_pos] = getchar();
}

void output() {
	putchar(cells[cp_pos]);
}
