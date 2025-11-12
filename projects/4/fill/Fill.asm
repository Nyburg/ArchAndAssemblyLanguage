// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.


    @SCREEN
    D=A
    @screenStart
    M=D

    @KBD
    D=A
    @screenEnd
    M=D

(LOOP)
    @KBD
    D=M
    @BLACK
    D;JNE
    @WHITE
    0;JMP

// -------------------------
// Fill Screen Black
// -------------------------
(BLACK)
    @screenStart
    D=M
    @i
    M=D

(BLACK_LOOP)
    @i
    D=M
    @screenEnd
    D=D-M
    @END_BLACK
    D;JEQ

    @i
    A=M
    M=-1

    @i
    M=M+1
    @BLACK_LOOP
    0;JMP

(END_BLACK)
    @LOOP
    0;JMP

// -------------------------
// Fill Screen White
// -------------------------
(WHITE)
    @screenStart
    D=M
    @i
    M=D

(WHITE_LOOP)
    @i
    D=M
    @screenEnd
    D=D-M
    @END_WHITE
    D;JEQ

    @i
    A=M
    M=0

    @i
    M=M+1
    @WHITE_LOOP
    0;JMP

(END_WHITE)
    @LOOP
    0;JMP