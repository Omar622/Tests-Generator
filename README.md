# Tests-Generator
Tool helps creating test cases for problem creators in codeforces

# How to use

To create test cases for codeforces problem:

1. Implement generator code. (every time this code is run, it will output (standard output) a random valid input for the problem)
    - If you use `C++`, this library may help you.
2. run `Tests_Generator` and enter path of the generator executable file and number of test cases you want to generate.
    - You can find the tool in the releases or you can execute `main.cpp` in the source code.
    - The tool will generate each test case in `.txt` file with unique name of 6 digit number.
    - All files will be generated in directory `Tests` which will be in the same tool's directory.
