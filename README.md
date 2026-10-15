# PROG1353 — C++ Starter Project

A minimal C++ project that builds, runs, and debugs in VS Code with one keystroke.
Copy this folder, rename it, and start writing code in `src/main.cpp`.

Everything here matches the course toolchain: **`clang++`**, **`lldb`**, **CMake**,
**C++20**. If those are not installed yet, do the *C++ Toolchain Setup — Student Guide*
first; this project assumes `clang++ --version` and `cmake --version` already answer.

---

## What's in the box

```
.
├── src/
│   └── main.cpp          your program starts here
├── .vscode/
│   ├── extensions.json   the three extensions this project expects
│   ├── settings.json     build folder, generator, IntelliSense wiring
│   └── launch.json       the F5 debug configuration
├── CMakeLists.txt        what to build, and with which flags
├── .gitignore            keeps build output out of Git
└── README.md             this file
```

Nothing else is needed. `build/` appears the first time you build and is git-ignored —
**never edit anything inside it**, and delete the whole folder if a build goes strange.

## Extensions

Open the folder in VS Code and it will offer to install these. Say yes.

| Extension | Publisher | What it does here |
|---|---|---|
| **C/C++ Extension Pack** | Microsoft | IntelliSense, code navigation, error squiggles |
| **CMake Tools** | Microsoft | the Configure / Build / Launch buttons (inside the pack above) |
| **LLDB DAP** | LLVM | drives `lldb` from the VS Code debug UI |

LLDB DAP ships no debugger of its own — it runs the `lldb-dap.exe` that came with your
`clang++`. That is deliberate: the debugger reading your program is always the exact
version of LLDB that the compiler was built alongside, the same way this course installs
exactly one compiler. (The popular alternative, **CodeLLDB**, bundles a second copy of
LLDB and has no Windows-ARM64 build at all, so it would not run for everyone in the class.)

## Quick start

1. **Copy this folder** somewhere with **no spaces in the path** — `C:\Dev\prog1353\week03`,
   not `Documents\My School Work\...`. Build tools misbehave on paths with spaces.
2. Open a terminal there and run `code .`.
3. Accept the extension recommendations if prompted, then reload VS Code.
4. If VS Code asks you to **select a kit**, choose the **Clang** entry that points into
   `C:\msys64\clang64\bin` (or `clangarm64\bin` on an ARM machine).
5. Press **F5**.

That builds the project and starts it under the debugger. Put a breakpoint on the
`std::cout` line in `src/main.cpp` first — click to the left of the line number — and
F5 will stop there with `year` visible in the **Variables** panel.

## The four keystrokes

| Keystroke | What happens |
|---|---|
| **F7** | Build (CMake Tools) |
| **Ctrl + F5** | Run without the debugger |
| **F5** | Build, then run **under** the debugger |
| **Shift + F5** | Stop debugging |

While stopped at a breakpoint: **F10** steps over a line, **F11** steps into a function,
**Shift + F11** steps back out, **F5** continues.

## The same thing from the terminal

The buttons run these commands. Know both — the terminal is what you will have on a
server, in a lab machine that will not cooperate, and in the embedded courses next term.

```powershell
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -B build   # configure
cmake --build build                                            # compile + link
.\build\app.exe                                                # run
lldb .\build\app.exe                                           # debug
```

At the `(lldb)` prompt: `break set --name main`, `run`, `next`, `print year`, `continue`, `quit`.

## Adding a source file

Two edits, always in this order:

1. Create `src/greet.cpp` and `src/greet.h`.
2. Add the `.cpp` to the target in `CMakeLists.txt` — headers are never listed:

   ```cmake
   add_executable(app
       src/main.cpp
       src/greet.cpp
   )
   ```

3. Build. CMake Tools re-configures automatically when `CMakeLists.txt` changes.

Forget step 2 and you get an **`undefined symbol`** error from the **linker** — the file
compiled fine, it just was not handed to the link stage. That is the single most common
build error in this course, and now you know what it means.

## Commit every time it compiles

```powershell
git init                      # once, in a new project folder
git add .
git commit -m "what I just got working"
```

Graded code that does not compile scores zero. Committing on every clean build means a
working version is always one command away, however badly the next hour goes. You are
not marked on your Git use — two commands are enough.

