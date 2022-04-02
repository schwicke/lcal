# (Yet another) Command line calculator tool

```lcal``` is a command line calculator tool, written in C++. It supports a larger range of mathematical functions than ```bc```, including trigonometrical functions, as well as some constants like ```e```  and ```Pi```.

## Building
```bash
autogen.sh
./configure --prefix /path/to/where/it/should/be/installed
make
sudo make install
```
## Usage
On the command prompt type lcal, followed by the expression you want to evaluate. Note: some may characters need to be escaped, or put the whole expressions into quotes.

## Examples
```
bash> lcal 1+1
2

bash> lcal "4*atan(1.0)"
3.14159

bash> lcal "log(e)"
1

bash> lcal '2^(1/2)'
1.41421

```
