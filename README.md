# HelpGUI

HelpGUI presents `.help` — a file format for help docs. It can contain images, styled text (sizes, colors), links (with a security popup before opening), and tabs that hold pages — all stored in a single, simple file.

## Status

Pre-release. No builds yet, design in progress.

## Compiling it yourself

notice the project isn't build yet and its pre-release, but if you want to know to compile later, heres is it

Requirements:

- **MinGW-w64** (or GCC) — a C++ compiler
- **Git** — to clone the repo

Clone and build:

```bash
git clone https://github.com/Itz-korosh/HelpGUI.git
cd HelpGUI
g++ -std=c++17 -mwindows -static main.cpp -o HelpGUI.exe
```

Then run `HelpGUI.exe`.

*(A Makefile is planned so `make` will do this in one step.)*

## License

MIT © 2026 Korosh Jale — see [LICENSE](LICENSE).