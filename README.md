# Flag Hunt – A Mini Reverse Engineering Challenge

This is a small reverse engineering project I built for fun.
It is a single C program compiled into an ELF binary, and it contains five short challenges.
Each challenge hides a flag behind simple code analysis, string inspection, XOR decoding, or basic logic.

Nothing advanced. Nothing overwhelming. Just a good starter project if you want to practice reading C code inside Ghidra or IDA.

---

## What this binary includes

Here are the five levels you will find inside:

1. A simple PIN check
2. A password check with a hidden XOR key
3. A small math puzzle with constraints
4. A custom hash function guarding a flag
5. A final phrase check with one more XOR encoded flag

Each challenge teaches a slightly different reverse engineering idea.

---

## Why this exists

I wanted something small and clean that people could load into Ghidra without being hit with thousands of functions or crazy obfuscation.
This binary helps you practice the basics of:

* Reading C code after decompilation
* Following simple logic and conditions
* Understanding how XOR encoding works
* Identifying hardcoded values
* Looking at the Strings window
* Recognizing custom hash loops
* Tracing how data moves through a function

It is friendly for beginners but still interesting enough for anyone who enjoys taking binaries apart.

---

## How to run the program

If you want to compile from source:

```
gcc main.c -o flag_hunt
```

Or just run the already compiled binary:

```
./flag_hunt
```

You will see a menu like this:

```
==== Flag Hunt Menu ====
1) Challenge 1 - PIN
2) Challenge 2 - Password
3) Challenge 3 - Math puzzle
4) Challenge 4 - Hash word
5) Challenge 5 - Final phrase
0) Exit
```

Most challenges are not meant to be solved by guesswork.
The real solutions come from reverse engineering the program itself.

---

## How to solve it

Open the binary in Ghidra, Cutter, or IDA Free.
Then do the following:

1. Inspect the list of functions
2. Check the Strings window
3. Open each challenge function
4. Read the logic that checks the user input
5. Find encoded flag data inside `decode_and_print` calls
6. Reproduce the decoding logic on your own
7. Enter the correct inputs into the program or extract the flags directly

You will learn a lot just by following how the program flows.

---

## What this project teaches

* How to read decompiled C code
* How to identify comparison checks such as `strcmp`
* How basic XOR encoding works
* How to find data in `.rodata`
* How to understand small hash functions
* How to combine strings, assembly, and logic into a solution

It is a simple project, but it covers a lot of the fundamentals that real reverse engineering requires.

---

