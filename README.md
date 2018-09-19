# C-Bit-Manipulation-Exploration
A short exploration of bit manipulation problems in C. Adapted from UCLA CS33 coursework.

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
* >> — right shift — acts as a "divide by power of 2^n"

Note the differences between these bitwise operations and the logical counterparts, such as logical and, or, and not. Nothing says that bitwise and logical operators can't be used together, too; for example, in these exercises, a logical not (!) is sometimes used for its different behavior.

### Shifts

Finally, with right shifts, we can have arithmetic and logical shifts.

* Arithmetic — optimal for two's complement numbers, copies over the most significant bit (the sign bit)
* Logical — optimal for unsigned numbers, inserts 0 bits instead of copying anything over

In the case of these exercises, the shifts are assumed to be arithmetic. However, this can vary based on the implementation of C.

## Walkthrough

Each problem has a brief introduction on what it should accomplish, and relevent restrictions, such as the operators that can be used and the operator count cap.

### 1. negate

This is the probably the most simple bit manipulation problem there is. The problem statement asks to simply emulate the logical negate operator, `-`. To do so, the bits need to be flipped, and `1` needs to be added.

For example, take the number `42`. Let's assume this is a `short`, so 2 bytes of storage:

`00000000 00101010`

After performing the operation, which highlights the nature of two's complement representations, it is `-42`:

`11111111 11010110`

Here's a more in-depth explanation from Cornell: [Why Inversion and Adding One Works](https://www.cs.cornell.edu/~tomf/notes/cps104/twoscomp.html#whyworks)

### 2. bitAnd

The next problem asks to implement the bitwise and, `&`, using only `~` and `|`.

## Testing

### Harness

The Makefile can be used to compile the testing harness for this tutorial: `btest`. With this executable, it is possible to run tests for all of the associated problems.

To run a specific problem, use `./btest -f [problem_name]`.

For example, to test `negate` specifically, use:

```bash
./btest -f negate
```