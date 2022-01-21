#pragma once
#include <vector>

class IntCode
{ 
public:
	using memory_t = unsigned int;

	IntCode(std::vector<memory_t> ROM, bool debug = false);
	int performOp();
	void outputMemory();

private:

	struct State {
		std::vector<memory_t> Memory;
		int PC{ 0 };
		bool outputDebug{ false };
	};

	State state;

	int unknownOp();
	void printOp();
};

