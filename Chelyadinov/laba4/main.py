import sys
def search_cheap_travel(graph, value):
    global gl_min
    gl_min = 100000
    search_cheap_travel1(graph, 0, value, [], 0, len(graph) - 1)
    if gl_min == 100000:
        return -1
    else:
        return gl_min


def search_cheap_travel1(graph, city, value, check, loc_min, end_city):
    _check = list(check)
    _check.append(city)
    loc_min = loc_min + value[city]
    for next_city in graph[city]:
        if next_city not in _check:
            if next_city == end_city:
                _check.append(next_city)
                print (_check, '=', loc_min)
                global gl_min
                if gl_min > loc_min:
                    gl_min = loc_min
            else:
                search_cheap_travel1(graph, next_city, value, _check, loc_min, end_city)



f = "input.txt"
try:
    file = open(f)
except IOError:
    print ('File not found')
    sys.exit()
line = file.read().split('\n')
N = int(line[0])
line[1] = line[1].split(' ')
M = int(line[2])
roads = line[3].split(' ')
value = {a: int(line[1][a]) for a in range(N)}
graph = [[] for i in range(N)]
for i in range(0, M * 2, 2):
    graph[int(roads[i]) - 1].append(int(roads[i + 1]) - 1)
    graph[int(roads[i + 1]) - 1].append(int(roads[i]) - 1)
print (graph, '-graph')
print (value, '-prices')
print (search_cheap_travel(graph, value), '-minimum value')