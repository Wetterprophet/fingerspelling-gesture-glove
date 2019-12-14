import numpy as np
import argparse
import arduino_python.measureData as measure
import arduino_python.computeCentroid as centroid
import os
import subprocess
import time



def main():

    """
    Use this with command line arguments to train your Arduino
    Make sure the following are installed/downloaded:
    arduino-cli
    pyserial

    If measuring:
    Measures for 2 seconds with 25 ms between measurements

    Automatically uploads measurement and classification script to board
    """


    #parse arguments (measuring data or not, name of text file, input pins, smoothing out, arduino board, usb port)
    parser = argparse.ArgumentParser(description = "Train your Arduino.")
    parser.add_argument('-m', dest='measuring', default='True', nargs='?',
                            help = 'measuring new data True/False (default: True)')
    parser.add_argument('-n', dest = 'file_name', default = 'trainingData.txt', nargs='?',
                            help = 'name of .txt file for saving or reading data (default: trainingData.txt)')
    parser.add_argument('-p', dest='pins', nargs='+', default=['A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7'],
                            help='input pins (default: A1 A2 A3 A4 A5 A6 A7)')
    parser.add_argument('-s', dest='smoothing', default=0, nargs='?',
                            help='maximum value to smooth out to zero in measured data (default: 0)')
    parser.add_argument('-b', dest='board', default="arduino:mbed:nano33ble", nargs='?',
                            help='arduino board (default: arduino:mbed:nano33ble)')
    parser.add_argument('-usb', dest='port', default="COM22", nargs='?',
                            help='usb port connected with board (default: COM22')


    parse_args = parser.parse_args()
    file_name = parse_args.file_name
    #make sure it will be a text file
    if file_name[-4:] != '.txt':
        file_name = file_name + '.txt'


    pins = parse_args.pins
    board = parse_args.board
    port = parse_args.port
    smoothing = int(parse_args.smoothing)

    #potentially measure new data, or skip
    measuring = parse_args.measuring
    if measuring.lower() != 'false':
        measure_success = measure.main(file_name, port, board, pins)
    else:
        measure_success = True

    if measure_success is True:


        #compute centroids
        ordered_centroids, class_labels = centroid.main(file_name, pins, smoothing)


        #write ino script
        create_classification_script(ordered_centroids, list(class_labels), pins, smoothing)

        #automatically upload classification script to board
        try:
            subprocess.run(["arduino-cli", "compile", "--fqbn", board, "arduino_scripts/predict"], check=True)
        except subprocess.CalledProcessError:
            print("Can't compile predict file")

        try:
            subprocess.run(["arduino-cli", "upload", "-p", port, "--fqbn", board, "arduino_scripts/predict"], check=True)
            print("Wait for port")
            time.sleep(3)
            print("Done")
        except subprocess.CalledProcessError:
            print("Can't upload sketch")




    return None


def create_classification_script(centroids, class_labels, pins, smoothing, duration=2000, pause=25):

    """
    Writes the classification Arduino script
    Saves it in the arduino_script folder under the predict folder (dtw, normalization is already included)

    Input: centroid dictionary returned by the ordered_centroid method, list of unique class labels and list of input pins
    predict_1.txt, predict_2.txt, predict_3.txt should be in same directory
    Returns nothing
    """

    #change directories to save script in appropriate place
    os.chdir('arduino_scripts')

    #read in ino script sceletons
    with open('predict_1.txt') as p_1:
        predict_1 = p_1.read()

    with open('predict_2.txt') as p_2:
        predict_2 = p_2.read()

    with open('predict_3.txt') as p_3:
        predict_3 = p_3.read()

    #some working variables
    centroids = centroid.c_array(centroids)
    num_classes = len(class_labels)
    steps = int(duration/pause)

    dist_names = ['distance_' + str(label) for label in class_labels]
    cent_names = ['centroid_' + str(label) for label in class_labels]

    os.chdir('predict')

    with open('predict.ino', 'w') as ino:

        ino.write('boolean measure = false;\n')
        ino.write('const short duration = {};\nconst short pause = {};\n'.format(duration, pause))
        ino.write('const short steps = {};\n'.format(steps))
        ino.write('const short smoothing = {};\n\n'.format(smoothing))


        ino.write("""const short size_inPins = {};\n""".format(len(pins)))
        ino.write("""short inPins[size_inPins] = {""")
        ino.write(str(pins).replace("'", "")[1:-1])
        ino.write('};\n')

        ino.write(r"""const short n_classes = """)
        ino.write(str(num_classes))
        ino.write(';\n')

        ino.write('const short target[n_classes] = {')
        ino.write(str(class_labels)[1:-1])
        ino.write('};\n')

        for cent in cent_names:
            ino.write('const short {}[][steps] = {};\n'.format(cent, centroids[int(cent[-1])]))

        ino.write(predict_1)

        for dist in dist_names:
            ino.write('\t\tint {} = 0;\n'.format(dist))

        ino.write(predict_2)

        for dist, cent in zip(dist_names, cent_names):
            ino.write('\t\t{} = {} + dtw((short*)sensor_data_dim, (short*){}[i], steps, steps, 0.25);\n'.format(dist, dist, cent))

        ino.write('\n\t\t//get class during last iteration\n\n\t\t')
        ino.write(r"""if(i==size_inPins-1){""")
        ino.write('\n\n\t\t')


        #for debugging, delete later
        for dist in dist_names:
            ino.write('Serial.println({});'.format(dist))
            ino.write('\n\t\t')

        ino.write('\t\tint all_distances[n_classes] = {')
        ino.write(str(dist_names)[1:-1].replace("'", ""))
        ino.write('};\n')

        ino.write(predict_3)

    #switch back to default directory
    os.chdir('..')
    os.chdir('..')

    return None


if __name__ == '__main__':
    main()
