# Zero Level Machine Interpreter (Tiny)

This interpreter operates at a zero level; there are no abstractions, and everything you write is exactly what the processor sees and executes. This project serves as an educational example and is not recommended for professional use or serious development. However, theoretically, there are no limitations to what this interpreter can accomplish.

Its installation and execution are very easy and straightforward due to its zero-dependency nature.

## Installation
For installation, First Download the project..

```bash
git clone https://github.com/libremahdi/zelemi.git
cd zelemi
```

Then, Create a desired folder and navigate into it.

```bash
mkdir -p build
cd build/
```

Now, execute the following commands in order.

```bash
cmake ..
make
sudo make install # for Install
sudo make uninstall # for Uninstall
```

## Use and Examples

In the `example` folder, you can find a number of simple examples in machine language specific to x86_64 Unix.

To execute a file, simply write:

```
zelemi file.mi
```

After installation, go to the example folder and run the file hello-world.mi as follows:

```
$ zelemi hello-world.mi
Hello World!
```
If you don't provide any input and just type `zelemi`, it will run in console mode.

## License

This project is developed under the **BSD 3-Clause** License. For more information, please read the `LICENSE` file.