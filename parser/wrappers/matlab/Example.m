% read FT data, channels is 6
ftdata = ReadPlainFloatToArray('feet.ftdata', 6);

% read Emg data, channels is 16
emgdata = ReadPlainFloatToArray('emg.bin', 16);