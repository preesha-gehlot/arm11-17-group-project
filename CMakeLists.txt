cmake_minimum_required(VERSION 3.22)
project(arm11_17 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(testing/lib/json_pure-1.5.3/ext/json/ext/generator)
include_directories(testing/lib/json_pure-1.5.3/ext/json/ext/parser)

add_executable(arm11_17
        src/emulator/branch_instruction.c
        src/emulator/emulate_main.c
        src/emulator/emulator_cspr.c
        src/emulator/emulator_dataprocessing.c
        src/emulator/emulator_decode.c
        src/emulator/emulator_fetch.c
        src/emulator/emulator_io.c
        src/emulator/multiply_instruction.c
        src/emulator/single_data_transfer_instruction.c
        src/assemble.c
        src/definitions.h
        src/emulate.c
        src/utils.c
        testing/lib/json_pure-1.5.3/ext/json/ext/generator/generator.c
        testing/lib/json_pure-1.5.3/ext/json/ext/generator/generator.h
        testing/lib/json_pure-1.5.3/ext/json/ext/parser/parser.c
        testing/lib/json_pure-1.5.3/ext/json/ext/parser/parser.h src/assembler/symbol_table.h src/assembler/assemble_sdt.c src/assembler/assemble_sdt.h src/assembler/assemble_branch.c src/assembler/assemble_branch.h)
