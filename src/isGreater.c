/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */ 
int isGreater(int x, int y)
{
  /* determines the sign of x, y, and 1 less than their difference (to bias for the 0 case) and uses these results to check whether the signs are the different,
  in which case x has to positive and y negative, or whether the signs are the same and if the difference is positive or negative */
  int difference = x + ~y; //x - y = x + (~y + 1), then subtract 1 to bias for 0 case
  int signx = 1 & (x >> 31);
  int signy = 1 & (y >> 31);
  int signd = 1 & (difference >> 31);

  int samesign = !(signx ^ signy) & !signd;
  int diffsign = (!signx) & signy;

  return samesign | diffsign;
}