# END HERE
# END HERE
---

```
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "1. Start/Reset Build Server",
            "type": "shell",
            "windows": {
                "command": "docker rm -f baremetal-c ; docker run -d --name baremetal-c --rm -v \"${workspaceFolder}:/labs\" kongkrit/baremetal-c sleep infinity"
            },
            "osx": {
                "command": "docker rm -f baremetal-c || true && docker run -d --name baremetal-c --rm -v \"${workspaceFolder}:/labs\" kongkrit/baremetal-c sleep infinity"
            },
            "linux": {
                "command": "docker rm -f baremetal-c || true && docker run -d --name baremetal-c --rm -v \"${workspaceFolder}:/labs\" kongkrit/baremetal-c sleep infinity"
            },
            "runOptions": {
                "runOn": "folderOpen"
            },
            "presentation": {
                "echo": false,
                "reveal": "silent",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": [],
            "detail": "Auto-starts the docker container when VS Code opens."
        },
        {
            "label": "2. Build Project",
            "type": "shell",
            "command": "docker",
            "args": [
                "exec",
                "baremetal-c",
                "make",
                "-C",
                "/labs/code"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": [],
            "detail": "Compiles code instantly inside the running server."
        },
        {
            "label": "3. Clean Project",
            "type": "shell",
            "command": "docker",
            "args": [
                "exec",
                "baremetal-c",
                "make",
                "-C",
                "/labs/code",
                "clean"
            ],
            "group": {
                "kind": "build",
                "isDefault": false
            },
            "presentation": {
                "echo": true,
                "reveal": "always",
                "panel": "shared"
            },
            "problemMatcher": [],
            "detail": "Removes build artifacts."
        },
        {
            "label": "4. Stop Build Server",
            "type": "shell",
            "command": "docker kill baremetal-c",
            "problemMatcher": [],
            "detail": "Manually stops the container."
        }
    ]
}
```


```
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "1. Start/Reset Build Server",
            "type": "shell",
            "windows": {
                "command": "docker rm -f baremetal-c ; docker run -d --name baremetal-c --rm -v \"${workspaceFolder}:/labs\" kongkrit/baremetal-c sleep infinity"
            },
            "osx": {
                "command": "docker rm -f baremetal-c || true && docker run -d --name baremetal-c --rm -v \"${workspaceFolder}:/labs\" kongkrit/baremetal-c sleep infinity"
            },
            "runOptions": {
                "runOn": "folderOpen"
            },
            "presentation": {
                "echo": false,
                "reveal": "silent",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": [],
            "detail": "Auto-starts the docker container when VS Code opens."
        },
        {
            "label": "2. Build Project",
            "type": "shell",
            "command": "docker exec baremetal-c make -C /labs/code",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [],
            "detail": "Compiles code instantly inside the running server."
        },
        {
            "label": "3. Stop Build Server",
            "type": "shell",
            "command": "docker kill baremetal-c",
            "problemMatcher": [],
            "detail": "Manually stops the container."
        }
    ]
}
```




### here's my .vscode/tasks.json
```
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build BareMetal C",
            "type": "shell",
            "command": "docker",
            "args": [
                "run",
                "--rm",
                "-v", "${workspaceFolder}:/labs",
                "kongkrit/baremetal-c",
                "make",
                "-C", "/labs/code"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": []
        }
    ]
}
```


2. suggest whether i should remove `--rm` flag from `docker run`. I don't want to rebuild the container every time. 

3. is it possible not to re-run docker every time student touches a .c file? That would be slow.




The Optimized Workflow
You can set up two tasks: one to Start the environment (run once per session) and one to Build (run repeatedly).

Here is the advanced tasks.json for this workflow:
```
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "1. Start Build Server",
            "type": "shell",
            "command": "docker run -d --name baremetal-c --rm -v \"${workspaceFolder}:/labs\" kongkrit/baremetal-c sleep infinity",
            "problemMatcher": [],
            "detail": "Run this once when you open VS Code."
        },
        {
            "label": "2. Build Project (Fast)",
            "type": "shell",
            "command": "docker exec baremetal-c make -C /labs/code",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [],
            "detail": "Compiles code instantly inside the running server."
        },
        {
            "label": "3. Stop Build Server",
            "type": "shell",
            "command": "docker stop baremetal-c",
            "problemMatcher": [],
            "detail": "Run this when you are done."
        }
    ]
}
```

---

Robust Auto-Start tasks.json
This configuration uses a trick: it chains commands to ensure a clean slate every time the folder is opened.

