import csv
import matplotlib.pyplot as plt

# Initialize a list to store the header-value pairs for each line of data.
data_list = []

# Replace 'your_input_file.csv' with the path to your CSV file.
input_file = 'logfile.csv'

# Read the CSV file and process the lines.
with open(input_file, 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    
    for row in csv_reader:
        data_dict = {}
        for entry in row:
            # Split the entry into header and value using '=' as the delimiter.
            if(entry.startswith('BP')):
                parts = entry.strip().split('=')
                if len(parts) == 2:
                    header, value = parts
                    data_dict[header.strip()] = value.strip()
            else:
                break
            data_list.append(data_dict)

# Sort the data_list by the 'BP' key
data_list = sorted(data_list, key=lambda x: int( x['BP']))

# Replace 'your_output_file.csv' with the desired output file path.
output_file = 'data.csv'

# Write the header and corresponding values to a new CSV file.
with open(output_file, 'w', newline='') as csv_file:
    csv_writer = csv.writer(csv_file)

    # Write the header row
    header_row = data_list[0].keys()
    csv_writer.writerow(header_row)

    # Write the values in subsequent rows
    for data_dict in data_list:
        value_row = data_dict.values()
        csv_writer.writerow(value_row)

print("Data sorted and written to", output_file)

bp_values = [int(data['BP']) for data in data_list]

# Create the histogram
plt.hist(bp_values, bins=range(33), align='left', rwidth=0.8)
plt.xlabel('BP Values')
plt.ylabel('Frequency')
plt.title('BP Value Frequency Histogram')
plt.xticks(range(32))

# Annotate the bars with their frequencies
for i, count in enumerate(plt.hist(bp_values, bins=range(33), align='left', rwidth=0.8)[0]):
    if count > 0:
        plt.text(i, count, int(count), ha='center', va='bottom')
plt.show()
