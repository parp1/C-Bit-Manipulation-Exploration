/* 
 * tc2sm - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x) 
{
  /* uses a mask that starts with 1 and then is all zeros along with a 'boolean' sign value to either calculate the abs value of all lower bits (all except MSB) when 
  x is negative, or just return x if it is positive */
  int mask = 1 << 31;
  int sign = x >> 31;

  return ((~(x&~mask)+1)&sign) + (x&~sign);
}