#include <iostream>
#include <string>
#include <zmq.hpp>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::req);

    std::cout << "Connecting to \"hello world server\"..." << std::endl;
    socket.connect("tcp://localhost:5555");

    for (int n_req = 0; n_req != 10; ++n_req) {
        zmq::message_t request(5);
        memcpy(request.data(), "Hello", 5);
        std::cout << "Sending Hello " << n_req << "..." << std::endl;
        auto response = socket.send(request, zmq::send_flags::none);
        if (response.has_value()) {
            zmq::message_t reply;
            response = socket.recv(reply, zmq::recv_flags::none);
            if (response.has_value()) {
                std::cout << "Received World" << std::endl;
            }
        }
    }

    return 0;
}