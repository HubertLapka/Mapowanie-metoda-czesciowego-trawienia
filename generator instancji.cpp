#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> MAPA = { 4, 8, 12, 8, 9, 15, 7, 6, 8, 11, 17, 1, 8, 15, 6 }; // <=================================================

vector<int> calculateCumulativeSums(const vector<int>& input, int groupSize) {
    vector<int> cumulativeSums;
    for (int i = 0; i <= input.size() - groupSize; ++i) {
        int sum = 0;
        for (int j = 0; j < groupSize; ++j) {
            sum += input[i + j];
        }
        cumulativeSums.push_back(sum);
    }
    return cumulativeSums;
}

void saveResultToFile(const vector<int>& data, const string& filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (int value : data) {
            outputFile << value << " ";
        }
        outputFile.close();
        cout << "Wynik zapisano do pliku: " << filename << endl;
    } else {
        cerr << "Nie mo¿na otworzyæ pliku do zapisu." << endl;
    }
}

int main() {
    vector<int> sumresult;
    for (int i = 0; i < MAPA.size(); i++) {
        int groupSize = i + 1;

        vector<int> result = calculateCumulativeSums(MAPA, groupSize);
        sumresult.insert(sumresult.end(), result.begin(), result.end());
    }
    sort(sumresult.begin(), sumresult.end());
    int count = 0;
    for (int value : sumresult) {
        cout << value << " ";
        count++;
    }
    cout << endl << "Amount: " << count << endl;

    saveResultToFile(sumresult, "instancja14b.txt");

    return 0;
}
