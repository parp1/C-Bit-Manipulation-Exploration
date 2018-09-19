/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n)
{
  /* computes a bias based on the denominator in order to correctly round to 0 in the negative case */
  int bias = ((1 << n) + (~0)) & (x >> 31);
  return (x + bias) >> n;
}
