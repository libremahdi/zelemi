# Zero Level Machine Interpreter (Tiny)

This interpreter operates at a zero level; there are no abstractions, and everything you write is exactly what the processor sees and executes. This project serves as an educational example and is not recommended for professional use or serious development. However, theoretically, there are no limitations to what this interpreter can accomplish.

There are a series of basic commands such as RUN, ADR, CLR, etc., which do not affect the machine code and serve as management commands for the interpreter. The machine codes are entered into the software in hexadecimal format and are executed once the RUN command is entered.

There are also some internal commands and functions of the interpreter, and the addresses of these functions are made available to the programmer so that, depending on the hardware architecture, they can call the appropriate function. The reason the interpreter does not handle the machine code for calling the function and then generating an interrupt is to adhere to the principle that "zelemi has no abstractions."

## Installation
The zelemi project has only one dependency, which is the pgetopt project. Before installing zelemi, ensure that version 4.3 of the pgetopt library is installed, and then proceed with the following instructions.

```bash
git clone https://github.com/libremahdi/zelemi.git
cd zelemi
```

Create a temporary folder and enter it.
```
mkdir -p build
cd build/
```

Now, execute the following commands in order and Compile..
```bash
cmake ..
make
sudo make install # for Install
```

To uninstall, simply go to the same temporary build folder and, after running the make and cmake commands, use the following command:

```bash
sudo make uninstall # for Uninstall
```

## Use and Examples

In the `example` folder, you can find a number of simple examples in machine language specific to x86_64 Unix.

To execute a file, simply write:

```
zelemi run file.mi
```

After installation, go to the example folder and run the file hello-world.mi as follows:

```
$ zelemi run hello-world.mi
Hello World!
```
If you don't provide any input and just type `zelemi run`, it will run in console mode.

## License

This project is developed under the **BSD 3-Clause** License. For more information, please read the `LICENSE` file.