#!/usr/bin/env python
from math import sin, cos, exp, pi

def sinc(x):
    if x == 0:
        return 1
    else:
        return sin(pi*x)/(pi*x)

def build_window(name,trans_width):
    #name is a string, telling the program which window to use. trans_width is the width of the transition band in rad/s
    trans_width *= pi
    if name == 'hanning':
        size = int(6.65*pi/trans_width)
        if size % 2 == 0:
            size = size + 1
        x = range(size)
        window = []
        for n in x:
            value = sin(pi*n/(size-1)) ** 2
            window.append(value)
    elif name == 'hamming':
        size = int(6.22*pi/trans_width)
        if size % 2 == 0:
            size = size + 1
        x = range(size)
        window = []
        for n in x:
            value = 0.54 - 0.46 * cos(2*pi*n/(size-1))
            window.append(value)
    elif name == 'gaussian':
        size = int(8.52*pi/trans_width)
        if size % 2 == 0:
            size = size + 1
        x = range(-(size-1)/2, (size-1)/2 + 1)
        #x = range(size)
        stdev = (size-1)/5;
        window = []
        for n in x:
            value = exp(-1/2*(float(n)/stdev) ** 2);
            window.append(value)
    elif name == 'blackman':
        size = int(11.1*pi/trans_width)
        if size % 2 == 0:
            size = size + 1
        x = range(-(size-1)/2, (size-1)/2 + 1)
        #x = range(size)
        window = []
        for n in x:
            value = 0.42 + 0.5*cos(2*pi*n/(size-1)) + 0.08*cos(4*pi*n/(size-1));
            window.append(value)
    else:
        print 'Invalid window name'
        
    return window

def build_filter(Wc,window):
    size = len(window)
    x = range(-(size-1)/2, (size-1)/2 + 1)
    kernel = []
    for i in range(size):
        value = sinc(x[i]*Wc)*Wc*window[i]
        kernel.append(value)
    return kernel

def conv(f,g):      #f is kernel, g is signal
    nf = len(f)
    ng = len(g)
    n = nf + ng - 1
    out = []
    for i in range(n):
        result = 0.0
        for j in range(nf):
            if i - j < 0 or i - j >= ng:
                result += 0.0
            else:
                result += f[j] * g[i - j]
        out.append(result)
    return out[nf/2 : nf/2+ng]

signal = []

with open('signal.txt') as f:
    for line in f:
        l = line.split()
        for num in l:
            signal.append(float(num))

name = raw_input('Please enter the name of window: ')
trans_width = float(raw_input('Please enter the desired width of the transition band: '))
Wc = float(raw_input('Please enter the desired cut-off frequency: '))

window = build_window(name,trans_width)
kernel = build_filter(Wc,window)
filtered_signal = conv(kernel,signal)

outfile = open('D:\Documents\MATLAB\SKA project Perth\output.txt','w')
for data in filtered_signal:
    outfile.write('%f ' % data)
outfile.close()