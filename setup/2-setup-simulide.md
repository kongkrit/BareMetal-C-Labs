# setup simulide to be finished...

*In order to successfully install simulide, you must have installed the tools. See tools setup instructions [here](./1-setup-tools.md).*

---

## 1. Download and install SimulIDE:
- Download SimulIDE from [here](https://simulide.com/p/downloads/)
  - Select `Last Stable Version`, and select `Operating System` to be `Windows 64` for Windows and `MacOs x86` for macOS.
  - You may put in **`0`** as the donation amount. Then click `Download`.
- **macOS:** unzip the download and drag `simulide` to your `Applications` folder.
- **Windows:** unzip the download. Rename the folder from `SimulIDE_1.1.x...` to `simulide`. There's no installer for Windows. Change `NAME` to your *username* below:
  - Put `simulide` folder in: `C:\Users\NAME\Documents` so this file exists: `C:\Users\NAME\Documents\simulide\simulide.exe`

## **DOUBLE CHECK**

  - Go into `C:\Users\NAME\Documents\simulide\` folder, right click on `simulide.exe` and select `Pin to Start Menu`

## **DOUBLE CHECK**

---

## 2. Set class subcircuits
- Launch `simulide`. It will probably fail.
- **Windows:** You may get a prompt that `simulide` is a software downloaded from the internet. Allow it to run.
- **macOS:** Go to `System Settings` → `Privacy & Security` → scroll to bottom, you will see
  > ```
  > "simulide" was blocked to protect your Mac
  > ```
  - Click `Open Anyway`. Provide TouchID or password to allow it.
  - It may prompt: `To open this app, you need to install Rosetta. Do you want to install it now?`,  make sure you install *Rosetta*, or `simulide` will not work:
- You will get the main window that looks like this:
  - ![simulide main window](./1-simulide-window.png)

---

- Click the ⚙ gear icon on the top left (to the right of `Search Components` box
- Settings window appear. Select `App` tab. On the bottom there is:
  > ```
  > User Data folder:
  > <blank>            [ ... ]
  > ```
  - Click the `...` button and choose folder: `Documents/BareMetal-C-Labs/sim/subcircuits/`
- Restart `simulide`.
- On leftmost side, select `Components` tab, a column on components will show, starting from `Meters`, `Sources`, etc.
- Scroll down all the way to the bottom, you should see `BMC Subcircuits` and `BMC Subblocks`. These are the design used for our class.
- You can close `simulide` now. It's ready for use.
 
