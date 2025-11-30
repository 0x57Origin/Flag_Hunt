# Flag Hunt Solutions

This file walks through how each challenge in the binary can be solved.
The goal is not to brute force anything but to learn how to read the program using Ghidra or any reverse engineering tool.

The tone here is casual and simple.
Nothing fancy.
Just straight explanations.

---

# Challenge 1

### How I solved it

Open the binary in Ghidra and look at the function called **challenge1**.
Inside the decompiler window you will see:

```c
strcmp(buf, "0420");
```

That confirms the required PIN.

### Final Answer

**0420**
Flag prints right after.

---

# Challenge 2

### How I solved it

Inside **challenge2**, you will see:

```c
strcmp(buf, "reverse_me");
```

So the password is in plain text.

After that, the program calls:

```c
decode_and_print("q{vpLO\aEh^DhYXChERV[hTENGCXJ", 0x1c, '7');
```

The third argument is the key.
The key is `'7'`.

The encrypted string is the first argument.
So I decoded it using a simple Python script.

### Python code to decode

```python
enc = "q{vpLO\aEh^DhYXChERV[hTENGCXJ"
key = ord('7')
decoded = ""

for c in enc:
    decoded += chr(ord(c) ^ key)

print(decoded)
```

### Final Answer

Password: **reverse_me**
Flag prints after decoding.

---

# Challenge 3

### How I solved it

The decompiler shows this logic:

```c
(a + b + c == 42)
(a*a + b*b + c*c == 666)
(a*b*c == 420)
```

These are three conditions that all must be true at the same time.
The easiest way is to brute force small numbers or just experiment.

One working solution is:

```
a = 4
b = 5
c = 11
```

You can enter them as:

```
4 5 11
```

Then the program calls:

```c
decode_and_print("\x13\x19\x14\x12.6:;!':9\n39:\"\n<&\n4\'!(", 0x19, 'U');
```

Key is `'U'`.

### Python code to decode

```python
enc = "\x13\x19\x14\x12.6:;!':9\n39:\"\n<&\n4'!("
key = ord('U')
decoded = ""

for c in enc:
    decoded += chr(ord(c) ^ key)

print(decoded)
```

### Final Answer

Input: **4 5 11**
Flag prints after decoding.

---

# Challenge 4

### How I solved it

Inside **challenge4**, the code runs:

```c
uVar1 = simple_hash(buf);
if (uVar1 == 0x1862b5a8)
```

So your input must hash to `0x1862b5a8`.

Looking at the hash function:

```c
h = 0x12345678;
for each character:
    h = (h ^ char) * 0x45D9F3B;
```

Instead of reversing the hash, the easier method is to scroll through the binary and spot a string that looks like a phrase.
The one that matches the target is:

```
ghidra_is_cool
```

Typing that makes the hash check pass.

The flag itself is stored encoded here:

```c
decode_and_print("T^SUizsazM\x7fwM{tMk}gMqs|o", 0x18, '\x12');
```

So the key is `0x12`.

### Python code to decode

```python
enc = "T^SUizsazM\x7fwM{tMk}gMqs|o"
key = 0x12
decoded = ""

for c in enc:
    decoded += chr(ord(c) ^ key)

print(decoded)
```

### Final Answer

Magic word: **ghidra_is_cool**
Flag prints after decoding.

---

# Challenge 5

### How I solved it

The comparison is right in the decompiler:

```c
strcmp(buf, "i_will_reverse_anything");
```

So that is the required phrase.

Then the encoded flag is passed to:

```c
decode_and_print(",&+-\x11\x13\x05\x1f5\b\x0f\v\x1e5\x1e\x02\x0f5\b\x03\x04\v\x18\x13\x17", 0x19, 'j');
```

The third argument is `'j'`.
That is the decode key.

### Python code to decode

```python
enc = ",&+-\x11\x13\x05\x1f5\b\x0f\v\x1e5\x1e\x02\x0f5\b\x03\x04\v\x18\x13\x17"
key = ord('j')
decoded = ""

for c in enc:
    decoded += chr(ord(c) ^ key)

print(decoded)
```

### Final Answer

Input: **i_will_reverse_anything**
Flag prints after decoding.

---
