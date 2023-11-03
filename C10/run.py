import subprocess

# Define the base command with placeholders for -n and the output redirection
base_command = "./simple_mbe_test -n {} -p > logfile.csv"

# Define the initial and final values for -n
start_value = 1000000
end_value = 100000000
increment = 1000000

# Execute the command with -n incrementing in each iteration
for n in range(start_value, end_value + 1, increment):
    command = base_command.format(n)
    try:
        # Use subprocess to run the command
        subprocess.run(command, shell=True, check=True)
        
        # Print a message every 1,000,000 iterations
        if n % 1000000 == 0:
            print(f"Execution with -n {n} is done.")
    except subprocess.CalledProcessError as e:
        print(f"Command failed with exit code {e.returncode}")
    except Exception as e:
        print(f"An error occurred: {str(e)}")

print(f"All executions completed. Output saved to 'logfile.csv'.")
