## BareMetal-C Tool Setup for Windows / macOS
### 1. Install Docker Desktop
- **ALL:** Make sure you have *admin rights* on your computer. That is, you can install new programs for all users, etc.
- **ALL:** Make sure you don't have anything important running. `Docker Desktop` may force you to log out to complete the installation.
- **ALL:** Download and install `Docker Desktop`. Click *Download Docker Destop* and choose the drop down that matches your computer's CPU: `Windows AMD64`, `Mac - Apple Silicon`, or `Mac - Intel Chip`. Download [link](https://www.docker.com/products/docker-desktop/).
- **Windows:** Check `☑ Use WSL 2 instead of Hyper-V`
- **macOS:**
- **ALL:** `Accept` Docker Subscription Service Agreement. It's free for personal use.
- **ALL:** login?

---
---
---

# For Students:
---
## For Windows Students (PowerShell):

1. `Shift + Right-click` inside the `BareMetal-C-Labs\code` folder window.
2. Click `Open PowerShell window here` or `Open in Terminal`.
3. Paste this command:
```PowerShell
docker run --name baremetal-c --rm -it -v ${PWD}:/code kongkrit/baremetal-c
```
## For Mac Students (Terminal):
1. Open Terminal.
2. Type `cd` and drag the `z80_lab` folder into the window to go there.
3. Paste this:
```bash
docker run --name baremetal-c --rm -it -v $(pwd):/code kongkrit/baremetal-c
```
