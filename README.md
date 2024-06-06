# GRIV
Graph Reduction In Verilog

Graph reduction is a method of evaluating expressions.  Here I implement a graph reduction machine in System Verilog, along with a compiler to turn a lambda calculus based language into an intermediate representation suitable for the GRIV machine.

## Usage

Clone this repo recursively to pull both GRIV and GRIVc
```shell
git clone https://github.com/ellie-bee/griv_main.git --recursive
```

### grivc
build with Make
```shell
make all
```
Once built, you can run the tests using `make test`.  The compiled binary for grivc is placed into `grivc/bin/grivc`

### griv
None of the RTL has been implemented yet :lmao: