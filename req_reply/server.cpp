/**
 * Hello World server in C++
 * Binds REP socket to tcp://localhost:5555
 * Expects "Hello" from client, replies with "World"
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <zmq.hpp>

int main() {
    zmq::context_t context(2);
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.bind("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        // wait and receive for a request from a client
        auto response = socket.recv(request, zmq::recv_flags::none);

        if (response.has_value()) {
            std::cout << "Received Hello" << std::endl;

            sleep(1);
            zmq::message_t reply(5);
            memcpy(reply.data(), "World", 5);
            socket.send(reply, zmq::send_flags::none);
        }
    }

    return 0;
}