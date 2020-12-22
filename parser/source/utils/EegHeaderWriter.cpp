#include <fstream>
#include "dllmain.h"
using namespace std;

DLLEXPORT int DLLFUNEXP vrEegWriteBrainVisionHeader(const char* outFile)
{
    const char* text = R"(Brain Vision Data Exchange Header File Version 1.0
; Data created by the Vision Recorder

[Common Infos]
Codepage=UTF-8
DataFile=EegData.eeg
MarkerFile=EegMarker.vmrk
DataFormat=BINARY
; Data orientation: MULTIPLEXED=ch1,pt1, ch2,pt1 ...
DataOrientation=MULTIPLEXED
NumberOfChannels=35
; Sampling interval in microseconds
SamplingInterval=2000
segmentationtype=markerbased

[Binary Infos]
BinaryFormat=IEEE_FLOAT_32

[Channel Infos]
; Each entry: Ch<Channel number>=<Name>,<Reference channel name>,
; <Resolution in "Unit">,<Unit>, Future extensions..
; Fields are delimited by commas, some fields might be omitted (empty).
; Commas in channel names are coded as "\1".
Ch1=Fp1,,0.0406901,µV
Ch2=Fp2,,0.0406901,µV
Ch3=F3,,0.0406901,µV
Ch4=F4,,0.0406901,µV
Ch5=C3,,0.0406901,µV
Ch6=C4,,0.0406901,µV
Ch7=P3,,0.0406901,µV
Ch8=P4,,0.0406901,µV
Ch9=O1,,0.0406901,µV
Ch10=O2,,0.0406901,µV
Ch11=F7,,0.0406901,µV
Ch12=F8,,0.0406901,µV
Ch13=T7,,0.0406901,µV
Ch14=T8,,0.0406901,µV
Ch15=P7,,0.0406901,µV
Ch16=P8,,0.0406901,µV
Ch17=Fz,,0.0406901,µV
Ch18=Cz,,0.0406901,µV
Ch19=Pz,,0.0406901,µV
Ch20=IO,,0.0406901,µV
Ch21=FC1,,0.0406901,µV
Ch22=FC2,,0.0406901,µV
Ch23=CP1,,0.0406901,µV
Ch24=CP2,,0.0406901,µV
Ch25=FC5,,0.0406901,µV
Ch26=FC6,,0.0406901,µV
Ch27=CP5,,0.0406901,µV
Ch28=CP6,,0.0406901,µV
Ch29=FT9,,0.0406901,µV
Ch30=FT10,,0.0406901,µV
Ch31=TP9,,0.0406901,µV
Ch32=TP10,,0.0406901,µV
Ch33=x_dir,,1,mg
Ch34=y_dir,,1,mg
Ch35=z_dir,,1,mg

[Comment]

BrainVision Recorder Professional   -   V. 1.21.0303


A m p l i f i e r  S e t u p
============================
Number of channels: 35
Sampling Rate [Hz]: 500
Sampling Interval [µS]: 2000

Channels
--------
#     Name      Phys. Chn.    Resolution / Unit   Low Cutoff [s]   High Cutoff [Hz]   Notch [Hz]    Gradient         Offset
1     Fp1         1          0.0406901 µV             DC              131              Off
2     Fp2         2          0.0406901 µV             DC              131              Off
3     F3          3          0.0406901 µV             DC              131              Off
4     F4          4          0.0406901 µV             DC              131              Off
5     C3          5          0.0406901 µV             DC              131              Off
6     C4          6          0.0406901 µV             DC              131              Off
7     P3          7          0.0406901 µV             DC              131              Off
8     P4          8          0.0406901 µV             DC              131              Off
9     O1          9          0.0406901 µV             DC              131              Off
10    O2          10         0.0406901 µV             DC              131              Off
11    F7          11         0.0406901 µV             DC              131              Off
12    F8          12         0.0406901 µV             DC              131              Off
13    T7          13         0.0406901 µV             DC              131              Off
14    T8          14         0.0406901 µV             DC              131              Off
15    P7          15         0.0406901 µV             DC              131              Off
16    P8          16         0.0406901 µV             DC              131              Off
17    Fz          17         0.0406901 µV             DC              131              Off
18    Cz          18         0.0406901 µV             DC              131              Off
19    Pz          19         0.0406901 µV             DC              131              Off
20    IO          20         0.0406901 µV             DC              131              Off
21    FC1         21         0.0406901 µV             DC              131              Off
22    FC2         22         0.0406901 µV             DC              131              Off
23    CP1         23         0.0406901 µV             DC              131              Off
24    CP2         24         0.0406901 µV             DC              131              Off
25    FC5         25         0.0406901 µV             DC              131              Off
26    FC6         26         0.0406901 µV             DC              131              Off
27    CP5         27         0.0406901 µV             DC              131              Off
28    CP6         28         0.0406901 µV             DC              131              Off
29    FT9         29         0.0406901 µV             DC              131              Off
30    FT10        30         0.0406901 µV             DC              131              Off
31    TP9         31         0.0406901 µV             DC              131              Off
32    TP10        32         0.0406901 µV             DC              131              Off
33    x_dir       33                 1 mg             DC               50              Off
34    y_dir       34                 1 mg             DC               50              Off
35    z_dir       35                 1 mg             DC               50              Off


LiveAmp SN:                		LA-054907-0292
LiveAmp hardware revision: 		4
Firmware version:          		4.59

Sensor and trigger extension SN:                STE-000000-0000
Sensor and trigger extension hardware revision: 0
Sensor and trigger extension firmware version:  0.0

Library version:           		9.17.10.12

Use Active/Dry Electrodes: No

S o f t w a r e  F i l t e r s
==============================
Disabled


Data/Gnd/Ref Electrodes Selected Impedance Measurement Range: 0 - 50 kOhm
Impedance [kOhm] at 11:47:39 :
Fp1:          6
Fp2:          9
F3:           7
F4:           9
C3:           6
C4:           7
P3:           9
P4:           5
O1:           7
O2:           6
F7:          10
F8:           5
T7:           9
T8:           4
P7:           7
P8:           7
Fz:          15
Cz:           1
Pz:           6
IO:           3
FC1:         10
FC2:         11
CP1:          6
CP2:          5
FC5:          8
FC6:          8
CP5:         11
CP6:          7
FT9:         10
FT10:        10
TP9:         12
TP10:         8
Gnd:          4
Ref:          0

)";

    ofstream ofs(outFile);
    if (!ofs) {
        return -1;
    }
    ofs << text;
    ofs.close();
    return 1;
}


