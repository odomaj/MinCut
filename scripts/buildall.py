import os

print('bulding project...')

if(os.path.exists(os.getcwd() + '/../build')):
    os.chdir('../build')
else:
    os.chdir('../')
    os.system('mkdir build')
    os.chdir('build')

os.system('g++ -std=c++11 ../src/io/IO.cpp ../src/graph/Graph.cpp ../src/graph/Node.cpp ../src/cut/Cut.cpp ../src/main.cpp -o main')

print('build complete')