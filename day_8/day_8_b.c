#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_8.txt";

typedef enum opcode_t {
    JMP,
    NOP,
    ACC,
    HALT,
} opcode_t;

typedef struct instruction_t {
    opcode_t opcode;
    int64_t value;
    bool visited;
} instruction_t;

opcode_t parse_opcode_str(char* opcode_str) {
    if (strstr(opcode_str, "acc")) return ACC;
    if (strstr(opcode_str, "jmp")) return JMP;
    return NOP;
}

int64_t parse_value_str(char* value_str) {
    int64_t sign = 1;
    if (*value_str++ == '-') sign = -1;

    return sign * atoll(value_str);
}

bool program_halts(instruction_t* program_mem, int64_t* accumulator) {
    size_t pc = 0;

    while (1) {
        instruction_t* instruction = &program_mem[pc];
        if (instruction->visited) return false;
        switch (instruction->opcode) {
            case JMP:
                pc += instruction->value;
                break;
            case ACC:
                *accumulator += instruction->value;
                pc++;
                break;
            case HALT:
                return true;
                break;
            default:
                pc++;
        }
        instruction->visited = true;
    }
}

void reset_visits(instruction_t* program_mem) {
    size_t pc = 0;
    while(program_mem[pc].opcode != HALT) {
        program_mem[pc++].visited = false;
    }
}

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    instruction_t program_mem[1024];
    size_t i = 0;
    while (fgets(buffer, 128, file)) {
        char* split_point = strchr(buffer, ' ');
        *split_point = '\0';

        instruction_t instr = { 0 };
        instr.opcode = parse_opcode_str(buffer);
        instr.value = parse_value_str(split_point + 1);
        instr.visited = false;
        //printf("%zu: %d -> %lli\n", i, instr.opcode, instr.value);

        program_mem[i++] = instr;
    }
    instruction_t halting_instr = { 0 };
    halting_instr.opcode = HALT;
    program_mem[i] = halting_instr;

    size_t instruction_id = 0;
    int64_t accumulator;
    bool halts;
    do {
        reset_visits(program_mem);
        while (program_mem[instruction_id].opcode > 1) instruction_id++;

        program_mem[instruction_id].opcode = (program_mem[instruction_id].opcode + 1) % 2;
        accumulator = 0;
        halts = program_halts(program_mem, &accumulator);
        program_mem[instruction_id].opcode = (program_mem[instruction_id].opcode + 1) % 2;
        instruction_id++;
    } while (!halts);

    printf("%lli\n", accumulator);
}