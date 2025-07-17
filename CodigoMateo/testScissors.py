import pytest
from ScissorsManager import (
    createScissor,
    readScissors,
    updateScissor,
    deleteScissor,
    getAveragePrice,
    getTotalPrice,
    getMaxPriceScissor,
    getMinPriceScissor
)
import random
import string
from bson.objectid import ObjectId

# Helper: generate random test data
def generateRandomScissor():
    return {
        "name": "TestScissor_" + ''.join(random.choices(string.ascii_letters, k=5)),
        "brand": "TestBrand",
        "price": round(random.uniform(1.0, 100.0), 2)
    }

@pytest.fixture
def newScissor():
    data = generateRandomScissor()
    createScissor(data)
    return data

def testCreateAndReadScissor(newScissor):
    scissors = readScissors()
    names = [s["name"] for s in scissors]
    assert newScissor["name"] in names

def testUpdateScissor(newScissor):
    scissors = readScissors()
    found = next((s for s in scissors if s["name"] == newScissor["name"]), None)
    assert found is not None

    newPrice = newScissor["price"] + 10
    # Usar el _id tal cual, MongoDB lo reconoce
    updateScissor(found["_id"], {"price": newPrice})

    updated = next((s for s in readScissors() if s["_id"] == found["_id"]), None)
    assert updated["price"] == newPrice

def testDeleteScissor(newScissor):
    scissors = readScissors()
    found = next((s for s in scissors if s["name"] == newScissor["name"]), None)
    assert found is not None
    deleteScissor(found["_id"])

    remaining = readScissors()
    assert all(s["_id"] != found["_id"] for s in remaining)

def testStatisticalFunctions():
    scissors = readScissors()
    if scissors:
        assert isinstance(getAveragePrice(), float)
        assert isinstance(getTotalPrice(), float)
        assert getMaxPriceScissor() is not None
        assert getMinPriceScissor() is not None