---

## Troubleshooting

**A pop-up saying "Unimplemented", with a button offering to open `launch.json`.**
Something in the configuration asked the debug adapter for a feature it does not have on
Windows, and the launch was abandoned before your breakpoints were reached. The usual culprit
is `"console": "integratedTerminal"` (or the older `"runInTerminal": true`) — lldb-dap does not
implement it on Windows. Delete that line. This template ships without it, so if you see this
pop-up, check whether the line was added back.

Without it, your program opens **its own console window**: that is where its output appears and
where `std::cin` reads from. Look for the new window rather than the Debug Console.

**"Unable to find the lldb-dap binary" / the debug type `lldb-dap` is not recognised.**
Either the extension is missing or the adapter is not on your PATH. Check both — first that
**LLDB DAP** (publisher LLVM) appears in the Extensions panel, then, in a **new** terminal:

```powershell
Get-Command lldb-dap
```

It should print a path ending in `clang64\bin\lldb-dap.exe` (or `clangarm64\bin\...` on an
ARM machine). If it prints nothing, your PATH is not set — see the Troubleshooting section of
the setup guide, and remember that PATH changes need a restart and a fresh terminal. As a
stopgap you can name the adapter explicitly: uncomment the matching `lldb-dap.executable-path`
line in `.vscode/settings.json`. Only as a stopgap, though — that path is machine-specific and
must not be committed.

**`undefined symbol: std::__1::cout` from `ld.lld`, and the error line starts with `clang:`.**
Two tells here, and together they say the build never went through `CMakeLists.txt`. The driver
prints the name it was invoked under, so `clang:` means **`clang.exe`** ran, not `clang++.exe` —
and the object file it names is in `AppData\Local\Temp\`, where a single compile-and-link
command puts it. A CMake build writes to `build\CMakeFiles\app.dir\src\main.cpp.o` instead.

What ran was the C/C++ extension's **Run C/C++ File** — the ▷ button at the top-right of the
editor — which compiles the open file on its own. `clang` is the **C** driver: it finds the
libc++ headers (that is where `std::__1::` comes from — `__1` is libc++'s internal version
namespace) but never links the libc++ *library*, so every `std::` symbol is undefined at link
time. `clang++` is the same program under a different name, and the name is what adds the C++
standard library to the link.

Fix: build with **F7** and run with **F5**, not the ▷ button — and delete `.vscode/tasks.json`
if one has appeared, because the C/C++ extension wrote it and it will keep hijacking your builds.
To compile one file by hand, use `clang++ -std=c++20 -Wall -Wextra -g src\main.cpp -o main.exe`.

If F7 gives the **same** error, with the object file under `build\CMakeFiles\` this time, then
CMake itself is using the C driver: run **CMake: Select a Kit** and choose the entry whose C++
compiler is `clang++.exe`.

**"Could not find the task 'CMake: build'".**
CMake Tools has not activated. Run **CMake: Configure** once from the Command Palette
(`Ctrl + Shift + P`), then press F5 again. If it persists, delete the `preLaunchTask`
line from `launch.json` and build with **F7** before debugging.

**CMake picks the wrong compiler, or looks for Visual Studio.**
The generator is set in `.vscode/settings.json` (`"cmake.generator": "MinGW Makefiles"`).
If a `build/` folder was created before that was in place, delete `build/` and re-configure.
Check that `CC` and `CXX` point at `clang`/`clang++` — the setup script sets them.

**IntelliSense squiggles under code that compiles fine.**
`C_Cpp.default.configurationProvider` is set to CMake Tools, so IntelliSense follows the
real build — but only after a successful configure. Run **CMake: Configure**, then
**C/C++: Reset IntelliSense Database** from the Command Palette.

**The debugger runs but shows machine code, not my source.**
The build has no debug info. The default build type here is Debug; check the status bar
does not say Release, and re-configure with `-DCMAKE_BUILD_TYPE=Debug` if you built by hand.

**`clang++`, `lldb`, or `cmake` is "not recognized as a command".**
PATH problem, not a project problem — see the Troubleshooting section of the setup guide.
Restart the machine after any install, and open a **new** terminal.
