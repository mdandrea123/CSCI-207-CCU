import pandas as pd
import matplotlib.pyplot as plt

# Step 1: Read data from the CSV file
df = pd.read_csv('results.csv')  # Replace 'your_data.csv' with the actual file name

# Step 2: Extract x and y data
x = df['Trials']
y = df['Probability']

# Step 3: Create a line chart
plt.figure(figsize=(12, 6))  # Adjust the figure size as needed

# Generate the custom x-axis values
x_values = range(1000000, 100000001, 1000000)

plt.plot(x, y, marker='o', linestyle='-')  # Customize markers and linestyle
plt.title('Probability vs. Trials')
plt.xlabel('Trials')
plt.ylabel('Probability')
plt.xticks(x_values)  # Set custom x-axis values
plt.grid(True)  # Add grid lines (optional)

# Step 4: Show the chart in a window or save it to a file (or both)
plt.show()
# Optionally, save the chart to a file (e.g., PNG) with the following line:
# plt.savefig('line_chart.png')
