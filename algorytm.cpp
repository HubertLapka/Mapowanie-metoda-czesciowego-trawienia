#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include <chrono>
using namespace std;
using namespace std::chrono;

const string FILE_NAME = "instancja.txt";
int tmp = 0;
auto lastPart = make_shared<int>(tmp);

pair<vector<int>, vector<int>> getFile(string filename);
pair<bool, vector<int>> canBeAdded(vector<int> A, vector<int> solution, int length, int number);
void szukaj(vector<int> A, vector<int> solution, int ind, int maxind, int length, shared_ptr<int> jest);
unsigned long long factorial(int n);
unsigned long long binomialCoefficient(int n, int k);

int main() {
    auto start = high_resolution_clock::now();
    pair<vector<int>, vector<int>> data = getFile(FILE_NAME);
    vector<int> A = data.first;
    vector<int> solutionA = data.second;
    vector<int> solution;
    auto jest = make_shared<int>(0);

    int cuts = 0;
    unsigned long long result = 0;
    for (int i = 1; i < 20; i++) {
        cuts = i;
        result = binomialCoefficient(cuts + 2, 2);
        if (result == A.size()) {
            break;
        }
        if (i == 19) {
            cout << "error: incorrect number of cuts";
            return 1;
        }
    }
    cout << "set A:";
    for (int num : A) {
        cout << " " << num;
    }
    cout << endl;

    auto maxElementIter = max_element(A.begin(), A.end());
    auto secondMaxElementIter = max_element(A.begin(), maxElementIter);
    int maxElement = *maxElementIter;
    int secondMaxElement = *secondMaxElementIter;
    int startingElement = maxElement - secondMaxElement;

    solution.push_back(startingElement);

    auto it = find(A.begin(), A.end(), startingElement);
    A.erase(it);
    it = find(A.begin(), A.end(), maxElement);
    A.erase(it);
    it = find(A.begin(), A.end(), secondMaxElement);
    A.erase(it);

    szukaj(A, solution, 1, cuts, maxElement, jest);
    if (*jest == 0) {
        cout << "no solution found";
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Czas wykonania: " << duration.count() << " milisekund\n";
    return 0;
}

pair<vector<int>, vector<int>> getFile(string filename) {
    vector<int> A, solutionA;
    ifstream File(filename);
    if (File.is_open()) {
        string line;
        if (getline(File, line)) {
            stringstream ss(line);
            int number;
            while (ss >> number) {
                A.push_back(number);
            }
        }
        if (getline(File, line)) {
            stringstream ss(line);
            int number;
            while (ss >> number) {
                solutionA.push_back(number);
            }
        }
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
    File.close();
    return make_pair(A, solutionA);
}

pair<bool, vector<int>> canBeAdded(vector<int> A, vector<int> solution, int length, int number) {
    int sum = 0;
    vector<int> toRemove;
    for (int i = solution.size() - 1; i >= 0; i--) {
        int toFind = number + solution[i] + sum;
        auto it = find(A.begin(), A.end(), toFind);
        if (it != A.end()) {
            toRemove.push_back(distance(A.begin(), it));
        }
        else {
            return make_pair(false, toRemove);
        }
        sum += solution[i];
    }
    int sum2 = 0;
    for (int i = 0; i < solution.size(); i++) {
        sum2 += solution[i];
    }
    int toFind2 = length - (number + sum2);
    auto it2 = find(A.begin(), A.end(), toFind2);
    auto it3 = find(A.begin(), A.end(), number);
    if (it2 != A.end()) {
        *lastPart = A[distance(A.begin(), it2)];
        toRemove.push_back(distance(A.begin(), it2));
        toRemove.push_back(distance(A.begin(), it3));
        return make_pair(true, toRemove);
    }
    else {
        return make_pair(false, toRemove);
    }
}

void szukaj(vector<int> A, vector<int> solution, int ind, int maxind, int length, shared_ptr<int> jest) {
    if (ind == maxind) {
        cout << endl << "Solution:";
        for (int num : solution) {
            cout << " | " << num;
        }
        cout << " | " << *lastPart << " | " << endl;
        *jest = 1;
    }
    else {
        for (int i = 0; i < A.size(); i++) {
            int number = A[i];
            pair<bool, vector<int>> info = canBeAdded(A, solution, length, number);
            if (info.first == true) {
                vector<int> afterRemove;
                for (int j = 0; j < A.size(); j++) {
                    auto it = find(info.second.begin(), info.second.end(), j);
                    if (it == info.second.end()) {
                        afterRemove.push_back(A[j]);
                    }
                }
                vector<int> newA = afterRemove;
                vector<int> newSolution = solution;
                newSolution.push_back(number);
                szukaj(newA, newSolution, ind + 1, maxind, length, jest);
            }
            if (*jest == 1)
                break;
        }
    }
}

unsigned long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

unsigned long long binomialCoefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    else {
        return factorial(n) / (factorial(k) * factorial(n - k));
    }
}
