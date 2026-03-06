import tkinter as tk
from tkinter import messagebox
import random


class CandyDispenser:
    def __init__(self, root):
        self.root = root
        self.root.title("Classic Candy Dispenser - 0 Candies")
        self.candies = []
        
        # Dispenser and spring dimensions
        self.DISPENSER_HEIGHT = 300
        self.DISPENSER_WIDTH = 100
        self.MAX_CANDIES = 10
        self.SPRING_TOP_Y = 50
        self.SPRING_BASE_Y = 350
        self.SPRING_WIDTH = 60
        self.MIN_SPRING_HEIGHT = 50  
        
        # Create GUI elements
        self.canvas = tk.Canvas(root, width=300, height=400, bg="white")
        self.canvas.pack()
        
        # Draw dispenser
        self.canvas.create_rectangle(100, 50, 200, 350, fill="#ffe4b5", outline="black")
        self.spring = None
        self.draw_spring()
        
        # Create a frame to hold buttons and center them
        button_frame = tk.Frame(root)
        button_frame.pack(side="bottom", pady=10)

        # Buttons
        self.create_button(button_frame, "Push", "#4caf50", self.push)
        self.create_button(button_frame, "Pop", "#f44336", self.pop)
        self.create_button(button_frame, "Top", "#2196f3", self.top)
        self.create_button(button_frame, "Empty", "#ff9800", self.is_empty)
        self.create_button(button_frame, "Length", "#9c27b0", self.length)
        self.create_button(button_frame, "Exit", "#607d8b", root.quit)
    
    def create_button(self, frame, text, color, command):
        # Helper to create a button with specific color and action.
        button = tk.Button(frame, text=text, bg=color, fg="white", font=("Arial", 12, "bold"), width=10, height=2, command=command)
        button.pack(side="left", padx=5, pady=5)
    
    def draw_spring(self):
        # Draw the dynamic spring based on the number of candies.
        if self.spring:
            self.canvas.delete(self.spring)
        
        # Calculate spring height
        max_spring_height = self.SPRING_BASE_Y - self.SPRING_TOP_Y
        spring_height = max(
            self.MIN_SPRING_HEIGHT,
            max_spring_height - (len(self.candies) * (max_spring_height - self.MIN_SPRING_HEIGHT) // self.MAX_CANDIES),
        )
        
        # Draw spring as coils
        num_coils = 10
        coil_spacing = spring_height / num_coils
        x1, x2 = 120, 180
        y = self.SPRING_BASE_Y
        spring_coords = []
        for _ in range(num_coils):
            y -= coil_spacing
            spring_coords.extend([x1, y, x2, y])
        self.spring = self.canvas.create_line(spring_coords, fill="gray", width=2)
    
    def update_dispenser(self):
        # Update the spring and candies in the dispenser.
        self.draw_spring()
        self.draw_candies()
        self.root.title(f"Classic Candy Dispenser - {len(self.candies)} Candies")
    
    def draw_candies(self):
        # Draw candies as colored balls.
        self.canvas.delete("candy")  # Clear previous candies
        max_spring_height = self.SPRING_BASE_Y - self.SPRING_TOP_Y
        spring_height = max(
            self.MIN_SPRING_HEIGHT,
            max_spring_height - (len(self.candies) * (max_spring_height - self.MIN_SPRING_HEIGHT) // self.MAX_CANDIES),
        )
        candy_start_y = self.SPRING_BASE_Y - spring_height + 10  # Start above spring top
        
        y = candy_start_y
        for candy in self.candies:
            x1, y1 = 130, y - 20
            x2, y2 = 170, y
            self.canvas.create_oval(x1, y1, x2, y2, fill=candy, outline="black", tags="candy")
            y -= 20
    
    def push(self):
        # Add a candy to the dispenser.
        if len(self.candies) < self.MAX_CANDIES:
            candy_color = random.choice(["red", "pink", "blue", "green", "yellow"])
            self.candies.append(candy_color)
            self.update_dispenser()
            messagebox.showinfo("Push", f"A candy with color {candy_color} has been added!")
        else:
            messagebox.showinfo("Full", "The dispenser is full!")
    
    def pop(self):
        # Remove the top candy.
        if self.candies:
            removed_candy = self.candies.pop()
            self.update_dispenser()
            messagebox.showinfo("Pop", f"A candy with color {removed_candy} has been removed!")
        else:
            messagebox.showinfo("Empty", "The dispenser is empty!")
    
    def top(self):
        # Show the top candy.
        if self.candies:
            messagebox.showinfo("Top Candy", f"Top Candy Color: {self.candies[-1]}")
        else:
            messagebox.showinfo("Empty", "The dispenser is empty!")
    
    def is_empty(self):
        # Check if the dispenser is empty.
        if not self.candies:
            messagebox.showinfo("Empty", "The dispenser is empty!")
        else:
            messagebox.showinfo("Not Empty", f"The candy dispenser is not empty.")
    
    def length(self):
        # Show the number of candies.
        messagebox.showinfo("Length", f"The length is {len(self.candies)} candies.")


# Run the application
root = tk.Tk()
app = CandyDispenser(root)
root.mainloop()
