# llvm_passes

This repo contains some simple LLVM passes I wrote during my research, or just for fun. 

## How to run each pass

the simplest way is to run clang with the plugin 

    clang -Xclang -load -Xclang ~/llvm_passes/DIE/DIE.so hello.c

or if this does not work, you can write a script as a wrapper of clang

    #!/bin/bash
    clang -Xclang -load -Xclang ~/llvm_passes/DIE/DIE.so -g "$@"
    
## Directories

* **DIE**: this is just a template for LLVM Module passes
* **dbgIR**: encoding IR information into binary, so that you can use `addr2line` to find corresponding IR instruction for each binary address
