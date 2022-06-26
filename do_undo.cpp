#include <iostream>
#include "do_undo.h"

Stack::Stack()
{
    Size = 0;
    head = nullptr;
}

Stack::~Stack()
{
    clear();
}

void Stack::clear()
{
    int size = GetSize();
    for (int i = 0; i < size; i++)
    {
        pop_last();
    }
}

void Stack::push_back(string text)
{
    if (head == nullptr)
    {
        head = new Node(text);
    }
    else
    {
        Node* current = this->head;
        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node(text);
    }
    Size++;
}

string Stack::pop_last()
{
    int size = GetSize();
    if (size == 1) {
        Node* temp = head;
        string data = head->data;
        head = nullptr;
        delete temp;
        Size--;
        return data;
    }
    else
    {
        Node* previous = this->head;
        for (int i = 0; i < size - 2; i++)
        {
            previous = previous->pNext;
        }

        Node* pTemp = previous->pNext;
        previous->pNext = nullptr;
        string data = pTemp->data;
        delete pTemp;
        Size--;

        return data;
    }
}

string& Stack::operator[](const int index)
{
    int counter = 0;
    Node* current = this->head;

    while (current->pNext != nullptr)
    {
        if (index == counter)
            return current->data;
        current = current->pNext;
        counter++;
    }
    return current->data;
}

int main()
{
    setlocale(LC_ALL, "ru");
    Stack undo;
    Stack redo;
    cout << "Write an stroke that you would like to work with: ";
    string stroke;
    getline(cin, stroke);
    cout << "ADD (stroke) -  add stroke" << endl;
    cout << "DEL (num) - del 'num' amount of symbols" << endl;
    cout << "UNDO - return to previous result" << endl;
    cout << "REDO - call off previous UNDO" << endl;
    cout << "STOP - to stop the programm" << endl;
    while (true)
    {
        cout << "OK, you're working with: \"" + stroke + "\"" << endl;
        cout << "What's your next step?" << endl;
        string command;
        getline(cin, command);
        
        if (command == "STOP") {
            cout << "Programm has been stopped manually" << endl;
            cout << "Your final stroke is: " + stroke << endl;
            break;
        }

        if (command == "UNDO") {
            if (undo.GetSize() > 0) {
                redo.push_back(stroke);
                stroke = undo.pop_last();
            }
            else {
                cout << "Wrong syntax or there is nothing to UNDO" << endl;
            }
        }

        if (command == "REDO") {
            if (redo.GetSize() > 0) {
                undo.push_back(stroke);
                stroke = redo.pop_last();
            }
            else {
                cout << "Wrong syntax or last step wasn't \"UNDO\"" << endl;
            }
        }
        else {
            auto space = command.find(" ");
            string com = command.substr(0, space);

            if (com == "ADD") {
                string str = command.substr(space + 1);

                undo.push_back(stroke);
                stroke = stroke + str;

                if (redo.GetSize() > 0)   /// Чистим stack Redo, если в нем что-либо находится
                    redo.clear();
            }

            if (com == "DEL") {
                int num = stoi(command.substr(space + 1));

                undo.push_back(stroke);
                int len = stroke.length();
                stroke = stroke.erase(len - num);

                if (redo.GetSize() > 0)   /// Чистим stack Redo, если в нем что-либо находится
                    redo.clear();
            }
        }
        
    }
}
