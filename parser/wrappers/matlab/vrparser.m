loadlibrary("../library/parser.dll", "../../include/dllmain.h");
% "DIRA" is input directory contains all eeg data file and marker.txt
% "DIRB" is output directory, it can be unexsited
calllib("parser", "vrEegConvertAllInFolder", 'DIRA', 'DIRB')