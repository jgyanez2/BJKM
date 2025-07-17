import tkinter as tk
from tkinter import messagebox
from ScissorsManager import createScissor

# Predefined options
names = ["School Scissors", "Sewing Scissors", "Industrial Scissors", "Blunt Tip Scissors"]
brands = ["Faber-Castell", "Maped", "Tramontina", "Stanley"]

def addScissor():
    name = selectedName.get()
    brand = selectedBrand.get()
    try:
        price = float(entryPrice.get())
    except ValueError:
        messagebox.showerror("Error", "Invalid price")
        return

    if name and brand and price:
        data = {"name": name, "brand": brand, "price": price}
        createScissor(data)
        messagebox.showinfo("Success", "Scissor added")
    else:
        messagebox.showwarning("Warning", "Please fill all fields")

# GUI setup
root = tk.Tk()
root.title("Scissors CRUD")

# Name dropdown
tk.Label(root, text="Name:").pack()
selectedName = tk.StringVar()
selectedName.set(names[0])
tk.OptionMenu(root, selectedName, *names).pack()

# Brand dropdown
tk.Label(root, text="Brand:").pack()
selectedBrand = tk.StringVar()
selectedBrand.set(brands[0])
tk.OptionMenu(root, selectedBrand, *brands).pack()

# Price input
tk.Label(root, text="Price:").pack()
entryPrice = tk.Entry(root)
entryPrice.pack()

# Add button
tk.Button(root, text="Add Scissor", command=addScissor).pack()

root.mainloop()
