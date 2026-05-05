# 📦 Compression & Decompression Algorithms Suite

A comprehensive project that demonstrates multiple **lossless text compression algorithms**, ranging from simple repetition-based methods to advanced statistical and dictionary-based techniques.

This project is designed for:

* 🎓 Learning core compression concepts
* ⚙️ Experimenting with different algorithms
* 📊 Comparing performance and efficiency

---

# 🎯 Project Overview

This repository explores how different algorithms reduce data size by:

* Eliminating redundancy
* Detecting repeated patterns
* Encoding symbols efficiently
* Leveraging statistical frequency

Each algorithm supports:

* **Compression** (Encoding)
* **Decompression** (Decoding)

---

# 🧠 Algorithms Included

## 1) Run-Length Encoding (RLE)

### 🔹 Idea

Replaces consecutive repeated characters with a single character and a count.

### 🔹 Best for

* Highly repetitive data

### 🔹 Example concept

```text
AAAABBB → A4B3
```

---

## 2) Simple Repetition Suppression (SRS)

### 🔹 Idea

Removes consecutive duplicate characters, keeping only one.

### 🔹 Example

```text
aaabbbcc → abc
```

### ⚠️ Note

* Not reversible → **not true compression**

---

## 3) LZ77 (Advanced Pattern Substitution)

### 🔹 Idea

Replaces repeated substrings with references to previous occurrences using a sliding window.

### 🔹 Format

```text
(offset, length, next_character)
```

### 🔹 Key Features

* No fixed dictionary
* Uses previously seen data dynamically
* More powerful than basic pattern substitution


### 🖼️ LZ77 Example

![alt text](image.png)

The image should show:

* Sliding window
* Matching substring
* Generated tags

---

## 4) Fixed-Length Coding

### 🔹 Idea

Each symbol is assigned a binary code of equal length.

### 🔹 Example

```text
A → 00
B → 01
C → 10
D → 11
```

### 🔹 Limitation

* Does not consider frequency → inefficient

---

## 5) Variable-Length Coding

### 🔹 Idea

Assigns shorter codes to more frequent symbols.

### 🔹 Key Rule

* Must be **prefix-free**

### 🔹 Benefit

* Better compression than fixed-length

---

## 6) Shannon–Fano Algorithm

### 🔹 Idea

Creates variable-length prefix-free codes by recursively splitting symbols based on frequency.

### 🔹 Steps

1. Sort symbols by frequency
2. Divide into two balanced groups
3. Assign binary digits (0 / 1)
4. Repeat recursively

---

## 7) Huffman Algorithm

### 🔹 Idea

Builds optimal prefix-free codes using a greedy approach and a binary tree.

### 🔹 Features

* Frequency-based
* Produces optimal compression
* Widely used in real-world systems


---

# 🔄 Compression vs Decompression

| Operation     | Description                              |
| ------------- | ---------------------------------------- |
| Compression   | Converts original data into encoded form |
| Decompression | Restores original data from encoded form |

---

# ⚖️ Algorithm Comparison

| Algorithm            | Type             | Efficiency | Reversible |
| -------------------- | ---------------- | ---------- | ---------- |
| RLE                  | Repetition-based | Low–Medium | ✔️         |
| SRS                  | Reduction        | Low        | ❌          |
| LZ77                 | Dictionary-based | High       | ✔️         |
| Fixed-Length         | Coding           | Low        | ✔️         |
| Variable-Length      | Coding           | Medium     | ✔️         |
| Shannon–Fano         | Statistical      | Medium     | ✔️         |
| Huffman              | Statistical      | High       | ✔️         |

---

# 🧩 Suggested Project Structure

```text
project/
│
├── algorithms/
│   ├── rle
│   ├── srs
│   ├── lz77
│   ├── fixed_length
│   ├── variable_length
│   ├── shannon_fano
│   └── huffman
│
├── gui/
│   └── app.py
|
|── media/
|   └── pic.png
│
└── README.md
```

---

# 🚀 Future Improvements

* GUI integration with all algorithms
* File compression support
* Performance comparison dashboard
* Visualization tools (trees & windows)
* Bit-level optimization

---

# 🎓 Learning Outcomes

By working on this project, you will understand:

* How compression reduces redundancy
* The importance of frequency in encoding
* Differences between rule-based and statistical methods
* Real-world compression strategies

---

# 📌 Final Note

This project provides a structured journey from:

* Simple compression ideas → to
* Advanced, optimal encoding techniques

It is designed to build a strong foundation in **data compression concepts and implementations**.

---
