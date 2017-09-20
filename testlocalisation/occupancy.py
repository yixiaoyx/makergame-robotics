from numpy import *
from copy import copy
import matplotlib.pyplot as plt
%matplotlib inline

def reset():
    g =    matrix([[1,1,1,1,1,1,1,1,1,1],
                   [1,1,1,1,0,0,0,0,0,1],
                   [1,1,0,0,0,0,0,0,0,1],
                   [1,0,0,0,0,1,0,0,0,1],
                   [1,0,0,0,0,1,0,0,0,1],
                   [1,0,0,0,0,1,0,0,0,1],
                   [1,0,0,0,1,1,0,0,0,1],
                   [1,0,0,0,0,0,0,0,0,1],
                   [1,0,0,0,0,0,0,0,1,1],
                   [1,1,1,1,1,1,1,1,1,1]])

    sensor = matrix(zeros((3,3)))
    map = matrix(zeros(g.shape))
    sensor[1,1] = 3
    return g, map, sensor

def detect():
    now = where(g == 3)
    sensor = g[now[0][0]-1:now[0][0]+2, now[1][0]-1:now[1][0]+2]
    return sensor

def move(action):
    sensor = detect()
    good = 0
    now = where(map == 3)

    if action == 'left':
        if sensor[1,0] != 1: map[now[0], now[1]-1] = 3; good = 1;
    elif action == 'right':
        if sensor[1,2] != 1: map[now[0], now[1]+1] = 3; good = 1;
    elif action == 'up':
        if sensor[0,1] != 1: map[now[0]-1, now[1]] = 3; good = 1;
    elif action == 'down':
        if sensor[2,1] != 1: map[now[0]+1, now[1]] = 3; good = 1;

    if good == 1:
        g[where(map == 3)] = 3
        g[now] = 2
        map[now] = 2
    else:
        return 'invalid'

def show(im):
    fig, ax = plt.subplots(figsize=(2,2))
    ax.matshow(im)

def update(move1, move2):
    g[move1,move2] = 3
    map[move1,move2] = 3

def check(what):
    now = where(map == 3)
    if what == 'left': return g[now[0], now[1]-1]
    elif what == 'right': return g[now[0], now[1]+1]
    elif what == 'up': return g[now[0]-1, now[1]]
    elif what == 'down': return g[now[0]+1, now[1]]
In [2]:
g, map, sensor = reset()
update(8,1)
change, tried = 0, 0
state = [-10,-9,-8]

for time in range(80):

    current = where(g==3)

    if tried == 1:
        move('down')

    if state[0] == state[2]:
        break

    if current == state[-1]:
        if check('right')!=1:
            move('right')
        else:
            move('down')
            change = 0
            tried = 1

    if check('up') == 0 and change == 0:
        if check('left') == 0:
            if check('down') == 0:
                change = 1
            else:
                move('left')
        else:
            move('up')
    elif change == 0:
        if check('down') == 0:
            move('down')
        else:
            if check('left') == 0:
                move('left')
            else:
                move('right')
        change = 1
    elif check('down') == 0:
        if check('left') == 0:
            move('left')
        else:
                move('down')
    elif check('right') == 0:
        move('right')
        change = 0
    else:
        if check('up') == 0:
            change = 0
        else:
            if check('left') == 0:
                move('left')
            else:
                move('up')
                change = 0

    state.append(current)
    state = state[::-1][0:3][::-1]
    show(g)
