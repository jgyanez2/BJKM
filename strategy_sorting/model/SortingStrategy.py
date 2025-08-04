from abc import ABC, abstractmethod

# Interfaz base para las estrategias de ordenamiento
# Se usó ABC (clase abstracta) como reemplazo de interfaces en Python
class SortingStrategy(ABC):
    @abstractmethod
    def sort(self, data: list) -> list:
        pass