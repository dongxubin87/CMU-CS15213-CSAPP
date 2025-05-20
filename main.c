#include<stdio.h>
long copyLSB(long x) {
  // first we get the least bit: 0 or 1 by x & 1
  // then we compute the negation of 0 or 1, we can use : -a = ~a + 1;
  // we notice the result must be 0 or -1 in decimal;
  return ~(x & 1) + 1;
}
/*
* allOddBits - return 1 if all odd-numbered bits in word set to 1
*   where bits are numbered from 0 (least significant) to 63 (most significant)
*   Examples: allOddBits(0xFFFFFFFDFFFFFFFDL) = 0L,
*             allOddBits(0xAAAAAAAAAAAAAAAAL) = 1L
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 14
*   Rating: 2
*/
long allOddBits(long x) {
  // create binary AA: 10101010, AA | x, then shift left by 8 bits， then 16, 32 bits
  // you get 0xAAAAAAAAAAAAAAAA, then (c & x ^ c),it is 0 if all odd-numbered bits are 1

  long AA = 170;
  long a = (AA << 8) | AA;
  long b = (a << 16) | a;
  long c = (b << 32) | b; // c is 0xAAAAAAAAAAAAAAAA

  return !(c & x ^ c);
}
/*
* isNotEqual - return 0 if x == y, and 1 otherwise
*   Examples: isNotEqual(5L, 5L) = 0L, isNotEqual(4L, 5L) = 1L
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 6
*   Rating: 2
*/
long isNotEqual(long x, long y) {
  // first x^y, then we get 0 or non 0, then !(x^y) we get 1 or 0, 
  // how to convert 0 or 1 to 1 or 0. we use xor, |.
  return !(x^y)^1 ;
}
/*
* dividePower2 - Compute x/(2^n), for 0 <= n <= 62
*  Round toward zero
*   Examples: dividePower2(15L,1L) = 7L, dividePower2(-33L,4L) = -2L
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 15
*   Rating: 2
*/
long dividePower2(long x, long n) {
  return x >> n;
}
// 3
/*
* remainderPower2 - Compute x%(2^n), for 0 <= n <= 30
*   Negative arguments should yield negative remainders
*   Examples: remainderPower2(15L,2L) = 3, remainderPower2(-35L,3L) = -3L
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 20
*   Rating: 3
*/
long remainderPower2(long x, long n) {
  // if x is negative, 
  long mod =  x & ((1 << n) + ~0); // if it is positive, mod is result
  // if x is negative,according the above formular we will get :
  //        actual    expected
  // -5 % 8    3        -5
  // -6 % 8    2         -6
  // -11 % 8   5          -3
  // we found out we use actual-8(2^n) to get the correct result
  long isNeg = x >> 63; // if it is positive, we get 0, otherwise -1(0xFFFFFFFFFFFFFFFF)
  long bias = isNeg & (1 << n); // 
  long result = mod + (~bias + 1);
  return result;
}
/*
* rotateLeft - Rotate x to the left by n
*   Can assume that 0 <= n <= 63
*   Examples:
*      rotateLeft(0x8765432187654321L,4L) = 0x7654321876543218L
*   Legal ops: ~ & ^ | + << >> !
*   Max ops: 25
*   Rating: 3
*/
long rotateLeft(long x, long n) {
  // for instance: x = 1101 1001, n = 1
  // we want the result: 1001 1101
  // we need to consider it's positive or not 
  // shift x to the right by 64-n bits, we can get the dropped part:1111 1101
  // 
  long a =  x >> (64+ ~n +1); // 1111 1101
  long b = x << n; // 1001 0000
  long mask =  ~(1 >> (64+ ~n +1)<<1);// with this , we can get 0000 1111
  long result = a ^ (b & mask); //  a | (b & mask) is also available
  return result;
}
/*
* bitMask - Generate a mask consisting of all 1's
*   between lowbit and highbit
*   Examples: bitMask(5L,3L) = 0x38L
*   Assume 0 <= lowbit < 64, and 0 <= highbit < 64
*   If lowbit > highbit, then mask should be all 0's
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 16 
*   Rating: 3
*/
long bitMask(long highbit, long lowbit) {
  // (is_neg & number) can make result equals 0, if lowbit > highbit 
  long is_neg = ~((highbit + ~lowbit + 1) >> 63); 
  long oneCheck = 1L << 63;
  // for example, h = 5,l = 3, 
  long a = oneCheck >> (63+ ~lowbit +1); // then we can get  1111 1000
  long b = oneCheck >> (62+ ~highbit +1); //          we got 1100 0000
  // a ^ b, 0011 1000
  long ans = is_neg & (a ^ b);
  return ans;
}
/*
* isPower2 - returns 1 if x is a power of 2, and 0 otherwise
*   Examples: isPower2(5L) = 0L, isPower2(8L) = 1L, isPower2(0) = 0L
*   Note that no negative number is a power of 2.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 20
*   Rating: 3
*/
long isPower2(long x) {

  // there should be an only one 1 bit exists ，
  // when we x & (x-1),we get 0 if it is a power of 2
  // x = 0 is special
  long isZero = !x; // 1 if x is 0
  return !(x & (x + ~1 + 1)) & !isZero; // 
}
// 4
/*
* allAsciiDigits - return 1 if each byte b in x satisfies
*   0x30 <= b <= 0x39 (ASCII codes for characters '0' to '9')
*   Example: allAsciiDigits(0x3031323536373839L) = 1L.
*            allAsciiDigits(0x4031323536373839L) = 0L.
*            allAsciiDigits(0x0031323536373839L) = 0L.
*   Legal ops: ! ~ & ^ | << >>
*   Max ops: 30
*   Rating: 4
*/
long allAsciiDigits(long x) {
  long a = !((x + ~0x30L + 1) >> 63);
  long b = !((0x39L + ~x + 1) >> 63);
  return a & b;
}
/*
* trueThreeFourths - multiplies by 3/4 rounding toward 0,
*   avoiding errors due to overflow
*   Examples:
*    trueThreeFourths(11L) = 8
*    trueThreeFourths(-9L) = -6
*    trueThreeFourths(4611686018427387904L) = 3458764513820540928L (no
* overflow) Legal ops: ! ~ & ^ | + << >> Max ops: 20 Rating: 4
*/
long trueThreeFourths(long x) {
  return 2;
}
/*
* bitCount - returns count of number of 1's in word
*   Examples: bitCount(5L) = 2, bitCount(7L) = 3
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 50
*   Rating: 4
*/
long bitCount(long x) {
  return 2;
}

int main(){
  // isPower2(long x);
  // allAsciiDigits(long x);

  printf("copyLSB: %ld\n",copyLSB(6));
  printf("allOddBits: %ld\n",allOddBits(6));
  printf("isNotEqual: %ld\n",isNotEqual(5,5));
  printf("dividePower2: %ld\n",dividePower2(30,4));
  printf("remainderPower2: %ld\n",remainderPower2(-15,3));
  printf("rotateLeft: %ld\n",rotateLeft(1,2));
  printf("bitMask: %ld\n",bitMask(6,1));
  printf("isPower2: %ld\n",isPower2(-2147483648));
  printf("allAsciiDigits: %ld\n",allAsciiDigits(0x4031323536373839L));
  return 0;
}