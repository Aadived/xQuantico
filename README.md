<h1 align="center">
  <br>
  <a href="https://github.com/InTacht-OSS-Foundation/xQuantico"><img src="https://github.com/InTacht-OSS-Foundation/xQuantico/blob/master/resources/xQLogo.jpg" alt="ArminC AutoExec"></a>
</h1>

<h4 align="center">Project - xQuantico</h4>
<h6 align="center">The Only Programming Language, You Need</h6>
---
# About
Introducing you to Project xQuantico it is not just another Hobby or Toy project focused on showing the steps of compiler development. It is a serious project that we wish to turn into a mainstream general purpose programming language for Classical and Quantum Processors.

### Inspiration:
The main idea behind this project revolves around Bridging the Gaps formed due to availability of numerous programming languages, Developer Satisfaction, Ease of Usability, Feel the Power etc...
### Aimed Features:

0. Very High Compiling speeds between (1-10Million loc/s). On average computing devices.
1. Very small compiler binary in comparison to : Golang, Rust, Clang etc.
2. Adaptable Parser which understands your coding style.
3. Highly customizable syntax which you can learn in just 5 minutes, anyways the parser adapts your style so you can always teach it what is the best way to `Do it, Your Way`.
4. Support for various possible coding paradigms.
5. Code Once Run Anywhere without a VM.
6. Lightning Fast with an AIM to beat C in terms of speed and Match Assembly.
7. Power within, complete control from absolute low-level like Assembly and C to Advanced high-level abstractions like the modern languages.
8. Combine the power of Quantum Processors with Classical ones opening the possibility to making hybrid programs to outperform most of the existing Best Algorithms.
9. Rich standard library `xQLib` that includes everything that you will ever need while developing with `xQuantico`. Covering all the aspects from Classical Programs to Quantum to Hybrid...

## Roadmap
### CLI Application :
  1. Ready and Working
  2. 2.needs more clean up.

### Utility Codes :
  1. Mostly the part of xQLib.
  2. Currently only `Trie` and `List` data structures with some file reading support from scratch is done.

### Code Scanning and Tokenization :
  1. Ready and working.
  2. Uses the above mentioned utils for optimizing speeds and readability.

### Parsing Mechanism :
  1. Work in Progress (From: Aug 25,2020)
  2. Will be creating a basic version of parser which can parse a fixed syntax for `rc-v0.1` and evolve the codebase to make it adaptable in later versions.

### Code Generation Mechanism :
  1. To be done after Parser for `rc-v0.1` is complete.
  2. Will add support for `x86-64` generation for `rc-v0.1`.

### Linking Mechanism :
  1. Will be using `ld (from GNU bin utils)` as primary linker till `rc-v0.5`.
  2. Will add our own linking logic for xQuantico to compiler binary itself.