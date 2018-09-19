# C-Bit-Manipulation-Exploration
A short exploration of bit manipulation problems in C. Adapted from UCLA CS33 coursework.

****

## Bit Manipulation basics

### Representation 

Some important points to understand before this tutorial:

* Big vs. Little Endian
* Basic Boolean Algebra concepts and laws
* How Integers are stored in memory

### Operators

Assuming familiarity with how integers and floats are stored in memory, any representation of such values can be modified with the following operators:

* & — bitwise 'and' — acts as a "mask"
* | — bitwise 'or' — acts as a 
* ^ — bitwise 'xor' — acts as a "toggle"
* ~ — bitwise 'not' — acts as a "flip"
* << — left shift — acts as a "multiply by power of 2^n"
* \>\> — right shift — acts as a "divide by power of 2^n"

Note the differences between these bitwise operations and the logical counterparts, such as logical and, or, and not. Nothing says that bitwise and logical operators can't be used together, too; for example, in these exercises, a logical not (!) is sometimes used for its different behavior.

### Shifts

Finally, with right shifts, we can have arithmetic and logical shifts.

* Arithmetic — optimal for two's complement numbers, copies over the most significant bit (the sign bit)
* Logical — optimal for unsigned numbers, inserts 0 bits instead of copying anything over

In the case of these exercises, the shifts are assumed to be arithmetic. However, this can vary based on the implementation of C.

****

## Walkthrough

Each problem has a brief introduction on what it should accomplish, and relevent restrictions, such as the operators that can be used and the operator count cap.

### 1. negate

```C
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  return ~x + 1;
}
```

This is the probably the most simple bit manipulation problem there is. The problem statement asks to simply emulate the logical negate operator, `-`. To do so, the bits need to be flipped, and `1` needs to be added.

For example, take the number `42`. Let's assume this is a `short`, so 2 bytes of storage:

`00000000 00101010`

After performing the operation, which highlights the nature of two's complement representations, it is `-42`:

`11111111 11010110`

Here's a more in-depth explanation from Cornell: [Why Inversion and Adding One Works](https://www.cs.cornell.edu/~tomf/notes/cps104/twoscomp.html#whyworks).

### 2. bitAnd

```C
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y)
{
  return ~(~x | ~y);
}
```

The next problem asks to implement the bitwise and, `&`, using only `~` and `|`.

This can be solved using DeMorgan's law:

`x & y` = `~(~ (x & y))` = `~(~x | ~y)`

Some more information on DeMorgan's can be found [here](https://en.wikipedia.org/wiki/De_Morgan's_laws).

### 3. anyOddBit

```C
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x)
{
  int mask = (((((0xaa << 8) + 0xaa) << 8) + 0xaa) << 8) + 0xaa;
  return !!(x & mask);
}
```

The goal of this harder problem is to return 1 if any odd-numbered bit in the input is set to 1. Clearly, this will require the use of masks.

An suitable mask would have `1`'s in all odd positions. To do so without creating a constant that is not allowed by the specifications, left shifts must be used.

The mask is constructed with the constant `0xaa` and repeated left shifts of size `8` and additions of more of the constants. Then, the mask is applied to the input and two logical nots are used.

The logical nots serve the purpose of diminishing the output to either a `0` or `1`. If the mask results in any odd index being flagged, or containing a `1`, the first not will result in a `0` and then the second will result in a negation back to `1`. If the masks results in no odd index being flagged, then the result has to be `0`, which after two logical nots will still be `0`.

### 4. divpwr2

```C
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
  int bias = ((1 << n) + (~0)) & (x >> 31);
  return (x + bias) >> n;
}
```

Now, things get a bit trickier. Here, the problem states to compute x / (2 ^ n), rounding towards 0.

This requires accounting for two cases, a negative and positive case, since the latter naturally rounds towards 0 when dividing, while the former does not.

Examining this discrepancy further, take the following `char` values: `7` and `-7`. Assuming `n = 1`, then the result of this function should be `3` and `-3` respectively.

`0111` right shifted by 1 is `0011`, or `3`. This is correct. Positive values naturally truncate with right shifts.

`1001` right shifted by 1 is `1100`, or `-4`. This is incorrect. Negative values naturally round away from 0 with right shifts.

Thus, some sort of bias value needs to be created:

```C
int bias = ((1 << n) + (~0)) & (x >> 31);
```

First, the amount of bias needs to be determined. This is simply whatever the denominator, or `2 ^ n`, minus `1`. This is calculated by left shifting `1` by `n` and then adding a negative `1`, or `+ (~0)`.

