# BareMetal-C-Labs
- [x] 1. Setup Tools by clicking [here](https://github.com/kongkrit/BareMetal-C-Labs/blob/main/setup/1-setup-tools.md).
- [ ] 2. Setup `SimulIDE` by clicking [here](https://github.com/kongkrit/BareMetal-C-Labs/blob/main/setup/2-setup-simulide.md).
- [ ] 3. Setup `VS Code` by clicking [here](https://github.com/kongkrit/BareMetal-C-Labs/blob/main/setup/3-setup-vs-code.md).

## Peripherals designed
- [x] 1. 0xC000-0xC003 toggle switches
- [x] 2. 0xE000-0xE003 LEDs
- [ ] 3. numerical keypad read2clr
- [ ] 4. directional keypad read2clr

---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
## unfinished section
## ignore text below:
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
SimulIDE z-80 for teaching

- Download and unzip **SimulIDE** from [SimulIDE](https://simulide.com/p/)
- Download and install [**GitHub Desktop**](https://desktop.github.com/download/)
### 3 choices here - depending on your OS (choose just one):
> #### 1a. Window WSL (highly recommended)
> - follow detailed instructions [here](https://github.com/kongkrit/z80-semi/blob/main/vm/setup-deb13-wsl-tools-only.md).
> #### 1b. Windows Native Tools
> - Download **SDCC** compiler from [SDCC site](https://sdcc.sourceforge.net/) and make sure `sdcc` and `sdobjcopy` are in current user's `path`
> - Download **GNU make** from [SourceForge](https://gnuwin32.sourceforge.net/downlinks/make.php) and add `make.exe` to current user's `path`
> #### 2. Linux host (we only support [Debian](https://www.debian.org/))
> - You need to adjust from the instructions [here](https://github.com/kongkrit/z80-semi/blob/main/vm/setup-deb13-wsl-tools-simulde.md) or [here](https://github.com/kongkrit/z80-semi/blob/main/vm/setup-deb13-vmware.md).
> #### 3. MacOS native through `brew`
> - Install [brew](https://brew.sh/) and follows the last lines of instructions
>   open the terminal and copy and paste the following (`FOO` is replaced by your `username`):
>   ```bash
>   echo >> /Users/FOO/.zprofile
>   echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> /Users/FOO/.zprofile\
>   eval "$(/opt/homebrew/bin/brew shellenv)"
>   ```
>   Use  `brew` to install `sdcc` and `z80dasm`:
>   ```bash
>   brew install sdcc
>   brew install z80dasm
>   ```
#### Clone this repo to your computer
- see `sim` directory for hardware
- see `code` directory for sample C code
- add `subcircuits` folder as User data
  - click gear icon on top left of schematics, point `User data folder:` to wherever `subcircuits` folder from this repo is.
  - close and restart SimulIDE
  - now you should see Components class `My Subcircuits` near the bottom of components list on the left. There should at least be an `exor` component that can be dragged to the schematics.
- Code build instructions: 
  - For WSL Windows x64:
    
    Run `wsl` that you installed. From `(Debian)` prompt. `cd` into `code` folder and type:
    ```
    make 001-run.bin
    ```
    you should see output like:
    ```
    sdasz80 -l -o default-startup.rel default-startup.s
    cp default-startup.rel 001-startup.rel
    cp default-startup.lst 001-startup.lst
    sdcc -mz80 --std c99 --Werror -c 001-test-mem.c -o 001-test-mem.rel
    sdcc -mz80 --std c99 --Werror -c default-nmi_handler.c -o default-nmi_handler.rel
    cp default-nmi_handler.rel 001-nmi_handler.rel
    cp default-nmi_handler.lst 001-nmi_handler.lst
    sdcc -mz80 --no-std-crt0 001-startup.rel 001-test-mem.rel 001-nmi_handler.rel -Wl-u -Wl-f,001-memmap.ld -o 001-run.ihx

    Generating Binary and Disassembly 001-run.bin and 001-run.txs...

    sdobjcopy -I ihex -O binary 001-run.ihx 001-run.bin
    z80dasm -a -l -t -z -g0 001-run.bin ...
    Warning: Code might not be 8080 compatible!
    
    Info: 8080 incompatibility warning can be ignored.
    ```
    If this is the case, you're ready to go.
  - For Debian Linux:
    This is similar to Windows x64 case, since you're already on Linux.
  - For macOS:
 
    Open `terminal` and `cd` into `code` folder. Follow WSL for Windows intructions
- Open SimulIDE. Right click on ROM and select `Load data`. Use `.bin` file from your `code` folder as data.
- Click the red square button to start simulation.
