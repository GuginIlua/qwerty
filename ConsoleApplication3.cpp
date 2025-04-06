#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// Структура узла списка
struct Node {
    bool status;      // Состояние узла (true или false)
    Node* next;      // Указатель на следующий узел
    Node(bool stat) : status(stat), next(nullptr) {} // Конструктор для инициализации узла
};

// Структура для кольцевого списка
struct List {
    Node* head;      // Указатель на голову (первый узел) списка

    // Конструктор, который инициализирует пустой список
    List() : head(nullptr) {}

    // Функция проверки, пуст ли список
    bool is_empty() {
        return head == nullptr; // Если голова указывает на nullptr, список пуст
    }

    // Функция добавления нового узла в конец списка
    void push_back(int value) {
        Node* newNode = new Node(value); // Создаем новый узел

        if (head == nullptr) {      // Если список пуст
            head = newNode;         // Устанавливаем новый узел как голову списка
            head->next = head;      // Указываем, что следующий узел - это сам голова (кольцевой список)
        }
        else {
            Node* tail = head;
            // Находим последний узел списка
            while (tail->next != head) {
                tail = tail->next;  // Переход к следующему узлу
            }
            tail->next = newNode;   // Предыдущий последний узел указывает на новый узел
            newNode->next = head;   // Новый узел указывает на голову списка
        }
    }

    // Функция получения данных из узла по заданной позиции
    bool getDataAtPosition(int position) {
        Node* current = head;       // Начинаем с головы списка
        int count = 0;              // Счетчик для позиции

        do {
            if (count == position) {
                return current->status; // Если достигли заданной позиции, возвращаем статус узла
            }
            current = current->next;    // Переход к следующему узлу
            count++;                    // Увеличиваем счетчик
        } while (current != head);      // Зацикляем по всему списку
    }

    // Функция изменения значения статуса узла по заданной позиции
    bool changeValue(int pos, bool newStatus) {
        Node* current = head;// Начинаем с головы списка
        for (int i = 0; i <= pos; i++) {
            if (i == pos) {
                current->status = newStatus;    // Меняем статус узла на новый
                return true;                    // Возвращаем true, если изменение прошло успешно
            }
            else {
                current = current->next;        // Переход к следующему узлу
            }
        }
    }

    // Функция печати статусов всех узлов в списке
    void printList() {
        Node* current = head; // Начинаем с головы списка
        do {
            if (current->status == true) std::cout << "Heads ";     // Печатаем "Heads", если статус true
            if (current->status == false) std::cout << "Tails ";    // Печатаем "Tails", если статус false
            current = current->next; // Переход к следующему узлу
        } while (current != head); // Зацикливаем печать по всему списку

        std::cout << std::endl; // Печатаем новую строку
    }

    // Функция "подкинуть монету" для изменения статусов узлов
    void flipCoin(int move, int flip) {
        Node* current = head;               // Начинаем с головы списка
        for (int i = 0; i < flip; i++) {    // Выполняем flip раз
            for (int j = 0; j < move; j++) {
                current = current->next;    // Переходим move раз в списке
            }
            current->status = !current->status; // Инвертируем статус текущего узла
            current = current->next;            // Переход к следующему узлу
        }
    }

    // Функция проверки количества узлов со статусом true в списке
    int check() {
        int a = 0;              // Счетчик для узлов со статусом true
        Node* current = head;   // Начинаем с головы списка
        do {
            if (current->status == true) a++; // Увеличиваем счет
            current = current->next;
        } while (current != head);
        return a;
    }
};