The range is one less than the denominator value since the lower bound edge case of each multiple of the denominator would fail, otherwise.

For example, if `n = 1`, then the bias should be `1`, not `2`. If it were the latter, then the function would perform correctly on `-5`, but incorrectly on `-4`. (Try it!)

In the positive case the bias doesn't need to be present, so a final mask by the sign-bit right shifted by `31` (one less than the word size) is required. Hence, if the original `x` is negative, the mask will be all `1`'s and the bias will be kept. If not, the mask will be `0` and nullify the bias.

Finally, a right shift of `n` is applied to `x + bias` to attain the properly rounded value.

Overall, notice how parentheses are used to enforce the order of operations. Without these, the operations would follow precedence, which can get tricky and hard to remember.

### 5. ezThreeFourths

```C
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x)
{
  int result = x + x + x;
  int negativeCheck = 3 & (result >> 31);
  result = (result + negativeCheck) >> 2;
  return result;
}
```

This problem is essentially a degenerated form of the former. It incorporates the same logic for the bias values, although it is a bit more concrete to see here.

### 6. addOK

```C
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y)
{
  int addition = x + y;
  int signx = 1 & (x >> 31);
  int signy = 1 & (y >> 31);
  int signa = 1 & (addition >> 31);

  return (signx ^ signy) | (!(signx ^ signa) & !(signy ^ signa));
}
```

This problem is the first of the seriously difficult ones.

The first step is to calculate the sum, simply: 

```C
int addition = x + y;
```

Then, get the signs of each of the following: `x`, `y`, and `addition`. To do so, the value is right shifted by `31` and masked by `1`. Thus, if negative, this results in `1`, otherwise `0`.

The solution relies on understanding how overflow works. If the two inputs are of differing signs, there can never be overflow. If they are the same sign, then if the signs of the inputs and resulting addition differ, there was overflow.

```C
(signx ^ signy) | (!(signx ^ signa) & !(signy ^ signa))
```

Think of the above statement as two separate parts. The left side of the bitwise or checks if the signs of the inputs differ. The right side checks if the signs of the inputs and the result differ.

Note that the right side could look like the following:

```C
(signx ^ signy) | !(signx ^ signa)
```

or

```C
(signx ^ signy) | !(signy ^ signa)
```

This is due to (essentially) "short-circuiting". Air-quotes since technically both sides are evaluated. Both were combined using a bitwise and for the sake of completeness.

### 7. isGreater

```C
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
  int difference = x + ~y;
  int signx = 1 & (x >> 31);
  int signy = 1 & (y >> 31);
  int signd = 1 & (difference >> 31);

  int samesign = !(signx ^ signy) & !signd;
  int diffsign = (!signx) & signy;

  return samesign | diffsign;
}
```

This problem incoporates more of the same logic that was used in the former. There are two cases: the inputs are the same sign, or they are different. If they are the same sign, then the difference, `x - y` has to be positive. If they are different signs, then `x` has to be positive and `y` has to be negative. 

There is a special case to handle, too, where the inputs are equal, so the difference is `0`. Since the problem statement requires `x > y` to be emulated and not `x >= y`.

First, the difference is calculated with a bias for the above case:

```C
int difference = x + ~y; //x - y = x + (~y + 1), then subtract 1 to bias for 0 case
```

This bias accounts for this edge-case. (Try it without!)

Next, just like in the former problem, the signs of the inputs and the difference are acquired. Then, two checks are made, one for when the inputs are the same sign, and another for when they are different:

```C
int samesign = !(signx ^ signy) & !signd;
```

The bitwise and here masks the result of the xor that checks that the signs are indeed the same, and then makes sure the sign of the difference is positive.

```C
int diffsign = (!signx) & signy;
```

This just checks if the two signs are different. There are no other conditions that need to be met in this case. Finally, as one of these cases has to be true, the correct answer is given by:

```C
return samesign | diffsign;
```

Notice how the "short-circuiting"-like principle also applies here. To observe the behavior without handling the `0` case described above, replace the difference line with the following:

```C
int difference = x + (~y + 1);
```

****

## Testing

### Harness

The Makefile can be used to compile the testing harness for this tutorial: `btest`. With this executable, it is possible to run tests for all of the associated problems.

To run a specific problem, use `./btest -f [problem_name]`.

For example, to test `negate` specifically, use:

```bash
./btest -f negate
```