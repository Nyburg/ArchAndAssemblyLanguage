// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

    // initialize result = 0
    @R2
    M=0

    // load R0 into D (multiplicand)
    @R0
    D=M
    @END
    D;JEQ

    // load R1 into D (multiplier)
    @R1
    D=M
    @END
    D;JEQ

    // store R1 in variable COUNT
    @R1
    D=M
    @COUNT
    M=D

(LOOP)
    // check if COUNT == 0
    @COUNT
    D=M
    @END
    D;JEQ

    // add R0 to R2 (R2 = R2 + R0)
    @R0
    D=M
    @R2
    M=M+D

    // decrement COUNT
    @COUNT
    M=M-1

    // loop back
    @LOOP
    0;JMP

(END)
    @END
    0;JMP