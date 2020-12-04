function [Data] = ReadPlainFloatToArray(InputFile, channels)
% Read input emg file to Emg array
% assuming channel is 16 and datatype is float

f = fopen(InputFile);
bytes = fread(f, Inf, 'char');
len = floor(length(bytes) / 4);
row = floor(len / channels);
fclose(f);
clear bytes

f = fopen(InputFile);
data = fread(f, len, 'single');
Data = reshape(data, channels, row);
end

