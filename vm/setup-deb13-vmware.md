## Debian 13 VM Setup for SimulIDE
### After Installation
`root` and `dev` password is `c` - single character
Become `root` and add `sudo`:
```bash
su -
```
and then
```bash
apt install sudo
usermod -aG sudo dev
```
log out and log in again
### 0. low level setup and sudo without providing password
```bash
sudo visudo
```
scroll below `%sudo   ALL=(ALL:ALL) ALL` and add
```
dev    ALL=(ALL) NOPASSWD: ALL
```
and logout of root shell.

set time zone correctly
```bash
sudo timedatectl set-timezone Asia/Bangkok
```
set locale
```bash
sudo locale-gen en_US.UTF-8
```
```bash
sudo nano /etc/environment
```
and add the following to the top of `/etc/environment` (if it exists)
```bash
LANG="en_US.UTF-8"
LC_ALL="en_US.UTF-8"
LC_CTYPE="en_US.UTF-8"
```
log out and log in, you should see no: `-bash: warning: setlocale: LC_CTYPE: cannot change locale (UTF-8): No such file or directory` warnings.
### prettify and add useful bash aliases
> add the following to the tail of `~/.bash_profile`
> ```bash
> if [ -f ~/.bashrc ]; then
>   . ~/.bashrc
> fi
> ```
in `~/.bashrc`, uncomment:
```bash
alias ll='ls -l'
alias la='ls -A'
alias l='ls -CF'
```
> prompt customization to show distro name. add to tail of `.bashrc`
> ```bash
> # --- DISTRO PROMPT CUSTOMIZATION ---
> if [ -f /etc/os-release ]; then
>     . /etc/os-release
>     PS1="(${ID^}) $PS1"
> fi
> ```
### 1. make sure debian is up to date
```bash
sudo apt update
```
```bash
sudo apt upgrade -y
```
### 2. eliminate grub timeout
```bash
sudo nano /etc/default/grub
```
and set `GRUB_TIMEOUT=1`
```bash
sudo update-grub
```
### 3. install utilities besides simulide
```bash
sudo apt install -y sdcc git z80dasm make man manpages bash-completion -y
```
### 4. install simulide to keep its dependency and remove just simulide itself
```bash
sudo apt install simulide
```
then remove it so its dependency still remains:
```bash
sudo apt remove simulide
```
### add shared folder support to UTM
```bash
sudo apt install virtiofsd
```
create share mount point
```bash
sudo mkdir -p /mnt/share
```
Assuming your shared folder tag (UTM “Name”) is `shared`:
```bash
sudo mount -t 9p -o trans=virtio,version=9p2000.L share /mnt/share
```
### 5. add simulide appimage
as a normal user
```bash
mkdir -p ~/.local/share
cd ~/.local/share
```
add appimage simulide downloaded from simulide.com (SimulIDE_1.1.0-SR1_Lin64.tar.gz) to `~/.local/share`
```bash
tar -xvf SimulIDE_1.1.0-SR1_Lin64.tar.gz
```
> #### for Windows VMware
> add `libfuse2t64`
> ```bash
> sudo apt install libfuse2t64
> ```
> #### for UTM
> add `libfuse3`
> ```bash
> sudo apt install fuse3
> ```
#### other stuff that may be necessary
`sudo apt install libgpg-error0`
### 6. add simulide to PATH
do it only once.
```bash
echo 'export PATH="$HOME/.local/share/SimulIDE_1.1.0-SR1_Lin64:$PATH"' >> ~/.bashrc
```
> ### 8. Possible additonal quality of life installations
> `clang cmake`
