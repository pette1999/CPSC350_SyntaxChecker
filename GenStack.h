 #include <iostream>

using namespace std;

//template class, can handle different types of parameters
template <class E>
class GenStack
{
public:
    GenStack();            //constructor
    GenStack(int maxSize); //overloaded constructor
    ~GenStack();           //destructor

    void push(E d); //add an element to the stack
    E pop();
    E peek(); //AKA top()

    bool isFull();  //check if the stack is full
    bool isEmpty(); //check if the stack is empty
    int getSize();

    int size;
    int top;

    char *myArray; //pointer / dinamic memory allocation
    char *temp;
};

//default constrctor
template <class E>
GenStack<E>::GenStack()
{
    myArray = new E[128]; //create an array with length 128
    size = 128;
    top = -1; //top position in the stack
}

//overloaded constructor
template <class E>
GenStack<E>::GenStack(int maxSize)
{
    myArray = new E[maxSize]; //create an array with length maxSize
    size = maxSize;
    top = -1;
}

//destructor
template <class E>
GenStack<E>::~GenStack()
{
    delete myArray; //move the Array to the "trashcan"
}

//add elements to the stack
template <class E>
void GenStack<E>::push(E d)
{
    //need to check error/boundary check
    if (isFull())
    {
        temp = new char[size]; //temp array
        for (int i = 0; i < size; ++i)
        {
            temp[i] = myArray[i]; //copy every elements in the old array over
        }
        delete myArray;               //delete the odl one
        myArray = new char[size * 2]; //set up a new array with double space but same name
        size *= 2;
        for (int i = 0; i < size; ++i)
        {
            myArray[i] = temp[i]; //put elements back in
        }
        delete temp; //delete temp array
    }
    myArray[++top] = d;
}

template <class E>
E GenStack<E>::pop()
{
    if (isEmpty())
    {
        cout << "The stack is empty!!!" << endl;
        exit(0);
    }
    //error checking, make sure its not empty
    return myArray[top--];
}

template <class E>
E GenStack<E>::peek()
{
    //check if empty
    if (isEmpty())
    {
        cout << "The stack is empty!!!" << endl;
        exit(0);
    }
    return myArray[top];
}

template <class E>
bool GenStack<E>::isFull()
{
    return (top == size - 1);
}

template <class E>
bool GenStack<E>::isEmpty()
{
    return (top == -1);
}

template <class E>
int GenStack<E>::getSize()
{
    return size;
}