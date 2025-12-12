# VS Code & Docker Sidecar Setup Guide

This guide covers the installation of Visual Studio Code and Docker Desktop for macOS and Windows, and details how to integrate the `baremetal-c` container as a development sidecar.

## 1. Prerequisites: Tools and SimulIDE installation

Before setting up VS Code, ensure the tools (which includes Docker Desktop) and SimulIDE are installed and running, as the sidecar depends on it.

- Instructions for installing tools [here](./1-setup-tools.md).
- Instructions for installing SimulIDE [here](./2-setup-simulide.md).

---

## 2. VS Code Installation

### macOS
1.  **Download:** Visit [code.visualstudio.com](https://code.visualstudio.com/) and download the Universal build for macOS.
2.  **Install:** Open the downloaded `.zip` file and drag `Visual Studio Code.app` to your **Applications** folder.
3.  **Add to Path (Optional but recommended):**
    * Open VS Code.
    * Press `Cmd + Shift + P` to open the Command Palette.
    * Type `Shell Command: Install 'code' command in PATH` and select it. This allows you to type `code .` in your terminal.

### Windows
1.  **Download:** Visit [code.visualstudio.com](https://code.visualstudio.com/) and download the User Installer (x64).
2.  **Install:** Run the installer.
3.  **Select Options:** During installation, check the following boxes for a better experience:
    * "Add 'Open with Code' action to Windows Explorer file context menu"
    * "Add 'Open with Code' action to Windows Explorer directory context menu"
    * "Add to PATH"

---

## 3. Integrating the Sidecar

We will configure VS Code to run your Docker container command as a native **Task**. This allows you to launch the baremetal tools environment directly from the IDE with a single click or keyboard shortcut.

### Step 1: Open Your Project
Open the folder containing your C code in VS Code.

### Step 2: Configure the Task
1.  Press `Cmd + Shift + P` (macOS) or `Ctrl + Shift + P` (Windows).
2.  Type **"Tasks: Open User Tasks"** (or "Tasks: Configure Task" if you want it specific to just this project folder).
3.  Select **"Others"** if prompted.
4.  This will open a `tasks.json` file. Replace its content with the configuration below. 

This configuration automatically handles the path mapping (`${PWD}`) using VS Code's internal variables (`${workspaceFolder}`), ensuring it works seamlessly on both Windows and macOS without syntax errors.

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Start Baremetal Sidecar",
            "type": "shell",
            "command": "docker",
            "args": [
                "run",
                "--name", "baremetal-c",
                "--rm",
                "-it",
                "-v", "${workspaceFolder}:/labs",
                "kongkrit/baremetal-c"
            ],
            "isBackground": false,
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": true,
                "panel": "dedicated",
                "clear": true
            },
            "problemMatcher": []
        }
    ]
}
```

### Step 3: Running the Sidecar

1. Press `Cmd + Shift + P` (macOS) or `Ctrl + Shift + P` (Windows).
2. Type **"Tasks: Run Task"**.
3. Select **"Start Baremetal Sidecar"**.

A new terminal window will open inside VS Code, dropping you directly into the `/labs` directory inside the container. You can now compile and run your tools (e.g., `make`, `gcc`, etc.) while editing your files in VS Code.

---

## 4. Manual Terminal Command (Alternative)
If you prefer to run the command manually in a terminal, use the syntax specific to your OS shell.

**PowerShell (Windows) or Terminal (macOS):**

```bash
docker run --name baremetal-c --rm -it -v ${PWD}:/labs kongkrit/baremetal-c
```

**Command Prompt (Windows cmd.exe):**

```DOS
docker run --name baremetal-c --rm -it -v %cd%:/labs kongkrit/baremetal-c
```
