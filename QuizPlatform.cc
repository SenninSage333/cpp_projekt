#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <ctime>

using namespace std;

vector<int> randoms(int s, int numOfQuestions)
{
    vector<int> numbers;
    int el;
    while (numbers.size() < s)
    {
        el = rand() % numOfQuestions;
        while (count(numbers.begin(), numbers.end(), el))
        {
            el = rand() % numOfQuestions;
        }
        numbers.push_back(el);
    }
    return numbers;
}

class MainScreen
{
public:
    MainScreen() { show(); };
    friend class Quiz;

private:
    void show();
    void initQuiz(int quiz, string chosen);
    void initTest(int test, string chosen);
    void resultsQuiz(int score);
    void resultsTest(int score);
};

class Quiz
{
public:
    Quiz(int quiz)
    {
        pick(quiz);
        score = 0;
    };
    friend class MainScreen;

private:
    int score;
    string questions[10];
    string answers[10];
    char correct[10];
    void pick(int quiz);
    int start(string chosen);
    void ask(int i);
};

class Test
{
public:
    Test(int test)
    {
        pick(test);
        score = 0;
    };
    int score;
    void pick(int test);
    string questions[25];
    string answers[25];
    char correct[25];
    int start(string chosen);
    void ask(int i);
};

void MainScreen::show()
{
    system("CLS");
    int q;
    cout << "Welcome!!!" << endl;
    cout << "Choose a quiz: \n\n";
    cout << "0: C++ Quiz\n\n";
    cout << "1: JAVA Quiz\n\n";
    cout << "or go to test: \n\n";
    cout << "2: C++ Test\n\n";
    cout << "3: JAVA Test\n\n";
    cout << "\n\n4: Exit\n\n";
    cin.clear();
    fflush(stdin);
    cin >> q;
    switch (q)
    {
    case 0:
        system("CLS");
        initQuiz(0, "C++");
        break;
    case 1:
        system("CLS");
        initQuiz(1, "JAVA");
        break;
    case 2:
        system("CLS");
        initTest(0, "C++");
        break;
    case 3:
        system("CLS");
        initTest(1, "JAVA");
        break;
    case 4:
        break;
    default:
        cout << "There is no such quiz/test" << endl;
        cout << "Press any key to start again" << endl;
        getch();
        system("CLS");
        show();
        break;
    }
}

void MainScreen::initQuiz(int quiz, string chosen)
{
    Quiz A(quiz);
    resultsQuiz(A.start(chosen));
    return show();
}

void MainScreen::initTest(int test, string chosen)
{
    Test A(test);
    resultsTest(A.start(chosen));
    return show();
}

void MainScreen::resultsQuiz(int score)
{
    system("CLS");
    cout << "Your score: " << score << " / " << 10 << endl;
    cout << "Percentage: " << (score / 10.0) * 100 << " %" << endl;
    cout << endl;
    cout << "Press any key to show main screen." << endl;
    getch();
}

void MainScreen::resultsTest(int score)
{
    time_t now = time(0);
    system("CLS");
    cout << "Your score: " << score << " / " << 25 << endl;
    cout << "Percentage: " << (score / 25.0) * 100 << " %" << endl;
    cout << endl;
    if(score >= 12){
        cout << "Congratulations! You have passed the test." << endl;
    } else {
        cout << "I'm sorry but you failed the test." << endl;
    }

    ofstream results;
    results.open("results.txt", ofstream::app);
    if (results.is_open()){
        results << "Score: " << score << "/" << 25 << "\nDate: " << asctime(localtime(&now)) << "\n\n";
    }
    results.close();

    cout << "Press any key to show main screen." << endl;
    getch();
}

void Quiz::pick(int quiz)
{
    ifstream q;
    ifstream a;
    ifstream c;
    switch (quiz)
    {
    case 0:
        //ifstream q("questionsA.txt");
        //ifstream a("answersA.txt");
        //ifstream c("correctA.txt");
        q.open("questionsA.txt");
        a.open("answersA.txt");
        c.open("correctA.txt");
        break;
    case 1:
        //ifstream q("questionsA.txt");
        //ifstream a("answersA.txt");
        //ifstream c("correctA.txt");
        q.open("questionsB.txt");
        a.open("answersB.txt");
        c.open("correctB.txt");
        break;
    }
    if (q.is_open() && a.is_open() && c.is_open())
    {
        vector<int> numbers = randoms(10, 25);
        string line;
        int i = 0;
        int t;
        while (getline(q, line))
        {
            if (count(numbers.begin(), numbers.end(), i))
            {
                for (t = 0; t < 10; t++)
                {
                    if (numbers[t] == i)
                        break;
                }
                questions[t] = line;
            }
            i++;
        }
        q.close();
        i = 0;
        while (getline(a, line))
        {
            if (count(numbers.begin(), numbers.end(), i))
            {
                for (t = 0; t < 10; t++)
                {
                    if (numbers[t] == i)
                        break;
                }
                answers[t] = line;
            }
            i++;
        }
        a.close();
        i = 0;
        char l;
        while (!c.eof())
        {
            c.get(l);
            if (l == '\n')
                continue;
            if (count(numbers.begin(), numbers.end(), i))
            {
                for (t = 0; t < 10; t++)
                {
                    if (numbers[t] == i)
                        break;
                }
                correct[t] = l;
            }
            i++;
        }
    }
    else
    {
        system("CLS");
        cout << "Unable to open a file" << endl;
    }
}

