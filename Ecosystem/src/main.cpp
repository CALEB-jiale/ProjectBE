#include "./bug/Bug.h"
#include "./bug/BugFactory.h"
#include "./environment/Aquarium.h"
#include "./environment/Milieu.h"

#include "constants.h"

#include <iostream>
#include <array>

using namespace std;

void showMessageBar() {
    system("clear");
    cout << "============================================" << endl;
    cout << "============================================" << endl;
    cout << "There are 5 kinds of bugs: " << endl;
    cout << "[1] : Social - Orange" << endl;
    cout << "[2] : Fearful - Blue" << endl;
    cout << "[3] : Suicide Boomer - Red" << endl;
    cout << "[4] : Careful - Green " << endl;
    cout << "[5] : MultiPersona" << endl;
    cout << "Please set the percentage for each type of bug (Press q to exit)： " << endl;
}

std::array<int, 5> getPercentages() {
    std::array<int, 5> nums;
    int sum = 0;

    showMessageBar();

    // 循环读入 5 个数
    for (int i = 0; i < 5; i++) {
        std::cout << "Social: ";
        std::cin >> nums[i];

        // 判断输入的数是否大于 0
        if (nums[i] <= 0) {
            std::cerr << "输入错误：数字必须大于 0。" << std::endl;
            return {};
        }

        sum += nums[i];
    }

    // 判断输入的数是否和为 100
    if (sum != 100) {
        std::cerr << "输入错误：数字之和必须为 100。" << std::endl;]
    }

    return nums;
}

int get_user_comportement_choose() {
    showMessageBar();
    
  char index_comportement = 0;
  index_comportement = getchar();

  if(index_comportement == 'q'){
    exit(0);
  }
  if(isdigit(index_comportement) == 0){
    index_comportement = 0;
  } else {
    index_comportement -= '0';
  }
  cout << "Your choose is:  " << int(index_comportement) << endl;
  cout << "============================================" << endl;
  cout << "============================================\n" << endl;
  return int(index_comportement);
}

int main() {
    while (1) {
        
        int numBugs = INIT_BUG_NUM;
        int force_comportement = get_user_comportement_choose();

        Aquarium ecosysteme(MILIEU_WIDTH, MILIEU_HEIGHT+INFO_BAR_HEIGHT, 30);

        auto &milieu = ecosysteme.getMilieu();
        BestiolFactory bestiole_factory(milieu.getWidth(), milieu.getHeight());
        bestiole_factory.force_comportement = force_comportement;
        milieu.setBestioleFactory(&bestiole_factory);

        for (int i = 1; i <= total_num_bestiole; ++i)
            ecosysteme.getMilieu().addMember(bestiole_factory.create_bestiole());

        ecosysteme.run();
        getchar();
    }
    
    return 0;
}
