/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y)
{
  /* uses DeMorgan's law: x & y = !(!(x && y)) = !(!x || !y) */
  return ~(~x | ~y);
}