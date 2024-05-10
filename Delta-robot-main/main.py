#!/usr/bin/python3
import time
import cv2
import numpy as np
from picamera2 import Picamera2
from roboflow import Roboflow

from serial_main import sendData

# Initialize Roboflow and get the model
rf = Roboflow(api_key="bhIytFU8etgDZ4368VPZ")
project = rf.workspace("phiscape-7ja5g").project("delta_vein")
version = project.version(1)
model = project.version(1).model

# Define count2 and count3
count2 = 95
count3 = 250

# Start window thread for OpenCV
cv2.startWindowThread()

# Function to get predictions from the model
def get_prediction(image):
    # Save the image
    cv2.imwrite("capture0.jpg", image)
    
    # Infer on the local image
    result = model.predict("capture0.jpg", confidence=10, overlap=30).json()
    print(result)
    
    # Get x and y coordinates from the predictions
    x = result['predictions'][0]['x']
    y = result['predictions'][0]['y']
    print(x)
    print(y)

    sendData(x,y)

    # visualize your prediction
    model.predict("capture0.jpg", confidence=40, overlap=30).save("prediction.jpg")

    cv2.destroyAllWindows()
    time.sleep(2)

    # Load predicted image using OpenCV
    predicted_image = cv2.imread('prediction.jpg')

    # Display the predicted image
    cv2.imshow("Prediction", predicted_image)
    cv2.waitKey(0)

# Initialize Picamera2
picam2 = Picamera2()
picam2.configure(picam2.create_preview_configuration(main={"format": 'XRGB8888', "size": (640, 480)}))
picam2.start()

# Main loop for capturing and processing images
while True:
    im = picam2.capture_array()

    grey = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)

    clahe = cv2.createCLAHE(clipLimit=2, tileGridSize=(8, 8))
    cl1 = clahe.apply(grey)
    clamp = np.uint8(np.interp(cl1, [count2, count3], [0, 255]))

    equ = clahe.apply(clamp)

    cv2.imshow("Camera", equ)

    key = cv2.waitKey(1)
    if key == ord('q'):
        break
    elif key == ord('a'):  # Decrease count2
        count2 -= 1
        print("count2: "+str(count2))
    elif key == ord('d'):  # Increase count2
        count2 += 1
        print("count2: "+str(count2))
    elif key == ord('z'):  # Decrease count3
        count3 -= 1
        print("count3: "+str(count3))
    elif key == ord('x'):  # Increase count3
        count3 += 1
        print("count3: "+str(count3))
    elif key == ord('c'):
        get_prediction(equ)
        break

# Stop Picamera2 and close OpenCV windows
picam2.stop()
cv2.destroyAllWindows()
