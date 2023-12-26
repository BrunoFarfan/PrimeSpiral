import json
import os

class JsonHandler:
    def __init__(self, file_path):
        self.file_path = file_path

    def read(self):
        # Verificar si el archivo existe
        if not os.path.exists(self.file_path):
            # Si no existe, crear el archivo con la estructura deseada
            initial_data = {"prime_start": 0, "prime_list": []}
            with open(self.file_path, 'w') as file:
                json.dump(initial_data, file, indent=4)

        # Leer el archivo después de crearlo si es necesario
        with open(self.file_path, 'r') as file:
            data = json.load(file)
            prime_start = data.get("prime_start", None)
            prime_list = data.get("prime_list", [])
            return prime_list, prime_start

    def write(self, prime_list, prime_start):
        data = {
            "prime_start": prime_start,
            "prime_list": prime_list
        }
        with open(self.file_path, 'w') as file:
            json.dump(data, file, indent=4)
