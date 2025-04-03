# Debugging Guide for GDB

This guide explains how to use GDB for proactive debugging, particularly focusing on debugging segfaults and other issues in the verbose_minunit implementation.

## Compiling for Debugging

First, ensure your Makefile includes debug symbols:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -I. -g -O0
LDFLAGS = -lm
```

The `-g` flag includes debug symbols, and `-O0` disables optimizations for easier debugging.

## GDB Commands and Usage

### 1. Starting GDB
```bash
gdb ./verbose_minunit_example
```
- Launches GDB with your program loaded
- The `-g` flag ensures debug symbols are included
- `-O0` disables optimizations for easier debugging

### 2. Setting Breakpoints
```bash
break main
break mu_check_verbose
```
- `break` (or `b`) sets a breakpoint where execution will pause
- You can set breakpoints at:
  - Function names
  - Line numbers (e.g., `break verbose_minunit_example.c:42`)
  - File and line (e.g., `break minunit_verbose.h:123`)

### 3. Running the Program
```bash
run
```
- Starts program execution
- Will stop at first breakpoint
- You can also run with arguments: `run arg1 arg2`

### 4. Stepping Through Code
```bash
next    # Execute next line, stepping over function calls
step    # Execute next line, stepping into function calls
continue # Continue execution until next breakpoint
```
- `next` (or `n`) is good for moving through your code
- `step` (or `s`) is useful when you want to dive into a function
- `continue` (or `c`) resumes normal execution

### 5. Examining Variables
```bash
print variable_name
print *pointer
print array[0]@10  # Print first 10 elements of array
```
- `print` (or `p`) shows variable values
- Can evaluate expressions
- Can print memory contents

### 6. Viewing Call Stack
```bash
backtrace
```
- Shows the call stack
- Very useful when you hit a segfault
- Shows the chain of function calls that led to the crash

### 7. Memory Examination
```bash
x/10x pointer  # Examine 10 words in hex
x/10c pointer  # Examine 10 bytes as characters
x/10i pointer  # Examine 10 instructions
```
- `x` command is powerful for memory inspection
- Can show memory in different formats
- Useful for finding buffer overflows

### 8. Watching Variables
```bash
watch variable_name
```
- Stops execution when a variable changes
- Great for tracking down where values change unexpectedly

### 9. Conditional Breakpoints
```bash
break minunit_verbose.h:123 if count == 5
```
- Only breaks when condition is true
- Useful for debugging loops or specific cases

### 10. Frame Navigation
```bash
frame 2    # Switch to frame 2 in backtrace
up         # Move up one frame
down       # Move down one frame
```
- Helps navigate the call stack
- Useful for examining different contexts

### 11. Viewing Source Code
```bash
list       # Show current location
list 20,30 # Show lines 20-30
list function_name
```
- Shows source code around current position
- Helps orient yourself in the code

### 12. Debugging a Segfault

When you hit a segfault:
1. Use `backtrace` to see where it occurred
2. Use `frame` to move to the relevant stack frame
3. Use `print` to examine variables
4. Use `x` to examine memory if needed
5. Set breakpoints before the crash to catch it earlier

## Advantages Over printf Debugging

Using GDB is much more powerful than printf because:
- You can examine any variable at any time
- You can step through code line by line
- You can see the exact state when a crash occurs
- You can modify variables during execution
- You can set conditional breakpoints
- You can examine memory directly
- You can see the full call stack

## Example Debugging Session

Here's an example of debugging a segfault in verbose_minunit:

```bash
# Start GDB
gdb ./verbose_minunit_example

# Set breakpoint at the test function
break test_check_verbose

# Run the program
run

# When it stops at the breakpoint, step through
step

# If it crashes, examine the backtrace
backtrace

# Move to the relevant frame
frame 2

# Examine variables
print variable_name

# Continue execution
continue
```

This approach allows you to systematically track down issues without modifying your code with printf statements. 