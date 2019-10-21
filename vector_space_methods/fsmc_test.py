# Test script for fsmc_code.py
import numpy as np
from fsmc_code import compute_Phi_ET, simulate_hitting_time, stationary_distribution

#
# Desired output of this script
# -----------------------------
#
# Markov transition matrix:
#  [[0.5 0.5 0. ]
#  [0.5 0.  0.5]
#  [0.  0.  1. ]] 
#
# Expected hitting times E[T_ij]:
#  [[0.         2.         5.98897748]
#  [0.5        0.         3.99318771]
#  [0.         0.         0.        ]] 
#
# Pr(T_ij <= 4):
#  [[1.    0.875 0.375]
#  [0.5   1.    0.625]
#  [0.    0.    1.   ]] 
#
# Pr(T_ij <= 8):
#  [[1.        0.9921875 0.734375 ]
#  [0.5       1.        0.8359375]
#  [0.        0.        1.       ]] 
#
# E[T_1j] Sim:
#  [0.    2.026 6.018] 
#
# Markov transition matrix:
#  [[0.7 0.2 0.1]
#  [0.2 0.3 0.5]
#  [0.1 0.2 0.7]] 
#
# Stationary distribution:
#  [0.30555556 0.22222222 0.47222222] 


# Test code for expected hitting time
P = np.array([[0.5, 0.5, 0], [0.5, 0, 0.5], [0, 0, 1]])  
Phi_list, ET = compute_Phi_ET(P, 40)
print("Markov transition matrix:\n",P,"\n")
print("Expected hitting times E[T_ij]:\n",ET,"\n")
print("Pr(T_ij <= 4):\n",Phi_list[3],"\n")
print("Pr(T_ij <= 8):\n",Phi_list[7],"\n")

# Test code for simulating hitting time
ETsim = np.zeros([3])
for j in range(3):
    T = simulate_hitting_time(P, [0, j], 500)
    ETsim[j] = np.mean(T)
print("E[T_1j] Sim:\n",ETsim,"\n")

# Test code for computing stationary distribution
P = np.array([[0.7, 0.2, 0.1], [0.2, 0.3, 0.5], [0.1, 0.2, 0.7]])
pi = stationary_distribution(P)
print("Markov transition matrix:\n",P,"\n")
print("Stationary distribution:\n",pi,"\n")
