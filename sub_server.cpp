#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <zmq.hpp>

/**
 * Many publishers, single subscriber
 *
 * Collects images from many clients that publish images, and displays them
 * in a Window.
 *
 * This is very basic! Will try to display images as they come, without any sync
 */
int main(int argc, char *argv[]) {
    zmq::context_t context(1);

    std::cout << "Collecting images" << std::endl;
    zmq::socket_t sub(context, zmq::socket_type::sub);
    sub.connect("tcp://localhost:5555");

    // Subscribe to a channel (aka topic)
    const char *topic = (argc > 1) ? argv[1] : "images";
    sub.setsockopt(ZMQ_SUBSCRIBE, topic, strlen(topic));

    cv::namedWindow("Stream from clients");

    for (;;) {
        zmq::message_t request;
        zmq::recv_result_t result =
            sub.recv(request, zmq::recv_flags::dontwait);
        if (result.has_value()) {
            size_t message_size = request.size();
            std::string img_str(static_cast<char *>(request.data()),
                                message_size);
            cv::Mat raw_data(1, img_str.size(), CV_8UC1,
                             (void *)img_str.c_str());
            // Decode and display image
            cv::Mat decoded_image = cv::imdecode(raw_data, cv::COLOR_BGR2RGB);
            if (decoded_image.empty()) {
                std::cerr << "Something wrong in decoding..." << std::endl;
                exit(EXIT_FAILURE);
            }
            cv::imshow("Stream from clients", decoded_image);
            int key = cv::waitKey(0);
            if (key == 'q')
                break;
        }

        result.reset();
    }

    cv::destroyAllWindows();
    return 0;
}