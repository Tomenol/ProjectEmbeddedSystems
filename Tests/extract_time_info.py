import numpy as np

filename = "gdb_result_001.txt"
filename_ref = "hotspots_count.txt"

test_names = ["acquire_raw_data", "compute_median", "compute_mean", "store_reference", "compute_hotspot_count"]

file = open(filename, "r")
file_hs_count = open(filename_ref, "r")

def get_hs_count_expected():
	hs_count_expected = []

	for line in file_hs_count.readlines():
		hs_count_expected += [int(line.split(" ")[-1])]

	return hs_count_expected

def get_sim_results(hs_count_expected):
	iter_ = 0
	step_id = 0
	sim_name = None

	step_cycles = [[] for i in range(len(test_names))]
	hs_count = []

	# read and process file
	for line in file.readlines():
		if "sim_" in line:
			if iter_ > 0:
				print_sim_performances(sim_name, iter_, step_cycles, hs_count, hs_count_expected)

			# reset vars
			iter_ = 0
			step_cycles = [[] for i in range(len(test_names))]
			hs_count = []

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

		# get cycle count
		if "$" in line and "=" in line:
			if test_names[step_id] == "compute_hotspot_count" or test_names[step_id] == "store_reference":
				hs_count += [int(line.split(" ")[-1])]

	print_sim_performances(sim_name, iter_, step_cycles, hs_count, hs_count_expected)


def print_sim_performances(sim_name, iterations, step_cycles, hs_count, hs_count_expected):
	print(f"\n\nOveraul performances ({sim_name}): ")
	print("Number of iterations ", iterations)

	print("{:<30} {:<15} {:<15} {:<15} {:<15}".format("Step", "Mean", "Min", "Max", "Std"))
	for i, name in enumerate(test_names):
		print("{:<30} {:<15} {:<15} {:<15} {:<15}".format(name, int(np.mean(step_cycles[i])), np.min(step_cycles[i]), np.max(step_cycles[i]), np.std(step_cycles[i])))

	print("\nHS count differences (sim ids) : 	", np.where(np.array(hs_count_expected) != np.array(hs_count))[0])	

if __name__ == "__main__":
	hs_count_expected = get_hs_count_expected()

	get_sim_results(hs_count_expected)

	