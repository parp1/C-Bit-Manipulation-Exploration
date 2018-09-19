/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y)
{
  /* determines the sign of x, y, and their sum, and uses these results to check whether the signs are different which would never result in overflow
  or whether the signs are the same and both differ from the sign of the sum */
  int addition = x + y;
  int signx = 1 & (x >> 31);
  int signy = 1 & (y >> 31);
  int signa = 1 & (addition >> 31);

  return (signx ^ signy) | (!(signx ^ signa) & !(signy ^ signa));
}