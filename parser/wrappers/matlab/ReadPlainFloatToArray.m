function [Data] = ReadPlainFloatToArray(InputFile, DataType)
% Read FT data : ft = ReadPlainFloatToArray('feet.ftdata', 'FT');
% Read Emg data : emg = ReadPlainFloatToArray('emg.bin', 'Emg');

f = fopen(InputFile);
if (f < 0)
    error('input file name is invalid')
end
tp = 'single';
DataType = lower(DataType);

if nargin < 2
    chans = 1;
elseif strcmp(DataType, 'ft')
    chans = 6;
elseif strcmp(DataType, 'emg')
    chans = 16;
elseif strcmp(DataType, 'eeg')
    chans = 35;
else
    error('data type is not defined')
end

data = fread(f, Inf, tp);
cols = floor(length(data) / chans);
Data = reshape(data(1: cols * chans), chans, cols);
fclose(f);

end

