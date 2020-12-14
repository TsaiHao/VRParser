function [Data] = ReadPlainFloatToArray(InputFile, DataType)
% Read FT data : ft = ReadPlainFloatToArray('feet.ftdata', 'FT');
% Read Emg data : emg = ReadPlainFloatToArray('emg.bin', 'Emg');

f = fopen(InputFile);
tp = 'single';
if strcmp(DataType, 'FT')
    chans = 6;
elseif strcmp(DataType, 'Emg')
    chans = 16;
elseif strcmp(DataType, 'Eeg')
    chans = 35;
else
    return;
end
data = fread(f, Inf, tp);
cols = floor(length(data) / chans);
Data = reshape(data(1: cols * chans), chans, cols);
fclose(f);
end

