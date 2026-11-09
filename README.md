# Vole Machine – Qt GUI

A graphical interface for the Vole Machine simulator, built with C++ and Qt 6.
Load a Vole program from a file or type it in instruction by instruction, then run it or step through it while watching the memory, registers, and output live.

## Features

- **Program Control**: browse for a program file and Load it, then Run, Step, or Reset.
- **Instruction entry**: type a 4-digit hex instruction and press **Add** (or Enter) to append it to memory, so you can write a program by hand without a file.
- **Help button**: opens a table of every supported instruction.
- **Memory view**: 128 rows (addresses `00`–`FE`, two cells per row). The row at the current PC is highlighted.
- **Address search**: type a hex address to jump to it.
- **Registers view**: R0–RF as cards, plus large **PC** and **IR** displays.
- **Input / Output console**: shows program output and opens a dialog when the program asks for input.
- **Dark navy theme**, and the window opens maximized to fit the screen.

## Requirements

- Qt 6 (tested with Qt 6.12.0, MinGW 64-bit)
- CMake 3.16 or newer
- A C++17 compiler (MinGW on Windows)
- Qt Creator (recommended)

## Project structure

```
CMakeLists.txt
main.cpp            application entry point (opens the window maximized)
widget.h / .cpp     the GUI (class MainWindow)
Machine.h / .cpp    ties CPU, Memory, Loader and IO together
CPU.h / .cpp        fetch, decode, execute
Memory.h / .cpp     256 memory cells
Register.h / .cpp   16 registers
Loader.h / .cpp     loads a program file into memory
Instruction.h / .cpp
InputOutput.h / .cpp
```

## Build and run

1. Open `CMakeLists.txt` in Qt Creator.
2. Choose the kit **Desktop Qt 6.x MinGW 64-bit**.
3. Run **Build → Run CMake**, then **Build → Rebuild All**.
4. Press **Run** (green triangle) or `Ctrl+R`.

`CMakeLists.txt` uses `file(GLOB ...)`, so any `.cpp` / `.h` file you add to the folder is picked up after re-running CMake.

## How to use

### Run a program from a file

1. Click the folder button and choose a program file, or type its path.
2. Click **Load**. The program appears in the Memory table.
3. Click **Step** to execute one instruction, or **Run** to execute until the program halts.
4. Click **Reset** to reload the file and start over.

### Write a program by hand

1. Type a 4-digit hex instruction (for example `2141`) in the **Instruction** box.
2. Click **Add** or press Enter. It is written to the next free address in memory.
3. Repeat for each instruction, ending with `C000` (halt).
4. Click **Run** or **Step**.

Note: if you Load a file that already ends with `C000` and then Add instructions, they are placed after the halt and will not run. Start from an empty memory (don't Load) when writing by hand.

### Help

Click **Help** next to Add to see the instruction set.

After every Add, Step, or Run, the Memory, Registers, PC, and IR are refreshed.
When the program reaches `C000` (halt), Run and Step stop. Press **Reset** to run again.

## Program file format

A text file of hex instructions, each one 4 hex digits (2 bytes). Example:

```
2141
3100
C000
```

| Opcode | Meaning |
|--------|---------|
| `1RXY` | Load register R from memory address XY |
| `2RXY` | Load register R with the value XY |
| `3RXY` | Store register R at address XY (address `00` prints to the screen) |
| `40RS` | Copy register R to register S |
| `5RST` | R = S + T (two's complement) |
| `6RST` | R = S + T (floating point) |
| `7RST` | R = S OR T |
| `8RST` | R = S AND T |
| `9RST` | R = S XOR T |
| `AR0X` | Rotate register R right X times |
| `BRXY` | Jump to address XY if R equals R0 |
| `C000` | Halt |

The example above loads `41` (the letter `A`) into R1, stores it at address `00` so it prints to the Output console, then halts.

## How the GUI connects to the machine

The `InputOutput` class has two callbacks, `outputHandler` and `inputHandler`.
`MainWindow` sets them in its constructor:

- `outputHandler` appends the text to the Output console.
- `inputHandler` opens a Qt input dialog and returns what the user typed.

If the callbacks are not set, `InputOutput` falls back to `cin` / `cout`, so the machine still works as a console program.

`Machine` exposes `getCPU()`, `getMemory()` and `getIO()` so the GUI can read the registers and memory and write instructions into memory.

## Troubleshooting

| Problem | Fix |
|---------|-----|
| `'Machine.h' file not found` | Copy all Vole `.h` and `.cpp` files into the same folder as `widget.h` |
| `undefined reference ...` | A `.cpp` file is missing from the project folder. Re-run CMake |
| `Failed to load program!` | Check the file path and that the file contains valid hex instructions |
| Output stays empty | The program never stores to address `00`. Try the example above |
| Added instruction doesn't run | It was added after a `C000`. Reset memory and add instructions from the start |
