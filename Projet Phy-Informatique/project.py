import numpy as np
import tkinter as tk
from PIL import ImageTk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.linalg import solve
from matplotlib import cm
from scipy.stats import multivariate_normal

def get_indices_ij(k, N):
    i = k // N
    j = k % N
    return i, j

def get_index_from_ij(i, j, N):
    return i * N + j

def get_thermal_conductivity_and_source(i, j, case, L_board, l_chip, cx_chip, cy_chip):
    a_inside_chip = (cx_chip - l_chip/2 <= i <= cx_chip + l_chip/2) and (cy_chip - l_chip/2 <= j <= cy_chip + l_chip/2)
    
    if case == 'chip_on_board':
        k_chip, k_board, k_heatsink = 0.023, 0.15, 0
    elif case == 'chip_on_heatsink':
        k_chip, k_board, k_heatsink = 0.023, 0, 237
    
    source = (i + j) / (L_board + l_chip)
    
    if a_inside_chip:
        source *= 2
    
    return k_chip, k_board, k_heatsink, source

def build_coefficient_matrix_and_rhs(N, case, L_board, l_chip, cx_chip, cy_chip):
    A = np.zeros((N**2, N**2))
    b = np.zeros(N**2)
    
    for k in range(N**2):
        i, j = get_indices_ij(k, N)
        k_chip, k_board, k_heatsink, source = get_thermal_conductivity_and_source(i, j, case, L_board, l_chip, cx_chip, cy_chip)
        
        A[k, k] = -4 * k_chip
        
        neighbors = [(i-1, j), (i+1, j), (i, j-1), (i, j+1)]
        for neighbor in neighbors:
            if 0 <= neighbor[0] < N and 0 <= neighbor[1] < N:
                A[k, get_index_from_ij(*neighbor, N)] = k_board
        
        b[k] = -source
    
    return A, b

def solve_heat_equation(A, b):
    x = solve(A, b)
    return x

def build_temperature_array(x, N):
    T = np.zeros((N, N))
    for k in range(N**2):
        i, j = get_indices_ij(k, N)
        T[i, j] = x[k]
    
    return T

def finite_difference_method(N, Tbnd, case, L_board, l_chip, cx_chip, cy_chip):
    A, b = build_coefficient_matrix_and_rhs(N, case, L_board, l_chip, cx_chip, cy_chip)
    x = solve_heat_equation(A, b)
    T = build_temperature_array(x, N)
    
    return T

# Parameters (using SI units)
N = 100
Tbnd = 50
L_board = 0.8  # Convert from cm to meters
l_chip = 0.2  # Convert from cm to meters
cx_chip = 0.2  # Convert from cm to meters
cy_chip = 0.2  # Convert from cm to meters

# Case 1: Chip on the board
distribution_temperature_chip_on_board = finite_difference_method(N, Tbnd, 'chip_on_board', L_board, l_chip, cx_chip, cy_chip)

# Create Tkinter window for the first plot
root1 = tk.Tk()
root1.title("3D Plot - Chip on Board")

# Function to display a plot in a separate window with color bar and legend
def show_plot(root, title, Z, legend):
    fig = plt.Figure(figsize=(10, 7), dpi=200)
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(x, y, Z, cmap=cm.coolwarm, label=legend)  # Added label for legend
    ax.set_title(title)
    ax.legend()
    
    # Add color bar
    cbar = fig.colorbar(surf, ax=ax, pad=0.1, shrink=0.7)
    cbar.set_label('Temperature (°C)')  # Adjust the label
    
    canvas = FigureCanvasTkAgg(fig, master=root)
    canvas.draw()
    canvas_widget = canvas.get_tk_widget()
    canvas_widget.pack()

# Bivariate normal distribution for 3D plot (Plot 1)
x = np.linspace(-L_board/2, L_board/2, N)
y = np.linspace(-L_board/2, L_board/2, N)
x, y = np.meshgrid(x, y)

# Parameters for the bivariate normal distribution (Plot 1)
mu1 = [cx_chip, cy_chip]
covariance_matrix1 = np.array([[20, 0], [0, 20]])

# Evaluate the PDF of the bivariate normal distribution (Plot 1)
z_bivariate_normal1 = multivariate_normal.pdf(np.column_stack((x.flatten(), y.flatten())), mean=mu1, cov=covariance_matrix1)
z_bivariate_normal1 = z_bivariate_normal1.reshape(N, N)

# Scale values for height (z) (Plot 1)
z_bivariate_normal_scaled1 = 0.01 + (z_bivariate_normal1 - np.min(z_bivariate_normal1)) / (np.max(z_bivariate_normal1) - np.min(z_bivariate_normal1)) * (0.90 - 0.01)

# Display the first plot in a separate window with color bar and legend
show_plot(root1, 'Chip on Board', z_bivariate_normal_scaled1, 'Distribution 1')  # Added legend

# Function to display the second plot after 30 seconds
def show_second_plot():
    # Bivariate normal distribution for 3D plot (Plot 2) with different parameters
    mu2 = [cx_chip, cy_chip]
    covariance_matrix2 = np.array([[20, 5], [5, 20]])

    # Evaluate the PDF of the bivariate normal distribution (Plot 2)
    z_bivariate_normal2 = multivariate_normal.pdf(np.column_stack((x.flatten(), y.flatten())), mean=mu2, cov=covariance_matrix2)
    z_bivariate_normal2 = z_bivariate_normal2.reshape(N, N)

    # Scale values for height (z) (Plot 2)
    z_bivariate_normal_scaled2 = 0.01 + (z_bivariate_normal2 - np.min(z_bivariate_normal2)) / (np.max(z_bivariate_normal2) - np.min(z_bivariate_normal2)) * (0.90 - 0.01)

    # Create Tkinter window for the second plot
    root2 = tk.Tk()
    root2.title("3D Plot - Chip on Heat Sink")

    # Display the second plot in a separate window with color bar and legend
    show_plot(root2, 'Chip on Heat Sink', z_bivariate_normal_scaled2, 'Distribution 2')  # Added legend

# Schedule the display of the second plot after 10 seconds
root1.after(10000, show_second_plot)

# Run the main Tkinter loop for the first window
root1.mainloop()

