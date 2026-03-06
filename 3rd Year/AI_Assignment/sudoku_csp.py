import tkinter as tk
from tkinter import messagebox, ttk
import time
import random

class SudokuCSP:
    def __init__(self, puzzle):
        """Initialize the Sudoku CSP with the given puzzle."""
        self.puzzle = puzzle
        self.size = 9
        self.subgrid_size = 3
        
        self.variables = [(i, j) for i in range(self.size) for j in range(self.size)]
        self.domains = {}
        for i, j in self.variables:
            if self.puzzle[i][j] != 0:
                self.domains[(i, j)] = [self.puzzle[i][j]]
            else:
                self.domains[(i, j)] = list(range(1, 10))
        
        self.constraints = {}
        for var in self.variables:
            self.constraints[var] = self._get_constraints_for(var)
    
    def _get_constraints_for(self, var):
        i, j = var
        constraints = set()
        
        for col in range(self.size):
            if col != j: constraints.add((i, col))
        
        for row in range(self.size):
            if row != i: constraints.add((row, j))
        
        subgrid_row, subgrid_col = i // 3, j // 3
        for x in range(subgrid_row*3, (subgrid_row+1)*3):
            for y in range(subgrid_col*3, (subgrid_col+1)*3):
                if x != i or y != j:
                    constraints.add((x, y))
        
        return constraints
    
    def is_consistent(self, var, value, assignment):
        for neighbor in self.constraints[var]:
            if neighbor in assignment and assignment[neighbor] == value:
                return False
        return True
    
    def is_complete(self, assignment):
        return len(assignment) == len(self.variables)
    
    def select_unassigned_variable(self, assignment):
        unassigned = [var for var in self.variables if var not in assignment]
        return min(unassigned, key=lambda var: len(self.domains[var]))
    
    def order_domain_values(self, var, assignment):
        return sorted(self.domains[var], key=lambda val: self._count_conflicts(var, val, assignment))
    
    def _count_conflicts(self, var, value, assignment):
        return sum(1 for neighbor in self.constraints[var] 
                  if neighbor in assignment and assignment[neighbor] == value)
    
    def backtracking_search(self):
        return self._backtrack({})
    
    def _backtrack(self, assignment):
        if self.is_complete(assignment):
            return assignment
        
        var = self.select_unassigned_variable(assignment)
        
        for value in self.order_domain_values(var, assignment):
            if self.is_consistent(var, value, assignment):
                assignment[var] = value
                result = self._backtrack(assignment)
                if result is not None:
                    return result
                del assignment[var]
        
        return None
    
    def solve(self):
        solution = self.backtracking_search()
        if solution is None:
            return None
        
        # Convert solution dictionary to 2D list
        solved_puzzle = [[0 for _ in range(9)] for _ in range(9)]
        for (i, j), val in solution.items():
            solved_puzzle[i][j] = val
        return solved_puzzle


class SudokuGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("✨ Sudoku Solver ✨")
        self.root.geometry("550x700")
        self.root.configure(bg='#f0f8ff')
        
        try:
            self.root.iconbitmap('sudoku.ico')
        except:
            pass
        
        self.puzzle = [[0]*9 for _ in range(9)]  # Initialize empty puzzle
        self.cells = {}
        
        self._create_menu()
        self._create_header()
        self._create_board()
        self._create_buttons()
        self._create_footer()
        
        # Generate initial puzzle after GUI is set up
        self.new_puzzle_with_clues(25)  # Start with medium difficulty
    
    def _generate_puzzle(self, clues=25):
        """Generate a random Sudoku puzzle with specified number of clues."""
        # Create a solved puzzle first
        solved = [[0]*9 for _ in range(9)]
        sudoku = SudokuCSP(solved)
        solution = sudoku.solve()
        
        if not solution:
            return [[0]*9 for _ in range(9)]
        
        # Remove numbers to create puzzle
        puzzle = [row.copy() for row in solution]
        positions = [(i,j) for i in range(9) for j in range(9)]
        random.shuffle(positions)
        
        for i, j in positions[:-clues]:
            puzzle[i][j] = 0
        
        return puzzle
    
    def _create_menu(self):
        menubar = tk.Menu(self.root, bg='#e6f2ff', fg='#333333', activebackground='#cce0ff')
        
        file_menu = tk.Menu(menubar, tearoff=0, bg='#e6f2ff', fg='#333333')
        file_menu.add_command(label="New Puzzle", command=self.new_puzzle, accelerator="Ctrl+N")
        file_menu.add_command(label="Generate Easy", command=lambda: self.new_puzzle_with_clues(35))
        file_menu.add_command(label="Generate Medium", command=lambda: self.new_puzzle_with_clues(25))
        file_menu.add_command(label="Generate Hard", command=lambda: self.new_puzzle_with_clues(17))
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.root.quit, accelerator="Alt+F4")
        menubar.add_cascade(label="File", menu=file_menu)
        
        help_menu = tk.Menu(menubar, tearoff=0, bg='#e6f2ff', fg='#333333')
        help_menu.add_command(label="About", command=self.show_about)
        help_menu.add_command(label="How to Play", command=self.show_instructions)
        menubar.add_cascade(label="Help", menu=help_menu)
        
        self.root.config(menu=menubar)
        self.root.bind('<Control-n>', lambda e: self.new_puzzle())
        self.root.bind('<Alt-F4>', lambda e: self.root.quit())
    
    def _create_header(self):
        header_frame = tk.Frame(self.root, bg='#5f9ea0')
        header_frame.pack(fill=tk.X, padx=5, pady=(5, 0))
        
        title = tk.Label(
            header_frame, text="SUDOKU SOLVER", 
            font=('Arial Rounded MT Bold', 24, 'bold'), 
            fg='white', bg='#5f9ea0', pady=10
        )
        title.pack()
        
        subtitle = tk.Label(
            header_frame, text="CSP Implementation with Backtracking", 
            font=('Arial', 10, 'italic'), 
            fg='#e6f2ff', bg='#5f9ea0'
        )
        subtitle.pack(pady=(0, 10))
    
    def _create_board(self):
        board_frame = tk.Frame(self.root, bg='#5f9ea0', padx=5, pady=5)
        board_frame.pack(pady=10)
        
        canvas = tk.Canvas(board_frame, width=450, height=450, bg='white', highlightthickness=0)
        canvas.pack()
        
        for i in range(0, 4):
            line_width = 3 if i % 3 == 0 else 1
            canvas.create_line(i*150, 0, i*150, 450, width=line_width, fill='#333333')
            canvas.create_line(0, i*150, 450, i*150, width=line_width, fill='#333333')
        
        for i in range(9):
            for j in range(9):
                x = j * 50 + 5
                y = i * 50 + 5
                
                cell = tk.Entry(
                    canvas, width=2, font=('Arial', 24),
                    justify='center', borderwidth=0,
                    highlightthickness=1, highlightbackground='#cccccc',
                    bg='white', fg='#333333'
                )
                cell.place(x=x, y=y, width=40, height=40)
                
                cell.bind('<FocusIn>', lambda e, c=cell: c.config(bg='#f0f8ff') if c.get() == '•' else None)
                cell.bind('<FocusOut>', lambda e, c=cell: c.config(bg='white') if c.get() == '•' else None)
                cell.bind('<Key>', self._handle_cell_key)
                
                cell['validate'] = 'key'
                cell['validatecommand'] = (cell.register(self._validate_input), '%P')
                
                self.cells[(i, j)] = cell
    
    def _handle_cell_key(self, event):
        """Handle key events for cells."""
        cell = event.widget
        if cell.get() == '•' and event.char.isdigit() and 1 <= int(event.char) <= 9:
            cell.delete(0, tk.END)
            cell.insert(0, event.char)
            cell.config(fg='#333333')
    
    def _validate_input(self, new_text):
        if new_text == "" or new_text == "•":
            return True
        if len(new_text) > 1:
            return False
        return new_text.isdigit() and 1 <= int(new_text) <= 9
    
    def _create_buttons(self):
        button_frame = tk.Frame(self.root, bg='#f0f8ff')
        button_frame.pack(pady=10)
        
        style = ttk.Style()
        style.configure('TButton', font=('Arial', 12), padding=5)
        style.map('TButton',
            foreground=[('pressed', 'white'), ('active', 'white')],
            background=[('pressed', '#3a7a7c'), ('active', '#4d9a9c')]
        )
        
        solve_btn = ttk.Button(
            button_frame, text="Solve Puzzle", command=self.solve_puzzle,
            style='TButton'
        )
        solve_btn.pack(side=tk.LEFT, padx=10, ipadx=10)
        
        clear_btn = ttk.Button(
            button_frame, text="Clear Board", command=self.clear_board,
            style='TButton'
        )
        clear_btn.pack(side=tk.LEFT, padx=10, ipadx=10)
        
        for btn in [solve_btn, clear_btn]:
            btn.bind('<Enter>', lambda e, b=btn: b.config(style='TButton'))
            btn.bind('<Leave>', lambda e, b=btn: b.config(style='TButton'))
    
    def _create_footer(self):
        footer_frame = tk.Frame(self.root, bg='#5f9ea0', height=30)
        footer_frame.pack(fill=tk.X, padx=5, pady=(0, 5))
        
        footer_text = tk.Label(
            footer_frame, text="© 2023 Sudoku Solver | CSP Implementation", 
            font=('Arial', 8), fg='white', bg='#5f9ea0'
        )
        footer_text.pack(pady=5)
    
    def get_puzzle(self):
        puzzle = [[0]*9 for _ in range(9)]
        for i in range(9):
            for j in range(9):
                value = self.cells[(i, j)].get()
                if value.isdigit() and 1 <= int(value) <= 9:
                    puzzle[i][j] = int(value)
        return puzzle
    
    def solve_puzzle(self):
        puzzle = self.get_puzzle()
        
        solving_label = tk.Label(
            self.root, text="Solving...", 
            font=('Arial', 12, 'italic'), fg='#5f9ea0', bg='#f0f8ff'
        )
        solving_label.pack()
        self.root.update()
        
        start_time = time.time()
        sudoku = SudokuCSP(puzzle)
        solution = sudoku.solve()
        solving_time = time.time() - start_time
        
        solving_label.pack_forget()
        
        if solution:
            self.display_solution(solution)
            messagebox.showinfo(
                "Success", 
                f"Sudoku solved in {solving_time:.2f} seconds!"
            )
        else:
            messagebox.showerror(
                "No Solution", 
                "No valid solution exists for this puzzle configuration."
            )
    
    def display_solution(self, solution):
        for i in range(9):
            for j in range(9):
                cell = self.cells[(i, j)]
                current_value = cell.get()
                cell.config(state='normal')
                cell.delete(0, tk.END)
                cell.insert(0, str(solution[i][j]))
                
                if current_value == "•" or current_value == "":
                    cell.config(state='readonly', readonlybackground='#f0f8ff', fg='black')
                else:
                    cell.config(state='readonly', readonlybackground='#e6f2ff', fg='#1a5f7a')
    
    def clear_board(self):
        for i in range(9):
            for j in range(9):
                self.cells[(i, j)].config(state='normal', bg='white', fg='#333333')
                self.cells[(i, j)].delete(0, tk.END)
                self.cells[(i, j)].insert(0, '•')
                self.cells[(i, j)].config(fg='#aaaaaa')
    
    def new_puzzle(self):
        self.new_puzzle_with_clues(25)  # Default to medium difficulty
    
    def new_puzzle_with_clues(self, clues):
        self.puzzle = self._generate_puzzle(clues)
        for i in range(9):
            for j in range(9):
                self.cells[(i, j)].config(state='normal')
                self.cells[(i, j)].delete(0, tk.END)
                if self.puzzle[i][j] != 0:
                    self.cells[(i, j)].insert(0, str(self.puzzle[i][j]))
                    self.cells[(i, j)].config(fg='#1a5f7a', readonlybackground='#e6f2ff', state='readonly')
                else:
                    self.cells[(i, j)].insert(0, '•')
                    self.cells[(i, j)].config(fg='#aaaaaa', state='normal')
        
        difficulty = {35: "Easy", 25: "Medium", 17: "Hard"}.get(clues, "")
        messagebox.showinfo("New Puzzle", f"New {difficulty} puzzle generated with {clues} clues!")
    
    def show_about(self):
        about_text = (
            "Sudoku Solver v2.0\n\n"
            "This application uses Constraint Satisfaction Problem (CSP) techniques\n"
            "with backtracking search to solve Sudoku puzzles.\n\n"
            "Features:\n"
            "• Generate puzzles with different difficulty levels\n"
            "• Visual distinction between clues and solved numbers\n"
            "• Dots (•) represent empty cells\n\n"
            "Created with Python and Tkinter"
        )
        messagebox.showinfo("About Sudoku Solver", about_text)
    
    def show_instructions(self):
        instructions = (
            "How to Use the Sudoku Solver:\n\n"
            "1. Enter numbers in the dotted cells (•)\n"
            "2. Click 'Solve Puzzle' to find the solution\n"
            "3. Use 'Clear Board' to reset\n"
            "4. Generate new puzzles from the File menu\n\n"
            "Blue numbers are fixed clues\n"
            "Black numbers are your entries\n"
            "Dots (•) represent empty cells"
        )
        messagebox.showinfo("How to Play Sudoku", instructions)


if __name__ == "__main__":
    root = tk.Tk()
    app = SudokuGUI(root)
    root.mainloop()