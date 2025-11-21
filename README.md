
# z80-semi
SimulIDE z-80 for teaching

- Download **SimulIDE** from [SimulIDE](https://simulide.com/p/)
### 2 choices here (choose just one):
#### 1. WSL
- Install `Debian` from the Microsoft Store
- get to `bash` prompt and run:
  ```bash
  sudo apt update
  sudo apt install sdcc make
  ```
#### 2. Windows Native Tools
- Download **SDCC** compiler from [SDCC site](https://sdcc.sourceforge.net/) and make sure `sdcc` and `sdobjcopy` are in current user's `path`
- Download **GNU make** from [SourceForge](https://gnuwin32.sourceforge.net/downlinks/make.php) and add `make.exe` to current user's `path`
#### Clone this repo to your computer
- see `sim` directory for hardware
- see `src` directory for sample C code
- add `subcircuits` folder as User data
  - click gear icon on top left of schematics, point `User data folder:` to wherever `subcircuits` folder from this repo is.
  - close and restart SimulIDE
  - now you should see Components class `My Subcircuits` near the bottom of components list on the left. There should at least be an `exor` component that can be dragged to the schematics.
- Code build instructions for Windows x64:

  Compile with
  ```
  sdcc -mz80 --no-std-crt0 --code-loc 0x0000 --data-loc 0x8000 --std c99 --Werror code-a.c
  ```
  convert to bin with
  ```
  sdobjcopy -I ihex -O binary code-a.ihx code-a.bin
  ```
- Open SimulIDE and click on ROM and load `code-a.bin`
- start simulation, strobe reset and see content in RAM.
