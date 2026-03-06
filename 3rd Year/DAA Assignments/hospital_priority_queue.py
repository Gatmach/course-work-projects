import tkinter as tk
from tkinter import ttk, messagebox
from heapq import heappush, heappop

class HospitalQueue:
    def __init__(self):
        self.queue = [] 
        self.counter = 0  # Counter to track order of arrival

    def add_patient(self, name, age, priority):
        # Use negative priority and age for max-heap behavior
        heappush(self.queue, (-priority, age, self.counter, name))
        self.counter += 1

    def remove_patient(self, name):
        found = False
        new_queue = []
        for patient in self.queue:
            if patient[3] == name:
                found = True
            else:
                new_queue.append(patient)
        if not found:
            return False
        self.queue = new_queue
        return True

    def update_patient(self, name, new_age=None, new_priority=None):
        found = False
        new_queue = []
        for patient in self.queue:
            if patient[3] == name:
                found = True
                updated_priority = new_priority if new_priority is not None else -patient[0]
                updated_age = new_age if new_age is not None else patient[1]
                new_queue.append((-updated_priority, updated_age, patient[2], name))
            else:
                new_queue.append(patient)
        if not found:
            return False
        self.queue = new_queue
        return True

    def is_empty(self):
        return len(self.queue) == 0

    def top(self):
        return None if self.is_empty() else self.queue[0]

    def length(self):
        return len(self.queue)

    def get_queue(self):
        return sorted(self.queue, reverse=True)
    

class HospitalApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Hospital Queue Management System")
        self.hospital_queue = HospitalQueue()

        # Title
        tk.Label(root, text="Hospital Queue Management System", font=("Arial", 16, "bold")).pack(pady=10)

        # Input Frame
        input_frame = tk.Frame(root)
        input_frame.pack(pady=10)

        tk.Label(input_frame, text="Name:").grid(row=0, column=0, padx=5, pady=5)
        self.name_entry = tk.Entry(input_frame)
        self.name_entry.grid(row=0, column=1, padx=5, pady=5)

        tk.Label(input_frame, text="Age:").grid(row=1, column=0, padx=5, pady=5)
        self.age_entry = tk.Entry(input_frame)
        self.age_entry.grid(row=1, column=1, padx=5, pady=5)

        tk.Label(input_frame, text="priority (1-5):").grid(row=2, column=0, padx=5, pady=5)
        self.priority_entry = tk.Entry(input_frame)
        self.priority_entry.grid(row=2, column=1, padx=5, pady=5)

        # Buttons Frame
        button_frame = tk.Frame(root)
        button_frame.pack(pady=10)

        self.add_button = tk.Button(button_frame, text="Add Patient", command=self.add_patient,
                                    bg="#4CAF50", fg="white", font=("Arial", 10), relief="groove", bd=2)
        self.add_button.grid(row=0, column=0, padx=5, ipadx=10)

        self.remove_button = tk.Button(button_frame, text="Remove Patient", command=self.remove_patient,
                                       bg="#F44336", fg="white", font=("Arial", 10), relief="groove", bd=2)
        self.remove_button.grid(row=0, column=1, padx=5, ipadx=5)

        self.update_button = tk.Button(button_frame, text="Update Patient", command=self.update_patient,
                                       bg="#2196F3", fg="white", font=("Arial", 10), relief="groove", bd=2)
        self.update_button.grid(row=0, column=2, padx=5, ipadx=5)

        self.status_button = tk.Button(button_frame, text="Length", command=self.check_status,
                                       bg="#9C27B0", fg="white", font=("Arial", 10), relief="groove", bd=2)
        self.status_button.grid(row=0, column=3, padx=5, ipadx=5)

        self.is_empty_button = tk.Button(button_frame, text="is_empty", command=self.check_if_empty,
                                         bg="purple", fg="white", font=("Arial", 10), relief="groove", bd=2)
        self.is_empty_button.grid(row=0, column=4, padx=5, ipadx=5)

        self.clear_all_button = tk.Button(button_frame, text="Clear All", command=self.clear_all,
                                  bg="#FF5722", fg="white", font=("Arial", 10), relief="groove", bd=2)
        self.clear_all_button.grid(row=0, column=5, padx=5, ipadx=5)
        # Queue Display
        self.queue_display = ttk.Treeview(root, columns=("Name", "Age", "priority"), show="headings")
        self.queue_display.heading("Name", text="Name")
        self.queue_display.heading("Age", text="Age")
        self.queue_display.heading("priority", text="priority")
        self.queue_display.pack(pady=10)

    def add_patient(self):
        name = self.name_entry.get().strip()
        age = self.age_entry.get().strip()
        priority = self.priority_entry.get().strip()

        if not name or not age or not priority:
            messagebox.showerror("Error", "All fields must be filled to add a patient!")
            return

        try:
            age = int(age)
            if age <= 0:
                raise ValueError("Age must be a positive number.")

            priority = int(priority)
            if priority < 1 or priority > 5:
                raise ValueError("Priority must be between 1 and 5.")
        except ValueError as ve:
            messagebox.showerror("Error", f"Invalid input: {str(ve)}")
            return

        self.hospital_queue.add_patient(name, age, priority)
        self.update_queue_display()
        messagebox.showinfo("Success", f"Patient '{name}' added successfully!")
        self.clear_entries()

    def remove_patient(self):
        name = self.name_entry.get().strip()
        if not name:
            messagebox.showerror("Error", "Enter the name of the patient to remove!")
            return

        if self.hospital_queue.remove_patient(name):
            self.update_queue_display()
            messagebox.showinfo("Success", f"Patient '{name}' removed successfully!")
        else:
            messagebox.showerror("Error", f"Patient '{name}' not found in the queue!")
        self.clear_entries()

    def update_patient(self):
        name = self.name_entry.get().strip()
        if not name:
            messagebox.showerror("Error", "Enter the name of the patient to update!")
            return

        new_age = self.age_entry.get().strip()
        new_priority = self.priority_entry.get().strip()
        try:
            new_age = int(new_age) if new_age else None
            if new_age is not None and new_age <= 0:
                raise ValueError("Age must be a positive number.")
            
            new_priority = int(new_priority) if new_priority else None
            if new_priority is not None and (new_priority < 1 or new_priority > 5):
                raise ValueError("Priority must be between 1 and 5.")
        except ValueError as ve:
            messagebox.showerror("Error", f"Invalid input: {str(ve)}")
            return

        if self.hospital_queue.update_patient(name, new_age, new_priority):
            self.update_queue_display()
            messagebox.showinfo("Success", f"Patient '{name}' updated successfully!")
        else:
            messagebox.showerror("Error", f"Patient '{name}' not found in the queue!")
        self.clear_entries()

    def check_if_empty(self):
        if self.hospital_queue.is_empty():
            messagebox.showinfo("Queue Status", "The queue is empty")
        else:
            messagebox.showinfo("Queue Status", "The queue is not empty")

    def clear_all(self):
    # Clear all patients from the queue."""
        self.hospital_queue.queue.clear()
        self.hospital_queue.counter = 0
        self.update_queue_display()
        messagebox.showinfo("Clear All", "All patients have been removed from the queue!")
    def check_status(self):
        if self.hospital_queue.is_empty():
            messagebox.showinfo("Info", "The queue is empty!")
        else:
            count = self.hospital_queue.length()
            messagebox.showinfo("Queue Status", f"The queue has {count} patient(s).")

    def update_queue_display(self):
        for row in self.queue_display.get_children():
            self.queue_display.delete(row)
        for priority, age, _, name in self.hospital_queue.get_queue():
            self.queue_display.insert("", "end", values=(name, age, -priority))

    def clear_entries(self):
        self.name_entry.delete(0, tk.END)
        self.age_entry.delete(0, tk.END)
        self.priority_entry.delete(0, tk.END)


if __name__ == "__main__":
    root = tk.Tk()
    app = HospitalApp(root)
    root.mainloop()
