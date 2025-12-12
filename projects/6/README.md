CS 271 Project 6 – Hack Assembler
Author: Nicholas Nyburg
Term: Fall 2025

Driver program:
    main.c builds the executable `assembler`.

How to build:
    From the Project 6 Directory, run: 
        make
    This compiles all necessary files and produces the executable: 
        assembler

To clean build artifacts:
    Run:
        make clean

How to run:
    ./assembler path/to/Prog.asm

Examples:
    ./assembler add/Add.asm
    ./assembler max/Max.asm
    ./assembler rect/Rect.asm
    ./assembler pong/Pong.asm

This will create:
    path/to/Prog.asm.hack

The assembler expects exactly one command-line argument
(.asm filename). If no filename is provided or the file
cannot be opened, the program prints an error message
and exits.