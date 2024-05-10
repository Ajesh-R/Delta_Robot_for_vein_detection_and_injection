from roboflow import Roboflow
rf = Roboflow(api_key="wKNBXHyqnqDxzRCCrA7w")
project = rf.workspace("phiscape-7ja5g").project("vein_detection")
#dataset = project.version(1).download("yolov8")

model = project.version(1, local="http://localhost:9001/").model

# infer on a local image
result = model.predict("capture0.jpg", confidence=10, overlap=30).json()
print(result)
x=result['predictions'][0]['x']
y=result['predictions'][0]['y']
print(x)
print(y)

# visualize your prediction
model.predict("capture0.jpg", confidence=10, overlap=30).save("prediction.jpg")

# infer on an image hosted elsewhere
# print(model.predict("URL_OF_YOUR_IMAGE", hosted=True, confidence=40, overlap=30).json())
