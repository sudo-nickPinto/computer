// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/DMux16.tst

load DMux16.hdl,
output-file DMux16.out,
compare-to DMux16.cmp,
output-list in%B1.16.1 sel a%B1.16.1 b%B1.16.1;

set in 0,
set sel 0,
eval,
output;

set sel 1,
eval,
output;

set in %B0001001000110100,
set sel 0,
eval,
output;

set sel 1,
eval,
output;

set in %B1001100001110110,
set sel 0,
eval,
output;

set sel 1,
eval,
output;

set in %B1010101010101010,
set sel 0,
eval,
output;

set sel 1,
eval,
output;
