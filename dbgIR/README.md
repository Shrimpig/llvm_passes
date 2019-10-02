# dbgIR pass

This pass encodes IR information into program debug format so that we can map each binary instruction back to the IR instruction.

## How to run this pass

the simplest way is to run clang with the plugin (do not forget the `-g`)

    clang -Xclang -load -Xclang ~/llvm_passes/dbg/dbgIR.so hello.c -g

or if this does not work, you can write a script as a wrapper of clang

    #!/bin/bash
    clang -Xclang -load -Xclang ~/llvm_passes/dbgIR/dbgIR.so -g "$@"
    
## How it works

This passs exploits the debug metadata of LLVM IR, which will be available when you compile the 
code with `-g` option. 

For each IR instruction, we create the debug information, specifically `DILocation`,
where the scope is the absolute pass of this IR file, and the line number is an unique
counter within this file. Then the compilation process will automatically encode such
information into the binary. You can use `addr2line` to find the debug information 
for each code address (which has been changed to the IR file location + the ID).

At the end, this pass saves the IR into a readable IR file. You can use the ID
printed by `addr2line` to locate the IR instruciton in the file.
