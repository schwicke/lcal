# (Yet another) Command line calculator tool

```lcal``` is a command line calculator tool, written in C++. It supports a larger range of mathematical functions than ```bc```, including trigonometrical functions, as well as some constants like ```e```  and ```Pi```.

## Building
```bash
make
```
This will create a distrib/lcal folder with the resulting executable.

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
## Parsing
The code works in two passes: First, the string given by the user is being parsed and converted into an internal representation.
Then, it is this internal represantation which is actually being evaluated.

The main program lcal.cpp is more like a sample implementation on how to use this.

## Variables
lcal supports variables named ```x```, ```y``` or ```z```. At evaluation time, these are read from environment variables of the same name. These variables can contain mathematical terms themselves. So things like this work:

```
bash> export x='atan(1)'
bash> export y='4*x'
bash> lcal y
3.14159
```
