import numpy as np
import computeCentroid as cc
import fastdtw #install package
from scipy.spatial.distance import euclidean #for distance metric used by fastdtw
import arduino_python.measureData as mD


def main():

    """
    Testing Nearest Centroid Classification with DTW as distance measure
    Computes centroids of training data using computeCentroid.py
    Reads in a file of test data with training instances and class labels and reports outcome of classification
    """

    centroids = cc.main()

    #convert to c array representation
    #c_centroids = c_array(centroids)
    #print(c_centroids['1'])

    test_data, target_values = mD.read_data('testData_small.txt') #to be filled in

    for i, instance in enumerate(test_data):

        distances, class_label = NCC(centroids, instance)
        print(distances)
        if class_label == target_values[i]:
            print("Success")
        else:
            print("Fail")


def NCC(centroids, instance):

    """
    Returns dictionary with distances between instance and centroid per class
    and class label of minimal distance
    using fastdtw
    """

    distances = {label : fastdtw.fastdtw(instance, centroids[label])[0]
                                for label in centroids.keys()}
    class_label = min(distances, key=distances.get)

    return distances, class_label






if __name__ == '__main__':
    main()
