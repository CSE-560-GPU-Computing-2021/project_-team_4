import matplotlib.pyplot as plt
import matplotlib.patches as patches

plt.axis('equal')

map_file = "map2.txt"
f = open(map_file)
line = f.readline()
line_ctr = 0
x,y = [], []
while line:
    line = list(map(float, line.split(" ")))
    x.append(line[0])
    y.append(line[1])
    line = f.readline()
    line_ctr += 1
plt.scatter(x, y, marker="*", color="black")
plt.pause(1)

map_file = "cmake-build-debug/quadtree_nodes.txt"
f = open(map_file)
line = f.readline()
while line:
    line = list(map(float, line.split(" ")))
    plt.plot(line[0], line[1], marker="*", color="green")
    line = f.readline()
plt.pause(1)


# color = ['b', 'r']
# file = "cmake-build-debug/path_raw.txt"
# f = open(file)
# line = f.readline()
# l_x, l_y,l_c = [], [], []
# while line:
#     line = list(map(float, line.split(" ")))
#     l_x.extend([line[0], line[2]])
#     l_y.extend([line[1], line[3]])
#     l_c.extend([color[int(line[4])],color[int(line[4])]])
#     # plt.plot(Xs, Ys, marker="o", color=color[int(line[4])])
#     line = f.readline()
# plt.scatter(l_x, l_y, marker="o", color=l_c)
plt.pause(1)
# file = "cmake-build-debug/quadtree.txt"
# f = open(file)
# line = f.readline()
# k = 0
# while line:
#     k+=1
#     line = list(map(float, line.split(" ")))
#     X1 = [line[0], line[1]]
#     X2 = [line[2], line[1]]
#     X3 = [line[2], line[3]]
#     X4 = [line[0], line[3]]
#     if  180 < X1[1] < 220:
#         plt.plot([X1[0], X2[0]] , [X2[1], X1[1]], marker="o", color="y")
#         plt.plot([X2[0], X3[0]] , [X3[1], X2[1]], marker="o", color="y")
#         plt.plot([X3[0], X4[0]] , [X4[1], X3[1]], marker="o", color="y")
#         plt.plot([X4[0], X1[0]] , [X1[1], X4[1]], marker="o", color="y")
#     line = f.readline()
#     if k%1000==0: print(k)
plt.show()