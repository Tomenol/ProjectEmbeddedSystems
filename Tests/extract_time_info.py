import numpy as np

filename = "gdb_result_001.txt"
test_names = ["compute_median", "compute_mean", "store_reference", "compute_hotspot_count"]

file = open(filename, "r")

def get_sim_results():
	iter_ = 0
	step_id = 0
	sim_name = None

	step_cycles = [[] for i in range(len(test_names))]

	# read and process file
	for line in file.readlines():
		if "sim_" in line:
			if iter_ > 0:
				print_sim_performances(sim_name, iter_, step_cycles)

			# reset vars
			iter_ = 0
			step_cycles = [[] for i in range(len(test_names))]

			# get simulation name
			for str_ in line.split(" "):
				if "sim_" in str_:
					sim_name = str_

		if "test = reset" in line:
			# print("\nIteration n° : ", iter_)
			iter_ += 1
		
		# get test name
		for i, name in enumerate(test_names):
			if name in line and "=" in line and "***" in line:
				step_id = i
				break
		
		# get cycle count
		if "Cycles" in line and ":" in line:
			cycles = int(line.strip(" Cycles       :      "))
			# print("   ", test_names[step_id], "cycles : ", cycles)

			step_cycles[step_id] += [cycles]

	print_sim_performances(sim_name, iter_, step_cycles)

def print_sim_performances(sim_name, iterations, step_cycles):
	print(f"\nOveraul performances ({sim_name}): ")
	print("Number of iterations ", iterations)
	print("{:<30} {:<15} {:<15} {:<15} {:<15}".format("Step", "Mean", "Min", "Max", "Std"))
	for i, name in enumerate(test_names):
		print("{:<30} {:<15} {:<15} {:<15} {:<15}".format(name, int(np.mean(step_cycles[i])), np.min(step_cycles[i]), np.max(step_cycles[i]), np.std(step_cycles[i])))

if __name__ == "__main__":
	get_sim_results()