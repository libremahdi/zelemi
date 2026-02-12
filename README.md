# Tiny Machine Interpreter

This interpreter operates at a zero level; there are no abstractions, and everything you write is exactly what the processor sees and executes. This project serves as an educational example and is not recommended for professional use or serious development. However, theoretically, there are no limitations to what this interpreter can accomplish.

Its installation and execution are very easy and straightforward due to its zero-dependency nature.

## Installation

To Compile, simply use GCC or Clang to compile and execute the following command:


```bash
clang -O3 -Ilib/ -Istring *.c string/*.c -o [OUTPUT-FILE]
```

However, to install it on the system, simply run the command `sudo make` in the source code directory.
To remove it, simply run: sudo make clean.

## Use and Examples

In the `example` folder, you can find a number of simple examples in machine language specific to x86_64 Unix.

To execute a file, simply write:

```
zelemi file.mi
```

If you don't provide any input and just type `zelemi`, it will run in console mode.

## License

This project is developed under the **BSD 3-Clause** License. For more information, please read the `LICENSE` file.