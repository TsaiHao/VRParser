function [Data] = ReadPlainFloatToArray(InputFile, DataType)
% Read FT data : ft = ReadPlainFloatToArray('feet.ftdata', 'FT');
% Read Emg data : emg = ReadPlainFloatToArray('emg.bin', 'Emg');

f = fopen(InputFile);
if strcmp(DataType, 'FT')
    chans = 6;
    tp = 'double';
elseif strcmp(DataType, 'Emg')
    chans = 16;
    tp = 'single';
else
    return;
end
data = fread(f, Inf, tp);
cols = floor(length(data) / chans);
Data = reshape(data(1: cols * chans), chans, cols);
fclose(f);
end

