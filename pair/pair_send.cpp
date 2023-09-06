#include <cstdlib>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <zmq.hpp>

int main(int argc, char *argv[]) {
    zmq::context_t context(1);
    zmq::socket_t ps(context, ZMQ_PAIR);
    ps.bind("tcp://*:5555");

    if (argc < 2) {
        std::cerr << "Please specify image path." << std::endl;
        throw std::runtime_error("Please specify the file to open.\n");
    }

    cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
    // The shitbag called OpenCV never throws an error, so need to check.
    if (img.empty()) {
        std::cout << "File path does not exist." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<uchar> buffer;

    // encode the read image as JPEG bytes into the byte buffer
    cv::imencode(".jpg", img, buffer);
    // convert the buffer to string.
    std::string img_str(buffer.begin(), buffer.end());
    zmq::message_t message(img_str.size());
    // copy the data to the message
    memcpy(message.data(), img_str.data(), img_str.size());
    ps.send(message);

    return 0;
}