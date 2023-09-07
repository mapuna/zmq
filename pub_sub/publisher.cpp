/*
 * Binds PUB socket to tcp://localhost:5555
 */
#include <cstdlib>
#include <iostream>
#include <zmq.hpp>

std::string random_string(const size_t len) {
    static const char alpha[] = "0123456789"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz";
    std::string tmp;
    tmp.reserve(len);

    for (size_t i = 0; i < len; ++i) {
        tmp += alpha[rand() % (sizeof(alpha) - 1)];
    }

    return tmp;
}

int main() {
    size_t len = 21;
    zmq::context_t context(1);
    zmq::socket_t pub(context, zmq::socket_type::pub);
    pub.bind("tcp://*:5555");
    pub.bind("ipc://pub.ipc");

    while (true) {
        zmq::message_t message(len);
        std::string to_send = random_string(len - 1);
        snprintf((char *)message.data(), len, "%s", to_send.c_str());

        std::cout << "Sending string: '" << to_send << "'" << std::endl;
        auto response = pub.send(message, zmq::send_flags::none);

        if (!response.has_value()) {
            std::cerr << "Some error sending data" << std::endl;
        }
    }

    return 0;
}