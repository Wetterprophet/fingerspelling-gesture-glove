import numpy as np
import arduino_python.measureData as mD
import arduino_python.DBA_multivariate as DBA
from scipy import stats
import matplotlib.pyplot as plt



def main(file_name, pins, smoothing):

    """
    Returns dictionary of centroids of training data by class labels
    Using multivariate DBA
    """
    #for easier testing, just read in saved data
    training_data, target_values = mD.read_data(file_name)
    unique_classes = np.unique(target_values)

    #sort data by class label
    sorted_data = sort_data(training_data, target_values, unique_classes)

    #order data to shape (dimension, length) & normalize & smooth out
    dim_data = {class_label : np.array([normalize(order_by_dim(series, smoothing)) for series in sorted_data[class_label]])
                                for class_label in unique_classes}


    centroids = compute_centroids(dim_data)

    #plotting for visualization and improvement purposes
    plot_centroids(centroids, unique_classes, pins)

    return centroids, unique_classes



def normalize(series):

    """
    Normalize each dimension of a series instance individually
    Using z transformation
    """
    #normalize dimension with z transformation
    #or return array of zeros if standard deviation is 0
    norm_series = np.array([stats.zscore(dimension) if np.std(dimension) != 0 else np.zeros(len(dimension)) for dimension in series])

    return norm_series


def order_by_dim(series, smoothing):

    """
    Reorder a series to an array of values per dimension
    Needed for DBA and DTW on Arduino

    Smoothing is applied here
    """

    ordered_series = []
    for i in range(len(series[0])):
        ordered_series.append([pin[i] if pin[i] > smoothing else 0 for pin in series])

    return np.array(ordered_series)

def sort_data(training_data, target_values, unique_classes):

    """
    Returns a dictionary with instances by class labels
    """

    sorted_data = {label : training_data[target_values==label] for label in unique_classes }

    return sorted_data


def compute_centroids(sorted_data):

    """
    Returns a dictionary with centroid per class
    Computed with multivariate DBA
    """

    all_centroids = {}
    for label in sorted_data.keys():
        centroid = DBA.performDBA(sorted_data[label])

        #round down to .2 float, multiply with 100
        #and convert to int for saving memory on Arduino
        all_centroids[label] = (np.around(centroid, 2) * 100).astype(int)

    return all_centroids

def plot_centroids(centroids, unique_classes, pins):

    """
    Plots centroid of each dimension (input pin) per class
    Returns none
    """

    n_dims = len(pins)
    num_plots = len(unique_classes)

    fig = plt.figure()
    for num, label in enumerate(centroids.keys()):
        ax = fig.add_subplot(num_plots, 1, num+1)
        for dim in range(0,n_dims):
            ax.plot(range(0,centroids[label].shape[1]), centroids[label][dim], label = pins[dim])
        ax.set_title(label)
    plt.legend(loc = 'best')
    plt.show()

    return None

#function for testing purposes
#and script creation
def c_array(centroids):

    """
    Returns new dictionary with a ready-to-copy string representation of data for use as array in C
    """
    c_centroids = {}
    for label in centroids.keys():
        c_centroid = str(centroids[label].tolist()).replace('[', '{')
        c_centroid = c_centroid.replace(']', '}')
        c_centroids[label] = c_centroid

    return c_centroids



#default setting if called on its own
if __name__ == '__main__':
    main('latext.txt', pins = ['A0', 'A2'], smoothing = 500)
