# z80-semi
SimulIDE z-80 for teaching

- Download **SDCC** compiler from [SDCC site](https://sdcc.sourceforge.net/)
- Download **SimulIDE** from [SimulIDE](https://simulide.com/p/)
- see `sim` directory for hardware
- see `src` directory for sample C code
- add `subcircuits` folder as User data
  - click gear icon on top left of circuit board, point `User data folder:` to wherever `subcircuits` folder from this repo is.
  - close and restart SimulIDE
  - now you should see Components class `My Subcircuits` near the bottom of components list on the left.
- Code build instructions for Windows x64
  Compile with
  ```
  sdcc -mz80 --no-std-crt0 --code-loc 0x0000 --data-loc 0x8000 main.c
  ```
  convert to bin with
  ```
  sdobjcopy -I ihex -O binary main.ihx main.bin
  ```
- Open SimulIDE and click on ROM and load `main.bin`
- start simulation, strobe reset and see content in RAM.
