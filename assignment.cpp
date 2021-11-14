#include <iostream>
#include <cmath>

using namespace std;

class Stack
{
    /*
    A stack class implemented using dynamic string array
    */
private:
    int size = 2;
    string *array = new string[size];
    int length = 0;

    bool isEmpty()
    {
        return length == 0;
    }

    bool isFull()
    {
        return length == size - 1;
    }

    string *increaseSize()
    {
        // create a new array
        string *newArray = new string[size];
        // copy the data from the old array to the new array
        for (int i = 0; i <= length; i++)
        {
            newArray[i] = *(array + i);
        }
        return newArray;
    }

    void growArray()
    {
        size *= 2;
        array = increaseSize();
    }

public:
    int len()
    {
        return length;
    }
    string peak()
    {
        if (isEmpty())
            return "";

        return array[length];
    }

    void push(string element)
    {
        if (isFull())
            growArray();
        length++;
        array[length] = element;
    }

    void push(char element)
    {
        if (isFull())
            growArray();
        length++;
        string temp = "";
        temp += element;
        array[length] = temp;
    }

    void pop()
    {
        if (!isEmpty())
        {
            length--;
        }
    }
};