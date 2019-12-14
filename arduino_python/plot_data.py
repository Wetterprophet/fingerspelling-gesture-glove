import matplotlib.pyplot as plt
import numpy as np

def main():

    """
    Plotting data copied from Arduino Serial monitor
    Auxiliary file, for improvement purposes
    """
    #fill in manually!
    pins = ['A0', 'A2', 'A4', 'A7']
    n_dims = len(pins)
    steps = 80
    data = np.array([[-56, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -56, -42, 5, 4, 6, 10, 40, 18, 65, 16, 24, 21, 83, 41, 77, 79, 81, 85, 50, 1, -5, -62, -64, -62, 49, -38, -37, -36, 194, 213, 213, 212, 161, 212, 206, 212, 211, 213, 210, 208, 263, 227, 231, -56, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62, -62], [-36, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -31, -34, -34, -34, -34, -33, -34, -34, -34, -34, -34, -34, 303, 288, 304, 295, 301, 297, 179, 296, -35, -34, -31, -34, -35, -34, -34, -34, -34, -34, -34, -34, -34, -34, -32, -34, -34, -34, -34, -34, -37, -34, -34, -37, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34], [-15, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 38, 95, -10, -10, -10, -8, 150, -7, 149, -10, 93, 91, 90, -16, -10, -10, -10, -10, -7, -10, -12, -10, -5, -10, -14, -10, -10, -10, -8, -10, -10, -10, -5, -10, -7, -10, -10, -10, -10, -10, -17, -10, -10, -22, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10], [-25, -33, -33, -33, -33, -33, -33, -33, -33, 2, -33, 190, 354, 350, 192, 191, 191, 190, 189, 188, 189, 189, -37, -33, -33, -33, -33, -35, -33, -35, -33, -33, -33, -33, -33, -35, -33, -33, -33, -33, -35, -28, -30, -33, -37, -33, -31, -33, -33, -33, -35, -33, -33, -33, -37, -33, -35, -33, -33, -33, -33, -33, -27, -33, -33, -35, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33]])

    #fig = plt.figure()

    for dim in range(0,n_dims):
        plt.plot(range(0,steps), data[dim], label = pins[dim])
    plt.legend(loc = 'best')
    plt.show()






if __name__ == '__main__':
    main()
