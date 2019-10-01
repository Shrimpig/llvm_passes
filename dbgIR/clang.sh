#!/bin/bash

clang -Xclang -load -Xclang /home/hong/llvm_passes/dbgIR/dbgIR.so -g "$@"
