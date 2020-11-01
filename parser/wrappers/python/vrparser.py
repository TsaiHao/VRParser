#!/usr/bin/python3
import os
import ctypes
import sys

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python vrparser.py {inDir} {outDir}\n")
        exit(1)
    try:
        libc = ctypes.CDLL("./libparserlib.so")
        print(libc)
    except Exception as e:
        print(e)
        exit(1)
    inDir = ctypes.c_char_p(bytes(sys.argv[1], "ascii"))
    outDir = ctypes.c_char_p(bytes(sys.argv[2], "ascii"))
    print(libc.vrEegConvertAllInFolder)
    libc.vrEegConvertAllInFolder(inDir, outDir)