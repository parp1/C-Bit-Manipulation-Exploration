/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x)
{
  /* multiplies by 3/4 by using shifts and checking the negative floor case */
  int result = x + x + x; // multiplying by 3 first to handle overflow cases
  int negativeCheck = 3 & (result >> 31); // checking negative case, will be 3 if number is negative, else 0
  result = (result + negativeCheck) >> 2; // dividing by 4
  return result;
}