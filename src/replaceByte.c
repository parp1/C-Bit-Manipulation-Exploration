/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c)
{
  /* uses a mask that zeros out the desired byte location in x, then shifts the given byte c to be fill in that zeroed out location after the sum is taken */
  return (x & ~(0xff << (n << 3))) + (c << (n << 3));
}