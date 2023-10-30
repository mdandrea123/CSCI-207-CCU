import pandas as pd
import matplotlib.pyplot as plt

# Step 1: Read data from the CSV file
df = pd.read_csv('results.csv')  # Replace 'your_data.csv' with the actual file name

# Step 2: Extract x and y data
x = df['Trials']
y = df['Probability']

# Step 3: Create a line chart
plt.figure(figsize=(10, 6))  # Adjust the figure size as needed

# Use a logarithmic scale for the x-axis
plt.semilogx(x, y, marker='o', linestyle='-')  # Customize markers and linestyle
plt.title('Probability vs. Trials (Logarithmic Scale for Trials)')
plt.xlabel('Trials (log scale)')  # Label for the x-axis with log scale
plt.ylabel('Probability')  # Label for the y-axis
plt.grid(True)  # Add grid lines (optional)

# Step 4: Show the chart in a window or save it to a file (or both)
plt.show()
# Optionally, save the chart to a file (e.g., PNG) with the following line:
# plt.savefig('line_chart.png')
