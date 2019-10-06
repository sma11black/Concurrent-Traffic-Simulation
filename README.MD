## ENV

### vcpkg

```shell
.\vcpkg.exe install opencv4
```

### CMakeSettings.json

```json
  "configurations": [
    {
      "name": "x86-Debug",
      ...,
      "buildCommandArgs": "-m -v:minimal",
      ...,
      "variables": [
        {
          "name": "CMAKE_TOOLCHAIN_FILE",
          "value": "D:\\Workspace\\VisualStudioProjects\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake"
        }
      ]
    },
```

### launch.vs.json

```json
"configurations": [
    {
      ...,
      "currentDir": "${workspaceRoot}\\src"
    }
  ]
```
