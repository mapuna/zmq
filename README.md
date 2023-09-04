# Simple Demo of 0MQ in PAIR mode.

1. The CPP code reads *one* image from the disk and sends it over a socket in `PAIR` mode as JPEG bytes. Compile it as follows (with OpenCV4 on an Ubuntu system):
```
g++ -o ps pair_send.cpp `pkg-config --cflags --libs opencv4` -lzmq
```
2. The receiver is in python with `opencv`, `numpy` and `pyzmq` requirements. It keeps waiting for data to apper on the port it connected. Once the data is available, it deocdes and displays it. 
