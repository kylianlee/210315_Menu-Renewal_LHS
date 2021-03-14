//
// Created by Kylian Lee on 2021/03/13.
//

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector<string> solution(vector<string> orders, vector<int> course);
vector<string> powerSet(string tmpOrder);
vector<pair<int, int>> mostPopCourse(map<string, int> courseMenu, vector<int> course);
vector<string> selectCourse(map<string, int> courseMenu, vector<pair<int, int>> maxCourse);

int main() {
    vector<string> orders, answer;
    vector<int> course;

    orders.push_back("XYZ");
    orders.push_back("XWY");
    orders.push_back("WXA");

//    orders.push_back("ABCFG");
//    orders.push_back("AC");
//    orders.push_back("CDE");
//    orders.push_back("ACDE");
//    orders.push_back("BCFG");
//    orders.push_back("ACDEH");

//    orders.push_back("ABCDE");
//    orders.push_back("AB");
//    orders.push_back("CD");
//    orders.push_back("ADE");
//    orders.push_back("XYZ");
//    orders.push_back("XYZ");
//    orders.push_back("ACD");

    course.push_back(2);
    course.push_back(3);
    course.push_back(4);

    answer = solution(orders, course);

    for(int i = 0; i < answer.size(); i++){
        cout << answer[i] << endl;
    }

    return 0;
}

vector<string> solution(vector<string> orders, vector<int> course) {
    map<string, int> courseMenu;
    int orderSize = orders.size(), courseSize = course.size();
    string tmpOrder, temp;
    vector<string> orderComb, answer;
    int combSize = 0;
    map<string, int>::iterator iter;
    vector<pair<int, int>> maxCourse;

    for(int i = 0; i < orderSize; i++){
        tmpOrder = orders[i];
        sort(tmpOrder.begin(), tmpOrder.end());
        orderComb = powerSet(tmpOrder);
        combSize = orderComb.size();
        for(int j = 0; j < combSize; j++){
            int length = orderComb[j].length();
            for(int k = 0; (k < courseSize); k++){
                if(length == course[k]) {
                    iter = courseMenu.find(orderComb[j]);
                    if (iter == courseMenu.end())
                        courseMenu.insert(pair<string, int>(orderComb[j], 1));
                    else
                        iter->second++;
                }
                else continue;
            }
        }
    }

    maxCourse = mostPopCourse(courseMenu, course);

    answer = selectCourse(courseMenu, maxCourse);

    sort(answer.begin(), answer.end());

    return answer;
}

vector<string> powerSet(string tmpOrder){
    int length = tmpOrder.length();
    int max = 1 << length;
    vector<string> orderComb;
    string temp;

    for(int i = 0; i < max; i++){
        for(int j = 0; j < length; j++)
            if(i & (1 << j)) temp.push_back(tmpOrder[j]);

        orderComb.push_back(temp);
        temp.clear();
    }
    return orderComb;
}

vector<pair<int, int>> mostPopCourse(map<string, int> courseMenu, vector<int> course){
    map<string, int>::iterator iter;
    vector<pair<int, int>> maxCourse;
    int length;
    int courseSize = course.size();

    for(int i = 0; i < courseSize; i++){
        maxCourse.push_back(make_pair(course[i], 0));
    }

    for(int i = 0; i < courseSize; i++){
        for(iter = courseMenu.begin(); iter != courseMenu.end(); iter++){
            length = iter->first.length();
            if(length == course[i]) {
                if (maxCourse[i].second <= iter->second)
                    maxCourse[i].second = iter->second;
                else continue;
            }else continue;
        }
    }

    return maxCourse;
}

vector<string> selectCourse(map<string, int> courseMenu, vector<pair<int, int>> maxCourse){
    map<string, int> finalCourse;
    int courseSize = maxCourse.size();
    map<string, int>::iterator iter;
    vector<string> answer;

    for(iter = courseMenu.begin(); iter != courseMenu.end(); iter++){
        for(int i = 0; i < courseSize; i++){
            if(iter->first.length() == maxCourse[i].first)
                if((iter->second == maxCourse[i].second) && (iter->second > 1))
                    answer.push_back(iter->first);
//                    finalCourse.insert(make_pair(iter->first, iter->second));
        }
    }
    return answer;
}
