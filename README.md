# Decaff compiler

## Megh Parikh - 201501184

## Structure
- All AST nodes and some utils associated with them are in src/ast:
  - all.hpp -> contains all the header files
  - base_minimal.hpp -> minimal header file to be included in other header files which are included in base.hpp
  - base.hpp -> base header file
  - calls -> MethodCalls and Callouts ((they) subclass Expr)
  - context -> Used for semantic validation phase
  - ctx_data_type -> Data type for context
  - errors -> error handler
  - exit_block -> Get an exit block. Used in runtime out of bounds checking for arrays
  - exprs -> All exprs excepts calls, locations and literals
  - field_decls -> Field decls
  - literals -> All literals (subclass Expr)
  - llvm -> Helpers to keep the llvm variables and context used during IR gen in one place
  - locations -> VarLocation & ArrLocation (which subclass Location, which subclasses Expr)
  - method_decls -> Method declarations
  - program -> Program class
  - statements -> All types of statements
  - utils -> generic utils for AST print, etc.
  - var_decls -> variable declarations
- src contains the parser, scanner, configure and (to be generated) Makefile
- src coontains helper.sh which calls decaff and calls lli
- All ast nodes subclass Base node which acts as an interface

## Run

### Building:
```
cd src
./configure
make
```

### Running: 
```
cd src
./helper.sh filename
```
eg.
```
cd src
./helper.sh ../test-programs/binary.dcf
```

## Outputting AST graphs
- Uncomment line 13 & 14 of `helper.sh`
- Run `./helper.sh filename`
- Requires [mermaid cli](https://github.com/mermaidjs/mermaid.cli) (or you can paste the contents of `tmp.mermaid` [here](https://mermaidjs.github.io/mermaid-live-editor/))

## Description
- All AST Nodes subclass Base
- Used virtual functions so that error comes in case a function is not implemented
- Base has traverse, print and codegen methods (compulsary to override)
- traverse does symantic check. codegen does IR gen. print outpus AST to `tmp.mermaid`
- Expr is superclass of anything that can be used as expr - Location, Literal, Calls and all kinds of expressions obviously
- Expr has get_type for symantic checks
- Context is a stack of maps, where each map is a new context and the variable is returned in the first context found. Thus each map consists of variables the block has redefined.
- Similar with MLLVMContext (used for IR gen), except it stores Value* instead of CtxDataType (used for symantic analysis)
- Statement is a superclass of Block, and other kinds of statements
- In IR gen, GlobalVariable used for fields and AllocaInst used for local variables
- Run time out of bounds checking done with friendly error message
- Static checking done if function is defined properly using verifyFunction
- Built step-by-step, first restricting to expr, then adding callouts, blocks (& statements), locations, methods, variable fields and finally array fields
- The AST graph was very helpful for debugging priority and seeing if function parameters, statements, method_decls, field_decls etc are parsed in the right order/precedence.
- Important globals: mllvm, context, errors