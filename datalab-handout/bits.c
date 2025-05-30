/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // x^y -> (x&~y) | (~x&y)
  // we use morgan's law to deal with "|"
  // x|y =  ~(-x&~y)
  return ~((~(~x&y))&(~(x&~y)));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // the idea is: Tmax is: 0111 1111(in 8-bit case), shift 1 bit to the left, then +1, you get 1111 1111
  // then +1, we get 0000 0000. that is !(~(x+x+1)) .
  // but if x = 1111 1111, we still get 0000 0000. so & !!(~x) can fix it. 
  return !(~(x+x+1)) & !!(~x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int a =  ((x & (x>>16))>>8) & (x & (x>>16)) & 0xAA; // we get 0xAA, if all odd-numbered bits are 1;
  int b = a ^ 0xAA; // 0, if a = 0xAA
  return !b;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // with subtraction,to make sure x is in the right range
  int a = ((x + ~0x30 + 1) | (0x39 + ~x + 1)) >> 31; // 0 ，if it is positive
  return !a;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int mask = ~(!x) + 1;
  return (~mask & y) | (mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // two cases: x<0 && y>0 
  // x,y have the same sign. it will over flow, if not.
  return ((x>>31) & !(y>>31)) | !((x^y) >> 31) & !((y + ~x + 1)>>31);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return ((x|~x+1)>>31)+1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  // the main idea is to get the most right 1,for negative number, we need to reverse it
  // because for negative number, we need to find the most right 0.
  // the idea is: first we shift x to the right by the 16 bits, check if it is 0 or not.
  int sign = x >> 31;
  x = x ^ sign; // for negative number, we need to reverse it 
  int b16 =!!(x>>16) << 4; // if (x>>16) is not 0, which means the most right 1 is at the 16-bit position
  x = x >> b16;

  int b8 = !!(x>>8) << 3;
  x = x >> b8;

  int b4 = !!(x>>4) << 2;
  x = x >> b4;

  int b2 = !!(x>>2) << 1;
  x = x >> b2;

  int b1 = !!(x>>1);
  x = x >> b1;

  int b0 = x;
  return b16 + b8 + b4 + b2 + b1 + b0 + 1; // add another 1, reprensenting a positve need a sign bit.
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  // extract sign
  int sign = uf & 0x80000000u;
  // extract exponent:
  int exponent = uf & 0x7f800000u;
  int isDenormalized = !exponent;
  // if exp = 1111 1111 return uf
  // exp = 0000 0000 , uf << 1
  // 0000 0000 < exp < 1111 1111, exp + 1,
  if(isDenormalized){
    uf = sign | (uf << 1); // shift uf ot the left 
  }else if(exponent != 0x7f800000u){
    uf = uf + 0x00800000u; // add 1 to exponent
  }
  return uf;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  // val = (-1)^s * M * 2^E; E = e - bias; 
  //  if exponent = 0000 0000, e = 1 - bias
  // bias = 2^7  = 127
  int sign = (uf >> 31) & 1;
  int exp = (uf >> 23) & 0xff;
  int frac = uf & 0x7FFFFF;  
  int bias = 127;
  int E = exp - bias;
  // nan or out of range, return 0x80000000u
  if(exp == 0xff || E > 31){
    return 0x80000000u;
  }
  if(E <= 0){
    return 0;
  }
  int M = frac | 0x800000;
  int value;
  // actually we create a 24-bit, like M * 2^23, but we want M * 2^E
  if(E>23){
   value = M << (E-23);
  }else{
    value = M >> (23-E);
  }

  if(sign){
    value = -value;
  }

  return value;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  // 2^x, so for denormal there is only 1 1bit in frac. otherwise it can't be 
  // represented as 2^x format: 2^x = 2^(1-127) * M, M = frac = 2^(-1 ~ -23)
  // sign always 0, 2^x > 0
  // smallest denormal: 000000000...1    M = 2^-23,  val = 2^-23 * 2^(1-127) = 2^-149
  //                    000000000..10    M = 2^-22,  val = 2^-22 * 2^(1-127) = 2^-148
  // biggest denormal:  0000000001..0    M = 2^-1,  val = 2^-1 * 2^(1-127) = 2^-127
  // smallest normal:   000000001...0    M = 1,  val = 2^(1-127) = 2^-126
  // biggest normal:    011111110...0    M = 1,  val = 2^(254-127) = 2^127
  // +inf               011111111...0
  if(x<-149){
    return 0;
  }
  if(x<=-127){
    return 1 << (149+x);
  }
  // -126 < x < 127
  if(x<=127){
    return (127 + x) << 23;
  }
    return 0x7f800000u;
}
