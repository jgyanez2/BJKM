from pymongo import MongoClient

# MongoDB Connection
client = MongoClient("mongodb+srv://mjunda1:MateoUndaJM05@cluster0.7yle2fx.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0")
db = client["ScissorsDB"]
collection = db["scissors"]

# CRUD Functions
def createScissor(data):
    collection.insert_one(data)

def readScissors():
    return list(collection.find())

def updateScissor(scissorId, newData):
    collection.update_one({"_id": scissorId}, {"$set": newData})

def deleteScissor(scissorId):
    collection.delete_one({"_id": scissorId})

# Numeric Calculations
def getAveragePrice():
    scissors = readScissors()
    if not scissors:
        return 0.0
    return sum(s["price"] for s in scissors) / len(scissors)

def getTotalPrice():
    scissors = readScissors()
    return sum(s["price"] for s in scissors)

def getMaxPriceScissor():
    scissors = readScissors()
    return max(scissors, key=lambda s: s["price"], default=None)

def getMinPriceScissor():
    scissors = readScissors()
    return min(scissors, key=lambda s: s["price"], default=None)
