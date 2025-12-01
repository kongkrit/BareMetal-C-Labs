# BareMetal-C Tool Setup for Windows / macOS

---
## 1. (Windows & macOS) Install Github Desktop
- Download GitHub desktop from [here](https://desktop.github.com/download/)
- Run it. You don't need to sign up, but you need to provide an email address and name. It's best that you **do not share** email addresses with friends.
- Click **Clone a repository from the internet** and select **URL**.
- Clone the following URL:
  ```
  https://github.com/kongkrit/BareMetal-C-Labs
  ```
- Choose **Local path**. Recommendations:
  - **(Windows & macOS):** Your `Documents` folder is probably ok.
- Click `Clone` and wait for it to finish. Now everything resides in `~/Documents/BareMetal-C-Labs` folder.

---
## 2. (Windows & macOS) Install Docker Desktop 

- **ALL:** Make sure you have *admin rights* on your computer. That is, you can install new programs for all users, etc.
- **ALL:** Make sure you don't have anything important running. `Docker Desktop` may force you to log out to complete the installation.
- **ALL:** Download and install `Docker Desktop`. Click *Download Docker Destop* and choose the drop down that matches your computer's CPU:
  - **Windows:** Choose `Windows AMD64`
  - **macOS (with M-series chip):** `Mac - Apple Silicon`
  - **old macOS (with Intel CPU):** `Mac - Intel Chip`
- Download **Docker Desktop** from this [link](https://www.docker.com/products/docker-desktop/).

### For Windows & macOS
- `Accept` Docker Subscription Service Agreement. It's free for personal use.

> ### For Windows:
> - Check `☑ Use WSL 2 instead of Hyper-V`
> - You can skip all the questions
---
> ### For macOS:
> - Drag and drop `Docker` into your `Applications` folder
> - Run `Docker` - and select `Use recommended settings`
> - You can skip all the questions
> - Accept all the permissions
> - Wait for the docker icon (a whale with containers on top) on menu bar stop dancing.

---
## 3. Pull the software container

> ### For Windows:
> - Open **File Explorer** and go to where your project is from GitHub clone above (`~/Documents/BareMetal-C-Labs`) was recommended.
> - Go into `BareMetal-C-Labs\code` folder
> - **Shift + Right-click** inside the `BareMetal-C-Labs\code` folder window, and select `Open PowerShell window here` or `Open in Terminal`
> - You now have a terminal with prompt:
>   `PS C:\Users\NAME\Documents\BareMetal-C-Labs\code>`
> ### For MacOS
> - Use **Finder** and go to where your project is from GitHub clone above (`~/Documents/BareMetal-C-Labs`) was recommended.
> - Go into `BareMetal-C-Labs\code` folder
> - Type `Command + space` and type `terminal` and you get a terminal window
> - type "`cd `" (`cd` and one space after)
> - drage `code` folder from **Finder** into terminal. terminal now reads: `cd /Users/NAME/Documents/BareMetal-C-Labs/code` and hit `enter`. Your prompt will be:
>   `name@computername code %`

---
## 4. Launching the tool environment (also called **tool-prompt**)
### For both Windows and macOS:
Copy and paste the command below:
```
docker run --name baremetal-c --rm -it -v ${PWD}:/code kongkrit/baremetal-c
```
> (**For macOS:** If `terminal` or `docker` asks you for any permission, give it)
> 
It will take a while for the first time, but you will end up with a prompt:
```
[baremetal-c]:/code$
```
If you get the above prompt, your installation is successful.

---
## 4. Test the tools (same for Windows and macOS)

- Type all the commands from `[baremetal-c]:/code$` prompt (from now on, we will call `[baremetal-c]:/code$` the **tool-prompt** to indicate that you can only run tools from here):
### Check `sdcc` `z80dasm` and `make` -- all from **tool-prompt**:
Check `sdcc`:
```bash
sdcc --version
```
It should say: `SDCC : mcs51/z80/.../f8 TD- 4.5.0 #15242 (Linux)`

Check `sdasz80`:
```bash
sdasz80 2>&1 | head -n 3
```
It should say: `sdas Assembler V02.00 + NoICE + SDCC mods  (Zilog Z80...)`

Check `z80dasm`:
```bash
z80dasm -V
```
It should say: `z80dasm, Z80 assembly language generating disassembler...`

Check compilation:
```bash
make 000-run.bin
```
and it should say:
```
[baremetal-c]:/code$ make 000-run.bin
sdasz80 -l -o default-startup.rel default-startup.s
cp default-startup.rel 000-startup.rel
cp default-startup.lst 000-startup.lst
sdcc -mz80 --std c99 --Werror -c 000-test-mem-nmi.c -o 000-test-mem-nmi.rel
sdcc -mz80 --no-std-crt0 000-startup.rel 000-test-mem-nmi.rel  -Wl-u -Wl-f,000-memmap.ld -o 000-run.ihx

Generating Binary and Disassembly 000-run.bin and 000-run.txs...

sdobjcopy -I ihex -O binary 000-run.ihx 000-run.bin
z80dasm -a -l -t -z -g0 000-run.bin | awk ' BEGIN { count = 0; } /^[ \t]+nop[ \t]+;[0-9a-fA-F]{4}[ \t]+00.*$/ { buffer[count++] = $0; next; } { if (count > 3) { print buffer[0]; print "    ..."; print buffer[count-1]; } else { for (i=0; i<count; i++) print buffer[i]; } count = 0; print $0; } END { if (count > 3) { print buffer[0]; print "    ..."; print buffer[count-1]; } else { for (i=0; i<count; i++) print buffer[i]; } }' > 000-run.txs
Warning: Code might not be 8080 compatible!

Info: 8080 incompatibility warning can be ignored.
```
and finally
```
make clean
```
and it should say:
> ```
> [baremetal-c]:/code$ make clean
> rm -f *.asm *.bin *.ihx *.lk *.lst *.map *.noi *.rel *.rst *.sym *.txs
> ```

---
## 5. How to logout of the tool prompt.
and get back to `tool-prompt`:

Log out of **tool-prompt**. Easy. type `ctrl+d` or type `exit` and you will see:
> ```
> [baremetal-c]:/code$
> exit
> ```
and the prompt changes to `PS C:\...` (Windows), or `name@computername code %` (macOS)

---
## 6. How to get back to the **tool-prompt**:
Easy. Make sure you're in the correct folder (`BareMetal-C-Labs`) and repeat step 4. above.