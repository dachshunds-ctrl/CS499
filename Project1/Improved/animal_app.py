from pymongo import MongoClient
from pprint import pprint

class AnimalShelter:
    def __init__(self, username, password):
        self.client = MongoClient(f'mongodb://{username}:{password}@localhost:27017/')
        self.db = self.client['AAC']

    def create(self, data):
        try:
            if data:
                result = self.db.animals.insert_one(data)
                pprint(result)
                return True
            else:
                raise Exception("Data is empty")
        except Exception as e:
            print(e)
            return False
    
    def read(self, query=None):
        try:
            if query:
                result = self.db.animals.find(query, {"_id": False})
                return list(result)
            else:
                raise Exception("Query is empty")
        except Exception as e:
            print(e)
            return False
    
    def update(self, query, new_values):
        try:
            if query and new_values:
                result = self.db.animals.update_many(query, {"$set": new_values})
                pprint(result)
                return True
            else:
                raise Exception("Query or new values is empty")
        except Exception as e:
            print(e)
            return False

    def delete(self, query):
        try:
            if query:
                result = self.db.animals.delete_many(query)
                pprint(result)
                return True
            else:
                raise Exception("Query is empty")
        except Exception as e:
            print(e)
            return False
