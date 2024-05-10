from roboflow import Roboflow
rf = Roboflow(api_key="wKNBXHyqnqDxzRCCrA7w")
project = rf.workspace("phiscape-7ja5g").project("delta_vein")

model = project.version(1, local="http://localhost:9001/").model

def getCoordinates():
	# infer
	result = model.predict("capture0.jpg", confidence=10, overlap=30).json()
	#save prediction
	model.predict("capture0.jpg", confidence=10, overlap=30).save("prediction.jpg")

	try:
		x=result['predictions'][0]['x']
		y=result['predictions'][0]['y']
		w=result['predictions'][0]['width']
		h=result['predictions'][0]['height']
		x=x+w/2
		y=h+h/2
		print(x)
		print(y)
		return x,y
	except:
		return 0,0
