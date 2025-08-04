# Esta clase representa el "Contexto" del patrón Strategy
# Se encarga de elegir la estrategia de ordenamiento según el tamaño

from model.BubbleSort import BubbleSort
from model.InsertionSort import InsertionSort
from model.QuickSort import QuickSort

class SortingContext:
    def __init__(self):
        self.strategy = None

    def sort(self, data: list) -> list:
        size = len(data)
        self.set_sort_strategy(size)
        return self.strategy.sort(data)

    # Se reimplementó lógica para elegir bien la estrategia
    # Rango corregido según el ejemplo en el PDF (0-30, 30-100, 100+)
    def set_sort_strategy(self, size: int):
        if 0 < size < 30:
            self.strategy = BubbleSort()
        elif 30 <= size < 100:
            self.strategy = InsertionSort()
        else:
            self.strategy = QuickSort()