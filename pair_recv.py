import zmq
import numpy as np
import cv2

context = zmq.Context()
pc = context.socket(zmq.PAIR)
pc.connect("tcp://localhost:5555")

while True:
    img_str = pc.recv()
    np_array = np.frombuffer(img_str, np.uint8)
    img = cv2.imdecode(np_array, cv2.COLOR_BGR2RGB)
    cv2.imshow("Image from ZMQ", img)
    key = cv2.waitKey(0)

    if key == ord("q"):
        break

cv2.destroyAllWindows()
