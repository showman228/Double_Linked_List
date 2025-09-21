// данный файл нужен для тестирования кода
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class List {
private:
    template <typename T2>
    class Node {
    public:
        T2 data;
        Node *next;
        Node *prev;

        Node(T2 data = T2(), Node *next = nullptr, Node *prev = nullptr) {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };
    private:
        int SIZE;
        Node<T> *head;
        Node<T> *tail;

public:
    List();
    ~List();
public:

    void push_back(T data);
    void pop_front();
    void push_front(T data);
    void pop_back();
    void clear_list();
    void ShowList();
    void insert(int index, T data);
    void remove(int index);

public:
    T & operator [] (const int index);
    int GetSize() const;
};

template<typename T>
List<T>::List() : SIZE(0), head(nullptr), tail(nullptr) { }

template<typename T>
List<T>::~List() {
    clear_list();
}

template<typename T>
int List<T>::GetSize() const {
    return SIZE;
}

// вставляем в конец
template<typename T>
void List<T>::push_back(T data) {
    Node<T>* newNode = new Node<T> (data);
    if (head == nullptr) {
        this->head = this->tail =  newNode;

    }
    else {
        newNode->prev = this->tail;
        tail->next = newNode;
        tail = newNode;
    }
    SIZE++;
}

// вставляем в начало
template<typename T>
void List<T>::push_front(T data) {
    Node<T>* newNode = new Node<T> (data);
    if (head == nullptr) {
        this->head = this->tail = newNode;
    }
    else { newNode->next = this->head; this->head->prev = newNode; this->head = newNode; }
    SIZE++;
}

// удаляем первый элемент
template<typename T>
void List<T>::pop_front() {
    if (head == nullptr) { return; }

    Node<T> *temp = this->head;
    head = head->next;

    if (head != nullptr) { head->prev = nullptr; }
    else { tail = nullptr; }

    delete temp;

    SIZE--;
}

// удаляем последний элемент
template<typename T>
void List<T>::pop_back() {
    if (tail == nullptr) { return; }

    Node<T> *temp = this->tail;
    tail = tail->prev;

    if (tail != nullptr) { tail->next = nullptr; }
    else { head = nullptr; }

    delete temp;

    SIZE--;
}

// перегрузка оператора []
template<typename T>
T & List<T>::operator [] (const int index) {

    if (index >= SIZE || index < 0) { throw out_of_range("index is out of range"); }

    if (index < ((SIZE / 2) + 1)) {
        int counter = 0;
        Node<T> *curr = head;
        while (curr != nullptr) {
            if (counter == index) {
                return curr->data;
            }
            curr = curr->next;
            counter++;
        }
    }

    else {
        int counter = SIZE - 1;
        Node<T> *curr = tail;
        while (curr != nullptr) {
            if (counter == index) {
                return curr->data;
            }
            curr = curr->prev;
            counter--;
        }
    }
}

// вставка по индексу
template<typename T>
void List<T>::insert(int index, T data) {

    Node<T> *curr;

    if (index == 0) { push_front(data); }

    else if (index == SIZE) { push_back(data); }

    else if ( 0 < index && index < SIZE) {

        if (index < ((SIZE / 2) + 1)) {

            Node<T> *newNode = new Node<T> (data);

            curr = this->head;
            int counter = 0;
            while (curr != nullptr) {
                if (counter == index) {

                    auto *pprev = curr->prev;

                    pprev->next = newNode;
                    newNode->prev = pprev;

                    newNode->next = curr;
                    curr->prev = newNode;

                    SIZE++;
                    return;
                }
                counter++;
                curr = curr->next;

            }
        }

        else {

            Node<T> *newNode = new Node<T> (data);

            int counter = (SIZE - 1);
            curr = this->tail;
            while (curr != nullptr) {
                if (counter == index) {

                    auto *pprev = curr->prev;

                    pprev->next = newNode;
                    newNode->prev = pprev;

                    newNode->next = curr;
                    curr->prev = newNode;

                    SIZE++;
                    return;
                }
                counter--;
                curr = curr->prev;
            }
        }

    }
    else {
        throw out_of_range("index is out of range");
    }

}

template<typename T>
void List<T>::remove(int index) {

    Node<T> *curr;

    if (index < 0 || index >= SIZE) {
        return;
    }

    if (index == 0) { pop_front(); }

    else if (index == (SIZE - 1)) { pop_back(); }

    else if (0 < index && index < SIZE) {

        if (index < ((SIZE / 2) + 1)) {

            curr = this->head;
            int counter = 0;

            while (curr != nullptr) {
                if (counter == index) {

                    auto *pprev = curr->prev;
                    auto *pnext = curr->next;

                    if (pprev != nullptr) pprev->next = pnext;
                    if (pnext != nullptr) pnext->prev = pprev;

                    delete curr;
                    SIZE--;
                    return;
                }
                counter++;
                curr = curr->next;
            }
        }

        else {
            curr = this->tail;
            int counter = (SIZE - 1);

            while (curr != nullptr) {
                if (counter == index) {

                    auto *pprev = curr->prev;
                    auto *pnext = curr->next;

                    if (pprev != nullptr) pprev->next = pnext;
                    if (pnext != nullptr) pnext->prev = pprev;

                    delete curr;
                    SIZE--;
                    return;
                }

                counter--;
                curr = curr->prev;
            }
        }
    }

    else {
        throw out_of_range("index is out of range");
    }
}



//Чистит лист
template<typename T>
void List<T>::clear_list() {
    while (head != nullptr) {
        pop_front();
    }
}

// вывод список
template<typename T>
void List<T>::ShowList() {

    if (SIZE == 0) { cout << "Список пуст" << endl; }
    else if (SIZE == 1) { cout << head->data << endl; }
    else {Node<T> *curr = this->head;
        cout << curr->data;
        curr = curr->next;
        while (curr != nullptr) {
            cout << "->";
            cout << curr->data;
            curr = curr->next;
        }
        cout << endl;}
}

// пример работы кода
int main() {
    List<int> tasks;
    for (int i = 0; i < 10; i++) {
        tasks.push_back(i);
    }

    tasks.ShowList();
    cout << "Кол-во элементов: " << tasks.GetSize() << endl;

    tasks.insert(8, 52);
    tasks.insert(2, 42);

    tasks.ShowList();

    tasks.remove(2);
    tasks.remove(8);

    tasks.ShowList();

    return 0;
}