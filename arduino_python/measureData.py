import serial #Serial communication
import time #delays
import ast #for file reading
import numpy as np
import sys #directories
import subprocess #communication with terminal
import os

def main(file_name, port, board, pins):

    """
    Creates measureData.ino with specified input pins
    Uploads measureData.ino to Arduino
    Measures data (follow terminal instructions),
    saves it in a txt file

    """

    #write script to be uploaded to Arduino depending on user input
    create_measure_script(pins)

    #compile & upload measuring sketch to board
    try:
        subprocess.run(["arduino-cli", "compile", "--fqbn", board, "arduino_scripts/measureData"], check=True)
    except subprocess.CalledProcessError:
        print("Can't compile measureData.ino")

    try:
        subprocess.run(["arduino-cli", "upload", "-p", port, "--fqbn", board, "arduino_scripts/measureData"], check=True)
    except subprocess.CalledProcessError:
        print("Can't upload sketch")

    #measure data
    training_data, target_values = measure_training_data(port)

    #if something went wrong, print error and abort
    if (training_data, target_values) == (None, None):
        print("Training failed. Check the connection of your Arduino.")
        return False

    else:
        #pre-process data for Python use, mainly converting from string to list of ints
        training_data = process_data(training_data)

        #write txt file with training data and target values for potential reuse
        create_data_file(training_data, target_values, file_name)

        #training_data, target_values = read_data(file_name)

        return True

def create_measure_script(pins):

    """
    Writes the measurement ino script
    Saves it in the arduino_script folder under the measureData folder

    Input: Input pins as list (as passed as argument from user)
    measure_1.txt should be in same directory
    Returns nothing
    """

    os.chdir('arduino_scripts')

    #read in measurement sceleton
    with open('measure_1.txt') as m_1:
        measure_1 = m_1.read()

    os.chdir('measureData')

    #write out variables in ino file
    with open('measureData.ino', 'w') as ino:

        ino.write("""const int size_inPins = {};\n""".format(len(pins)))
        ino.write("""int inPins[size_inPins] = {""")
        ino.write(str(pins).replace("'", "")[1:-1])
        ino.write('};\n')

        #add sceleton
        ino.write(measure_1)

    os.chdir('..')
    os.chdir('..')

    return None


def read_data(file_name):

    """
    Reads in and returns training data and target values from file created by function create_data_file
    Both are returned as arrays
    """

    with open(file_name) as file:

        all_data = file.read()
        training_data, target_values = all_data.split('\n')
        training_data = ast.literal_eval(training_data)
        target_values = ast.literal_eval(target_values)

    return np.array(training_data), np.array(target_values)

def create_data_file(training_data, target_values, file_name):

    """
    Creates a text file with training data and target values for further usage
    Training data and target values are seperated by a new line
    """

    with open(file_name, 'w') as file:

        file.write('{}'.format(training_data))
        file.write('\n')
        file.write('{}'.format(target_values))

    return None

def process_data(data):

    """
    Transforms training data to a list of instances
    which consists of a list of time steps
    that contain the measures of the individual pins

    The dimension is number instances x number of measured time steps x number of input pins
    """

    processed_data = [[[int(pin) for pin in step.split(',')] for step in series[:-1].split(';')] for series in data]

    return processed_data


def measure_training_data(port):

    """
    Measures training data with connected Arduino board

    Input pins are specified in Arduino sketch

    Returns a list of training data in raw form (as string)
    and list of target values/classes (as string)
    """
    print("Wait for port")
    time.sleep(5)

    try:
        arduino = serial.Serial(baudrate=9600, timeout=5, port = port)
        if not arduino.is_open:
            arduino.open()

        print("Wait for connection")
        time.sleep(2)

        measure = True #variable for loop control
        target_values = [] #initialize array with classes
        all_sensor_data = [] #initialize list to store measurements

        while measure:

            #get current class or command to quit
            current_input = input("Class or 'quit': ")

            #check for quit command
            if current_input == 'quit':
                measure = False
            else:
                #measure if valid class is given
                try:
                    assert(len(current_input) == 1)
                    current_class = int(current_input)
                    check_class = False

                    #save class
                    target_values.append(current_class)

                    print("Press button to start measuring")

                    read_in = True
                    while read_in:
                        #check if data is available
                        if arduino.inWaiting()>0:
                            sensor_data = arduino.readline().decode('utf-8')

                            #save sensor data
                            all_sensor_data.append(sensor_data)
                            print(sensor_data)

                            read_in = False

                except:
                    print("Invalid input (class should be a one digit integer)")


    except serial.serialutil.SerialException:
        print("Can't open port. Is your Arduino connected via USB? Serial monitor closed?")
        return None, None

    return all_sensor_data, target_values


#default settings if called on its own
if __name__ == '__main__':
    main(file_name='trainingData.txt', board = 'arduino:mbed:nano33ble', port="COM22",
                pins=['A0', 'A1', 'A2', 'A3'])