int Quiz::start(string chosen)
{
    system("CLS");
    cout << "You have chosen " << chosen << " Quiz\n";
    cout << "You will be asked 10 questions.\n";
    cout << "Every question has only one correct answer\n";
    cout << "For every correct answer you get 1 point.\n";
    cout << "Good luck!\n\n";
    cout << "Press any key to start\n";
    getch();
    ask(0);
    return score;
}

void Quiz::ask(int i)
{
    if (i == 10)
    {
        return;
    }
    system("CLS");
    char a = 'A';
    char answer;
    cout << i+1 << ": " << questions[i] << "\n\n";
    int temp = 0;
    int pos;
    while (true)
    {
        pos = answers[i].substr(temp).find("|");
        if (pos == string::npos)
        {
            cout << (char)a << ". " << answers[i].substr(temp) << "\n\n";
            break;
        }
        cout << (char)a << ". " << answers[i].substr(temp, pos) << "\n\n";
        temp += pos + 1;
        a += 1;
    }
    cin.clear();
    fflush(stdin);
    cin >> answer;
    if (answer == correct[i] || (char)(answer - 32) == correct[i])
    {
        score += 1;
    }
    ask(i + 1);
}

void Test::pick(int test){
    ifstream q;
    ifstream a;
    ifstream c;
    switch (test)
    {
    case 0:
        //ifstream q("questionsA.txt");
        //ifstream a("answersA.txt");
        //ifstream c("correctA.txt");
        q.open("questionsA.txt");
        a.open("answersA.txt");
        c.open("correctA.txt");
        break;
    case 1:
        //ifstream q("questionsA.txt");
        //ifstream a("answersA.txt");
        //ifstream c("correctA.txt");
        q.open("questionsB.txt");
        a.open("answersB.txt");
        c.open("correctB.txt");
        break;
    }
    if (q.is_open() && a.is_open() && c.is_open())
    {
        vector<int> numbers = randoms(25, 25);
        string line;
        int i = 0;
        int t;
        while (getline(q, line))
        {
            if (count(numbers.begin(), numbers.end(), i))
            {
                for (t = 0; t < 25; t++)
                {
                    if (numbers[t] == i)
                        break;
                }
                questions[t] = line;
            }
            i++;
        }
        q.close();
        i = 0;
        while (getline(a, line))
        {
            if (count(numbers.begin(), numbers.end(), i))
            {
                for (t = 0; t < 25; t++)
                {
                    if (numbers[t] == i)
                        break;
                }
                answers[t] = line;
            }
            i++;
        }
        a.close();
        i = 0;
        char l;
        while (!c.eof())
        {
            c.get(l);
            if (l == '\n')
                continue;
            if (count(numbers.begin(), numbers.end(), i))
            {
                for (t = 0; t < 25; t++)
                {
                    if (numbers[t] == i)
                        break;
                }
                correct[t] = l;
            }
            i++;
        }
    }
    else
    {
        system("CLS");
        cout << "Unable to open a file" << endl;
    }
}

int Test::start(string chosen)
{
    string name;
    system("CLS");
    cout << "You have chosen " << chosen << " Test\n";
    cout << "You will be asked 25 questions.\n";
    cout << "Every question has only one correct answer\n";
    cout << "For every correct answer you get 1 point.\n";
    cout << "To pass this test you have to gain at least 12 points.\n";
    cout << "Good luck!\n\n";
    cout << "Enter your full name and index number\n";
    cin.clear();
    fflush(stdin);
    getline(cin, name);
    ofstream results;
    results.open("results.txt", ofstream::app);
    if (results.is_open()){
        results << "Student: " << name << "\nTest: " << chosen <<"\n";
    }
    results.close();
    ask(0);
    return score;
}

void Test::ask(int i)
{
    if (i == 25)
    {
        return;
    }
    system("CLS");
    char a = 'A';
    char answer;
    cout << i+1 << ": " << questions[i] << "\n\n";
    int temp = 0;
    int pos;
    while (true)
    {
        pos = answers[i].substr(temp).find("|");
        if (pos == string::npos)
        {
            cout << (char)a << ". " << answers[i].substr(temp) << "\n\n";
            break;
        }
        cout << (char)a << ". " << answers[i].substr(temp, pos) << "\n\n";
        temp += pos + 1;
        a += 1;
    }
    cin.clear();
    fflush(stdin);
    cin >> answer;
    if (answer == correct[i] || (char)(answer - 32) == correct[i])
    {
        score += 1;
    }
    ask(i + 1);
}

int main(int argc, char *argv[])
{
    srand(time(0));
    MainScreen M;
    return 0;
}
