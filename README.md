PRBS Pattern Generator and Bit Error Rate Tester (BERT) OOT module for GNU Radio Companion (V3.8 or later)

<img src="https://github.com/7m4mon/gr-prbs/blob/main/prbs_source.png" alt="" title="">  
<img src="https://github.com/7m4mon/gr-prbs/blob/main/prbs_sink.PNG" alt="" title="">  
<img src="https://github.com/7m4mon/gr-prbs/blob/main/prbs_meas.PNG" alt="" title="">  

* You can choose PRBS from PN9, PN11, PN15, PN20, PN23, PN31.
* PN9, PN11, PN23 are based on O.153, PN15, PN20 are based on O.151.
* You can deliberately insert an error.
* Written by C++


How to build OOT module  
```
mkdir build
cd build
cmake ..
make
sudo make install
sudo ldconfig
```

The method for getting the BERT key is the brute force method.
Therefore, a high-speed machine is required for PN15 and above.

