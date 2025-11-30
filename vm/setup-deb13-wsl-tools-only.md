## Debian 13 WSL Setup for sdcc / sdz80asm *without SimulIDE*
### Install Windows Subsystem for Linux (WSL)
Click start and type:
```
turn windows features on or off
```
scroll down and check `Windows Subsystem for Linux`.

Reboot if necessary.
### Check your current WSL version:
Type `Win+R` and run `cmd` or `powershell`:
```
wsl --version
```
If it says `WSL version: 2.x`, you're ok,
> but if it is `1.x`, you must update `WSL` to `WSL2` by:
> ```
> wsl --update
> ```
> Reboot if necessary.

Now do the safety check.
```
wsl --list
```
If it contains `Debian`, proceed at your own risk!
### Install Debian
```
wsl --install Debian
```
This will take a while. You'll be asked for a new username. I suggest `dev` and just add a simple password (type it twice). We won't be doing anything unsecure on this machine.
### update `sudo` so we can do it without password
Your prompt should now read: `dev@something:/mnt/c/Users/name$`, type:
```bash
sudo visudo
```
give the password. scroll down this file until you see: `%sudo   ALL=(ALL:ALL) ALL`. Add a new line below it and type:
```
dev ALL=(ALL) NOPASSWD: ALL
```
so now that part reads:
```
# Allow...
%sudo   ALL=(ALL:ALL) ALL
dev ALL=(ALL) NOPASSWD: ALL

# See...
```
Type: `ctrl-o`, type `enter`, then `ctrl-x`, you will be back at `dev@something:/mnt/c/Users/name$`
### Print out distro name and alias `l` `ll` `la`
```bash
sed -i -E '/^#alias (l|ll|la)=/s/^#//' ~/.bashrc

cat << 'EOF' >> ~/.bashrc

# --- Distro display ---
if [ -f /etc/os-release ]; then
    . /etc/os-release
    PS1="(${ID^}) $PS1"
fi
EOF
```
### Optional but very nice `gocode` alias
You need to modify `YOURNAME` and `YOURPATH` to match your environment. Then,
```bash
cat << 'EOF' >> ~/.bashrc

alias gocode='cd /mnt/c/Users/YOURNAME/YOURPATH/BareMetal-C-Labs/code/'
EOF
```
and run it
```bash
source ~/.bashrc
```
Now your prompt will be: `(Debian) dev@something:/mnt/c/Users/name$`
### Update system
```bash
sudo apt update && sudo apt upgrade -y
```
### Install other utilities besides simulide/sdcc/z80dasm
```bash
sudo apt install -y sdcc git z80dasm make man manpages bash-completion
```
### Try `sdcc`, `sdasz80`, `z80dasm`
Make sure we're on the latest `.bashrc`
```bash
source ~/.bashrc
```
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
### Log out and set WSL networking to `Mirrored`
At the prompt:
```bash
(Debian) dev@something:/mnt/c/Users/name$
```
type
```
sudo poweroff
```
You will be returned to Windows, with something similar to `C:\Users\username> `

click windows start menu, type in `wsl settings` and run it (the blue-head penguin).

Click `Networking` tab on the left. On the right, select `Networking Mode` to be `Mirrored`.
#### Double check that your networking is now `mirrored`:
Check for the content of file: `C:\Users\NAME\.wslconfig` and it should have this section:
```
[wsl2]
networkingMode=Mirrored
```
### Restart WSL
Either:
- Open start menu and look for `Debian` and run it
- Start `cmd` and run:
  ```
  wsl -d Debian
  ```
You will be back at `(Debian) dev@something:/mnt/c/Users/name$` prompt.
