import matplotlib.pyplot as plt
from matplotlib.backend_bases import MouseButton
import numpy as np
import math

def clamp(n, smallest, largest): 
    return max(smallest, min(n, largest))

# Display settings
aspect_ratio = 16/9
refresh_rate_hz = 60

# Game settings
num_balls = 10
max_speed = 0.04
min_speed = max_speed/2.0
dwell_steps = 200

# Random initial headings, speeds, and coords
headings = 2*math.pi*np.random.random(num_balls)
speeds = min_speed + (max_speed-min_speed)*np.random.random(num_balls)
xcoord = aspect_ratio*np.random.random(num_balls)
ycoord = np.random.random(num_balls)

# Create figure
figure, ax = plt.subplots()

# Add vars for exiting game
run_game = False
def on_click(event):
    global run_game
    if event.button is MouseButton.LEFT:
        run_game = not run_game
        print(run_game)

def on_key_press(event):
    if event.key == 'q':
        exit()

plt.connect('button_press_event', on_click)
plt.connect('key_press_event', on_key_press)

while True:
    # Clear figure and wait for game start
    dp = []
    ax.clear()
    plt.xlim([0, aspect_ratio])
    plt.ylim([0, 1])  
    plt.gca().set_position((0, 0, 1, 1))
    figure.canvas.draw()
    figure.canvas.flush_events()
    while not run_game:
        plt.pause(0.1)

    for i in range(num_balls):
        new_dp, = ax.plot(xcoord[i], ycoord[i], 'o', markersize=50, markerfacecolor='k', markeredgecolor='k')
        dp.append(new_dp)
        figure.canvas.draw()
        figure.canvas.flush_events()
        plt.pause(3)
        for t in range(dwell_steps):
            if  not run_game:
                break
            for j in range(i+1):
                x_diff = math.cos(headings[j])
                y_diff = math.sin(headings[j])
                xcoord[j] += speeds[j]*x_diff
                ycoord[j] += speeds[j]*y_diff
                if xcoord[j] < 0 or xcoord[j] > aspect_ratio:
                    xcoord[j] = clamp(xcoord[j], 0, aspect_ratio)
                    speeds[j] = min_speed + (max_speed-min_speed)*np.random.rand()
                    headings[j]  = (0.1-0.2*np.random.rand()+math.atan2(y_diff, -x_diff))%(2*math.pi)
                if ycoord[j] < 0 or ycoord[j] > 1:
                    ycoord[j] = clamp(ycoord[j], 0, 1)
                    speeds[j] = min_speed + (max_speed-min_speed)*np.random.rand()
                    headings[j] = (0.1-0.2*np.random.rand()+math.atan2(-y_diff, x_diff))%(2*math.pi)
                dp[j].set_xdata(xcoord[j])
                dp[j].set_ydata(ycoord[j])
            figure.canvas.draw()
            figure.canvas.flush_events()
            plt.pause(1/refresh_rate_hz)
        if not run_game:
            break