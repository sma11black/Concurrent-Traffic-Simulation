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
CMakeLists.txt 右击 -> Debug and Launch Settings -> ...

```json
  "configurations": [
    {
      ...,
      "currentDir": "${workspaceRoot}\\src"
    }
  ]
```

如果不设置运行目录，加载的图片相对路径会错误，从而导致cv::imread无法获取图像，在cv::imshow时出现内存异常.

## Key Points

###	Running Threads
thread()
async()

### Passing Data Between Threads
future = promise.get_future()
future.wait()
promise.set_value()

future = std::async(...)
future.get()

### Mutex and Lock
mutex

lock_guard
unique_lock
