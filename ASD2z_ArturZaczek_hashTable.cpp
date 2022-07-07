#include <iostream>

using namespace std;

struct Pair {
    long key = -1;
    string value;
};

void updateTable(Pair *dynArray, int size);

int hashCode(long input, int size) {
    int result = static_cast<int>(input) % size;
    return result;
}

int nextHashCode(int currentHashCode, int size) {
    if (currentHashCode == size - 1) {
        return 0;
    }
    return ++currentHashCode;
}

void addCommand(Pair *dynArray, int size) {
    long key;
    string value;
    cin >> key;
    cin >> value;
    int index = hashCode(key, size);
    if (dynArray[index].key == -1 || dynArray[index].key == key) {
        dynArray[index].key = key;
        dynArray[index].value = value;
    } else {
        for (int i = 0; i < size; i++) {
            index = nextHashCode(index, size);
            if (dynArray[index].key == -1 || dynArray[index].key == key) {
                dynArray[index].key = key;
                dynArray[index].value = value;
                break;
            }
        }
    }
}

void deleteCommand(Pair *dynArray, int size) {
    long key;
    cin >> key;
    int index = hashCode(key, size);
    if (dynArray[index].key == key) {
        dynArray[index].key = -1;
    } else {
        for (int i = 0; i < size; i++) {
            index = nextHashCode(index, size);
            if (dynArray[index].key == key) {
                dynArray[index].key = -1;
                break;
            }
        }
    }
    updateTable(dynArray, size);
}

int sizeCommand() {
    int size;
    cin >> size;
    return size;
}

void printCommand(Pair *dynArray, int size) {
    cout << endl;
    for (int i = 0; i < size; i++) {
        if (dynArray[i].key != -1) {
            cout << i << " " << dynArray[i].key << " " << dynArray[i].value << endl;
        }
    }
}

void updateTable(Pair *dynArray, int size) {
    for (int i = 0; i < size; i++) {
        if (dynArray[i].key != -1) {
            long tempKey = dynArray[i].key;
            string tempValue = dynArray[i].value;
            int index = hashCode(tempKey, size);
            if (index == i) {
                continue;
            }
            if (dynArray[index].key == -1) {
                dynArray[index].key = dynArray[i].key;
                dynArray[index].value = dynArray[i].value;
                dynArray[i].key = -1;
            } else {
                for (int k = 0; k < size; k++) {
                    if(index == i){
                        continue;
                    }
                    index = nextHashCode(index, size);
                    if (dynArray[index].key == -1) {
                        dynArray[index].key = tempKey;
                        dynArray[index].value = tempValue;
                        dynArray[i].key = -1;
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    int testCount, arraySize;
    cin >> testCount;
    cout << endl;
    for (int i = 0; i < testCount; i++) {
        string input;
        Pair *dynArray;
        while (input != "stop") {
            cin >> input;
            if (input == "size") {
                arraySize = sizeCommand();
                dynArray = new(nothrow) Pair[arraySize];
            } else if (input == "add") {
                addCommand(dynArray, arraySize);
            } else if (input == "delete") {
                deleteCommand(dynArray, arraySize);
            } else if (input == "print") {
                printCommand(dynArray, arraySize);
            } else {
                break;
            }
        }
        delete[] dynArray;
    }
    return 0;
}