# 0MQ - Simple Demos

## PAIRed mode

Possibly thr simplest and the dumbest thing to do. 
Files in the subdir: [pair](pair)

1. The CPP code reads *one* image from the disk and sends it over a 
   socket in `PAIR` mode as JPEG bytes. Compile it as follows 
   (with OpenCV4 on an Ubuntu system):
`g++ -o ps pair_send.cpp `pkg-config --cflags --libs opencv4` -lzmq`
   One can create a simple unchecked video stremer by opening a video 
   stream in `pair_send.cpp`. The aim of this repo is just to show simple
   patterns for some common streaming use cases, so you'll need to hack on 
   it on your own for more esoteric usage.
2. The receiver is in python with `opencv`, `numpy` and `pyzmq` 
   requirements. It keeps waiting for data to apper on the port it 
   connected. Once the data is available, it deocdes and displays it. 
