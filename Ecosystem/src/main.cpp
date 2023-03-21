#include <iostream>
#include <array>

#include "./environment/Aquarium.h"
#include "constants.h"

//#include "constants.h"

using namespace std;

void showMessageBar() {
    system("clear");
    cout << "============================================" << endl;
    cout << "============================================" << endl;
    cout << "There are 5 kinds of bugs: " << endl;
    cout << "[1] : MultiPersona" << endl;
    cout << "[2] : Fearful - Blue" << endl;
    cout << "[3] : Suicide Boomer - Red" << endl;
    cout << "[4] : Social - Green" << endl;
    cout << "[5] : Careful - Purple" << endl;
    cout << "[6] : Reset Analyse Result (0: No, 1: Yes)" << endl;
    cout << "Please set the number for each type of bug (Enter -1 to exit)." << endl;
}

std::array<int, 5> getNums() {
    std::array<int, 5> nums;

    showMessageBar();

    for (int i = 0; i < 5; i++) {
        std::cout << "[" << i + 1 << "] : ";
        std::cin >> nums[i];

        if (nums[i] < 0) {
            exit(0);
        }
    }

    std::cout << "[6] : ";
    std::cin >> nums[5];

    if (nums[5] != 0 && nums[5] != 1) {
        exit(0);
    }

    return nums;
}

int main() {
    while(1) {
        showMessageBar();
        std::array<int, 5> nums = getNums();
        
        Aquarium ecosysteme(MILIEU_WIDTH, MILIEU_HEIGHT+INFO_BAR_HEIGHT, 30);

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < nums[i]; j++) {
                ecosysteme.addBug(i+1);
            }
        }
        
        if (nums[5] == 1) {
            ecosysteme.reset();
        }
        
        ecosysteme.run();
    }
    return 0;
}
