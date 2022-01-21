#include "IntCode.h"
#include <iostream>

IntCode::IntCode(std::vector<memory_t> ROM, bool debug) {
	// Read the ROM into memory
	state.Memory = ROM;

	// Clear the Program Counter
	state.PC = 0;

	// Set debug output 
	state.outputDebug = debug;

	// Insert an extra 4 values in case the program tries to read these somehow
	state.Memory.insert(state.Memory.end(), { 99, 99, 99, 99 });

}

int IntCode::unknownOp() {
	std::cout << "ERROR! Unknown Opcode Executed, Halting" << std::endl;
	return -1;
}

void IntCode::printOp() {
	memory_t i0 = state.Memory[state.PC + 1];
	memory_t i1 = state.Memory[state.PC + 2];
	memory_t  d = state.Memory[state.PC + 3];
	switch (state.Memory[state.PC]) {
	case 1:
		std::cout << "PC:" << state.PC << " [" << d << "] = ["
			<< i0 << "] + [" << i1 << "]" << std::endl;
		break;
	case 2:
		std::cout << "PC:" << state.PC << " [" << d << "] = ["
			<< i0 << "] * [" << i1 << "]" << std::endl;
		break;
	case 99:
		std::cout << "PC:" << state.PC << " HLT" << std::endl;
		break;
	default:
		std::cout << "PC:" << state.PC << " ???" << std::endl;
		break;
	}
}

int IntCode::performOp() {
	// If Debug Output is enabled, print the OP
	if (state.outputDebug) printOp();

	switch (state.Memory[state.PC]) {
		case 1:
			// ADD OPCODE
			state.Memory[state.Memory[state.PC + 3]] = 
				(state.Memory[state.Memory[state.PC + 1]] + state.Memory[state.Memory[state.PC + 2]]);
			state.PC += 4;
			return 0;
		case 2:
			// MUL OPCODE
			state.Memory[state.Memory[state.PC + 3]] =
				(state.Memory[state.Memory[state.PC + 1]] * state.Memory[state.Memory[state.PC + 2]]);
			state.PC += 4;
			return 0;
		case 99:
			// HLT OPCODE
			std::cout << "Halting Execution, Opcode 99 Found" << std::endl;
			return 1;
		default:
			// How did we get here?
			return unknownOp();
	}
}

void IntCode::outputMemory() {
	std::cout << "OUTPUTTING MEMORY\nPC: " << state.PC << "\n";
	for (memory_t i : state.Memory) {
		std::cout << i << ",";
	}
	std::cout << "\nEND OF MEMORY" << std::endl;
}