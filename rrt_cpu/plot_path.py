import matplotlib.pyplot as plt
import matplotlib.patches as patches

plt.axis('equal')

map_file = "map4.txt"
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

# map_file = "cmake-build-debug/quadtree_nodes.txt"
# f = open(map_file)
# line = f.readline()
# line_ctr = 0
# x,y = [], []
# while line:
#     line = list(map(float, line.split(" ")))
#     x.append(line[0])
#     y.append(line[1])
#     line = f.readline()
#     line_ctr += 1
# plt.scatter(x, y, marker="*", color="green")
# plt.pause(1)-debug/quad_false_nodes.txt"
# f = open(map_file)
# line = f.readline()
# line_ctr = 0
# x,y = [], []
# while line:
#     line = list(map(float, line.split(" ")))
#     x.append(line[0])
#     y.append(line[1])
#     line = f.readline()
#     line_ctr += 1
# plt.scatter(x, y, marker="*", color="cyan")
# plt.pause(1)
#
# map_file = "cmake-build-debug/false_nodes.txt"
# f = open(map_file)
# line = f.readline()
# line_ctr = 0
# x,y = [], []
# while line:
#     line = list(map(float, line.split(" ")))
#     x.append(line[0])
#     y.append(line[1])
#     line = f.readline()
#     line_ctr += 1
# plt.scatter(x, y, marker="*", color="yellow")
# plt.pause(1)
#
# map_file = "cmake-build-debug/quad_false_nodes.txt"
# f = open(map_file)
# line = f.readline()
# line_ctr = 0
# x,y = [], []
# while line:
#     line = list(map(float, line.split(" ")))
#     x.append(line[0])
#     y.append(line[1])
#     line = f.readline()
#     line_ctr += 1
# plt.scatter(x, y, marker="*", color="cyan")
# plt.pause(1)


color = ['b', 'r']
file = "cmake-build-debug/path_raw.txt"
f = open(file)
file = "cmake-build-debug/path_raw.txt"
f = open(file)
line = f.readline()
l_x, l_y,l_c = [], [], []
start, end = [], []
k = 0
while line:
    line = list(map(float, line.split(" ")))
    if k == 0:
        start = [line[0], line[1]]
        end = [line[2], line[3]]
        k+=1
    else:
        l_x.extend([line[0], line[2]])
        l_y.extend([line[1], line[3]])
        l_c.extend([color[int(line[4])],color[int(line[4])]])
    # plt.plot(Xs, Ys, marker="o", color=color[int(line[4])])
    line = f.readline()
plt.scatter(l_x, l_y, marker="o", s=0.1, color=l_c)
plt.plot(start[0], start[1], marker="o", markersize=10, color="orange")
plt.plot(end[0], end[1], marker="o", markersize=10, color="green")
plt.pause(1)

# line = f.readline()
# l_x, l_y,l_c = [], [], []
# start, end = [], []
# k = 0
# while line:
#     line = list(map(float, line.split(" ")))
#     if k == 0:
#         start = [line[0], line[1]]
#         end = [line[2], line[3]]
#         k+=1
#     else:
#         l_x.extend([line[0], line[2]])
#         l_y.extend([line[1], line[3]])
#         l_c.extend([color[int(line[4])],color[int(line[4])]])
#     # plt.plot(Xs, Ys, marker="o", color=color[int(line[4])])
#     line = f.readline()
# plt.scatter(l_x, l_y, marker="o", s=0.1, color=l_c)
# plt.plot(start[0], start[1], marker="o", markersize=10, color="orange")
# plt.plot(end[0], end[1], marker="o", markersize=10, color="green")
# plt.pause(1)



# from matplotlib.collections import PatchCollection
# import matplotlib
# import matplotlib.pyplot as plt
# import random
# fig = plt.figure()
# ax = fig.add_subplot(111, aspect='equal')
# file = "cmake-build-debug/quadtree.txt"
# f = open(file)
# line = f.readline()
# k = 0
# patches = []
# while line:
#     k+=1
#     line = list(map(float, line.split(" ")))
#     X1 = [line[0], line[1]]
#     X2 = [line[2], line[1]]
#     X3 = [line[2], line[3]]
#     X4 = [line[0], line[3]]
#     # print((X1[0], X1[1]),abs(X2[0]-X1[0]),abs(X4[1]-X1[1]))
#     patches.append(matplotlib.patches.Rectangle((X1[0], X1[1]), abs(X2[1]-X1[1]), abs(X4[0]-X1[0])))
#     line = f.readline()
# ax.add_collection(PatchCollection(patches))
# print("done quadtree")
# plt.show()

# from matplotlib.collections import PatchCollection
# import matplotlib
# import matplotlib.pyplot as plt
# import random
#
# # fig = plt.figure()
# # ax = fig.add_subplot(111, aspect='equal')
# # plt.xlim([0, 1001])
# # plt.ylim([0, 1001])
# n=10000
# patches = []
# for i in range(0,n):
#     x = random.uniform(1, 1000)
#     y = random.uniform(1, 1000)
#     patches.append(matplotlib.patches.Rectangle((x, y),1,1,))
# ax.add_collection(PatchCollection(patches))
# plt.show()
# print("--")
#


# file = "cmake-build-debug/quadtree.txt"
#     k+=1
#     line = list(map(float, line.split(" ")))
#     X1 = [line[0], line[1]]
#     X2 = [line[2], line[1]]
#     X3 = [line[2], line[3]]
#     X4 = [line[0], line[3]]
#     # print((X1[0], X1[1]),abs(X2[0]-X1[0]),abs(X4[1]-X1[1]))
#     patches.append(matplotlib.patches.Rectangle((X1[0], X1[1]), abs(X2[1]-X1[1]), abs(X4[0]-X1[0])))
#     line = f.readline()
# ax.add_collection(PatchCollection(patches))
# print("done quadtree")
# plt.show()

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
#     plt.plot([X1[0], X2[0]] , [X2[1], X1[1]], marker="o", color="y")
#     plt.plot([X2[0], X3[0]] , [X3[1], X2[1]], marker="o", color="y")
#     plt.plot([X3[0], X4[0]] , [X4[1], X3[1]], marker="o", color="y")
#     plt.plot([X4[0], X1[0]] , [X1[1], X4[1]], marker="o", color="y")
#     line = f.readline()
#     if k%1000==0: print(k)
#     if k>5000: break

plt.show()