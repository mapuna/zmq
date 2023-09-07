import zmq

context = zmq.Context()
sub = context.socket(zmq.SUB)
sub.connect("tcp://localhost:5555")

filter = "SOA"
sub.setsockopt_string(zmq.SUBSCRIBE, filter)

counter = 1
while True:
    string = sub.recv_string()
    if counter > 10:
        break
    print(f"String containing the subsequence {filter}: {string}")
    counter += 1
