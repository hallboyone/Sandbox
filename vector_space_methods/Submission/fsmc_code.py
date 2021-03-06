import numpy as np
from scipy.linalg import null_space
import matplotlib
import matplotlib.pyplot as plt

# General function to expected hitting time for Exercise 2.1
def compute_Phi_ET(P, ns=100):
    '''
    Arguments:
        P {numpy.array} -- n x n, transition matrix of the Markov chain
        ns {int} -- largest step to consider

    Returns:
        Phi_list {numpy.array} -- (ns + 1) x n x n, the Phi matrix for time 0, 1, ...,ns
        ET {numpy.array} -- n x n, expected hitting time approximated by ns steps ns
    '''
    
    #The size of the propability matrix
    n = P.shape[1]

    #Initialize all the vales
    Delta = np.identity(n)
    Phi_list = np.empty([ns+1, n, n])
    ET = np.zeros([n, n])
    ET = Delta
    Phi_list[0] = Delta

    #Solve over the given timeframe
    for i in range(0,ns):
        Phi_list[i+1] = Delta + np.multiply((1 - Delta), P.dot(Phi_list[i])) 
        ET = ET + (i+1)*(np.subtract(Phi_list[i+1],Phi_list[i]))
        pass
    
    return Phi_list, ET


# General function to simulate hitting time for Exercise 2.1
def simulate_hitting_time(P, states, nr):
    '''
    Arguments:
        P {numpy.array} -- n x n, transition matrix of the Markov chain
        states {list[int]} -- the list [start state, end state], index starts from 0
        nr {int} -- largest step to consider
    
    Returns:
        T {list[int]} -- a size nr list contains the hitting time of all realizations
    '''
    #Build the empty list
    T = np.empty(nr)
    
    for i in range(0, nr):
        #Initalize the trial
        step_counter = 0
        cur_state = states[0]
        
        #While we are 
        while (cur_state != states[1]):
            roll = np.random.random_sample()
            
            #Look for the element in the col of the current state for the roll
            col = 0
            while (roll > P[cur_state, col]):
                roll -= P[cur_state, col]
                col += 1
                pass
            
            cur_state = col
            
            step_counter += 1
            if (step_counter >= nr):
                break
            pass
        T[i] = step_counter
        pass
    
    return T



# General function to approximate the stationary distribution of a Markov chain for Exercise 2.4
def stationary_distribution(P):
    '''
    Arguments:
        P {numpy.array} -- n x n, transition matrix of the Markov chain
    
    Returns:
        pi {numpy.array} -- length n, stationary distribution of the Markov chain
    '''
    # Add code here: Think of pi as column vector, solve linear equations:
    #     P^T pi = pi
    #     sum(pi) = 1
    n = P.shape[1]
    P = np.eye(n)-P
    P = np.transpose(P)
    pi = null_space(P)
    pi = pi/np.sum(pi)
    return pi