int main() {
    // Создаем экземпляр списка для хранения монет
    List Money;
    const int maxExecutionTimeSeconds = 10;
    // Инициализация переменных
    int N, M, S, K, L, HC, a, start = 1, u, o, x;

    // Бесконечный цикл для выбора способа ввода информации
    while (1) {
        cout << "How would you like to enter information?" << endl;
        cout << "1-by yourself" << endl;
        cout << "2-from file" << endl;

        // Считываем выбор пользователя
        cin >> a;

        // Проверка на ошибку ввода
        if (std::cin.fail()) {
            std::cout << "Input error\n";
            std::cin.clear(); // Сбрасываем флаги ошибок
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
            continue; // Запрашиваем ввод заново
        }

        // Проверка корректности выбора (должен быть 1 или 2)
        if (a < 1 || a > 2) cout << "Input error" << endl; // Сообщаем об ошибке
        else break; // Выход из цикла, если ввод корректен
    }

    // Если пользователь выбрал ввод вручную
    if (a == 1) {
        while (1) {
            // Запрос числа монет с "орлом"
            std::cout << "Enter number of coins with heads:" << std::endl;
            std::cin >> N;
            // Проверка на ошибку ввода
            if (std::cin.fail()) {
                std::cout << "Input error\n";
                std::cin.clear(); // Сбрасываем флаги ошибок
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
                continue; // Запрашиваем ввод заново
            }

            // Запрос числа монет с "решкой"
            std::cout << "Enter number of coins with tails:" << std::endl;
            std::cin >> M;
            // Проверка на ошибку ввода
            if (std::cin.fail()) {
                std::cout << "Input error\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            // Запрос позиции монет для переворота
            std::cout << "Enter position of coins to be turned over:" << std::endl;
            std::cin >> S;
            // Проверка на ошибку ввода
            if (std::cin.fail()) {
                std::cout << "Input error\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            // Запрос количества шагов
            std::cout << "Enter number of steps:" << std::endl;
            std::cin >> K;
            // Проверка на ошибку ввода
            if (std::cin.fail()) {
                std::cout << "Input error\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            // Запрос конечного числа монет с "орлом"
            std::cout << "Enter final number of coins with heads:" << std::endl;
            std::cin >> L;
            // Проверка на ошибку ввода
            if (std::cin.fail()) {
                std::cout << "Input error\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            // Проверка корректности ввода (все значения должны быть больше 0)
            if (N <= 0 || M <= 0 || S <= 0 || K <= 0 || L <= 0) {
                std::cout << "Incorrect input" << std::endl;
            }
            else break; // Выход из цикла, если ввод корректен
        }
    }

    // Если пользователь выбрал ввод из файла
    if (a == 2) {
        // Открываем файл "text.txt" на чтение
        ifstream fin("text.txt");

        // Считываем значение переменной N из файла
        fin >> N;
        // Проверяем, произошла ли ошибка при вводе
        if (std::cin.fail()) {
            std::cout << "Input error\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }

        // Считываем значение переменной M из файла
        fin >> M;
        // Проверяем, произошла ли ошибка при вводе
        if (std::cin.fail()) {
            std::cout << "Input error\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }

        // Считываем значение переменной S из файла
        fin >> S;
        // Проверяем, произошла ли ошибка при вводе
        if (std::cin.fail()) {
            std::cout << "Input error\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }

        // Считываем значение переменной K из файла
        fin >> K;
        // Проверяем, произошла ли ошибка при вводе
        if (std::cin.fail()) {
            std::cout << "Input error\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }

        // Считываем значение переменной L из файла
        fin >> L;
        // Проверяем, произошла ли ошибка при вводе
        if (std::cin.fail()) {
            std::cout << "Input error\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }

        // Закрываем файл после завершения чтения данных
        fin.close();
    }
    HC = N + M;
    // Проверка возможности решения
    if (N + K < L || N - K > L) {
        std::cout << "There is no possible solution" << std::endl;
        return 0;
    }
    //Заполнение массива начальными данными
    for (int i = 0;i < N + M;i++) {
        if (i < N) Money.push_back(true);
        else Money.push_back(false);
    }
    auto startTime = std::chrono::high_resolution_clock::now();
    // Начинаем бесконечный цикл
    for (int i = 0; i > -2; i++) {
        // Генерируем случайные индексы x и y с использованием функции rand()
        // и ограничиваем их значениями от 0 до HC-1
        int x = (rand() % HC);
        int y = (rand() % HC);

        // Получаем значения из объекта Money по индексам x и y
        u = Money.getDataAtPosition(x);
        o = Money.getDataAtPosition(y);
        //cout << "Trying:" << endl;
        //Money.printList();
        // Обмениваем значения у элементов Money, расположенных по индексам x и y
        Money.changeValue(x, o);
        Money.changeValue(y, u);
        Money.flipCoin((S - 1), K);
        if (Money.check() == L) {
            // Если условие выполняется, снова вызываем flipCoin
            Money.flipCoin((S - 1), K);
            // Прерываем цикл
            break;
        }
        else {
            // Если условие не выполняется, просто вызываем flipCoin еще раз
            Money.flipCoin((S - 1), K);
        }
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        if (duration.count() >= maxExecutionTimeSeconds) {
            std::cout << "Answer wasn't found in " << maxExecutionTimeSeconds << " seconds.\n";
            std::cout << "Presumably the answer does not exist.\n";
            return 0;
        }
    }

    // Вывод списка до переворота монет
    cout << "Before flip:" << endl;
    Money.printList();

    // Вывод списка после переворота монет
    cout << "After flip:" << endl;
    Money.flipCoin((S - 1), K);
    Money.printList();

    return 0;
}