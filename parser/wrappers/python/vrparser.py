import os
import ctypes
import sys

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python vrparser.py {inDir} {outDir}\n")
        exit(1)
    try:
        libc = ctypes.CDLL("./parser.dll")
        print(libc)
    except Exception as e:
        print(e)
        exit(1)
    inDir = ctypes.c_char_p(bytes(inDir))
    outDir = ctypes.c_char_p(bytes(outDir))
    print(libc.vrEegConvertAllInFolder)
    libc.vrEegConvertAllInFolder(inDir, outDir)