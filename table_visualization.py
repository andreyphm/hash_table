import matplotlib.pyplot as plt

with open("output.txt", "r", encoding="utf-8") as file:
    capacity = int(file.readline())
    counts = [0] * capacity

    for line in file:
        parts = line.split()

        if not parts:
            continue

        if parts[0].isdigit():
            list_index = int(parts[0])
            counts[list_index] += len(parts) - 1

        else:
            counts[list_index] += len(parts)

x = list(range(capacity))   # x = {0, 1, 2, ...} list
y = counts

plt.figure(figsize=(20, 6))
plt.bar(x, y, width = 1.0)
plt.xlim(0, capacity - 1)   # removes voids
plt.xlabel("List index")
plt.ylabel("Number of elements")
plt.title("Hash table distribution")
plt.savefig("table_visualization.png")
