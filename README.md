# Eon

This repository was created for **learning purposes** only. Everything that I coded might be a bad idea.

---

## Installation

- **Prerequisites**
  - CMake
  - C++ Compiler (eg. Clang, GCC, MSVC)

- **Clone Repositories**
  - ```bash
    git clone https://github.com/jeanersten/Eon.git && cd Eon
    ```

- **Update Submodule**
  - ```bash
    git submodule update --init --recursive
    ```

- **Building**
  - **With tools.sh**: In order to generate build files you can use the tools.sh script
    if you have shell script invoker, in Linux this should be supported,
    in Windows you can use Git shell script invoker if it's listed on the
    environment variable path, I don't know about MacOS. You can then run:
    ```bash
    sh tool.sh
    ```
    This will show of what the script can do. It's useful if you don't
    use IDE, you can generate/build/run the program via terminal.

  - **Without tools.sh**: If you don't have shell script invoker you can run:
    ```bash
    cmake -G <generator (eg. Unix Makefiles/Ninja)> -B <build directory>
    ```
    This will generate build files of your preferred generator to build directory.
