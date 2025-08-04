# Cliente que usa el contexto para ordenar una lista
# Esta clase reemplaza a SortApp.java del ejemplo
# No hay interfaz gráfica, pero esto sería parte del "view"

from controller.SortingContext import SortingContext

if __name__ == "__main__":
    data = [3, 5, 4, 6, 7, 9, 5, 6, 7, 5, 10, 3]

    print("Lista original:", data)

    context = SortingContext()
    sorted_data = context.sort(data)

    print("Lista ordenada:", sorted_data)