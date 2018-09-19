/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x)
{
  /* uses a mask that has 1's in the odd locations by shifting 0xaa. Uses 2 !'s to get the resulting value to 0 or 1 */
  int mask = (((((0xaa << 8) + 0xaa) << 8) + 0xaa) << 8) + 0xaa; // 1010 1010 1010 1010 1010 1010 1010 1010
  return !!(x & mask);
}