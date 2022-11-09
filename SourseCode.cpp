#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <unordered_set>
using namespace std;

//Define a structure, easier to save formatted data
typedef map<float, float> Node;

vector<Node> multi_data;
vector<string> saved_multi;

//Create a polynomial line
void Create_multi(Node& cur_multi) {
    string a, b;
    cout << "Please enter coefficient and the exponent(input # to quit): " << "\n";
    while (true) {
        cin >> a >> b;
        if(a == "#" || b == "#") return;
        float coef = stof(a);
        float expo = stof(b);
        cur_multi[expo] += coef;
    }
}

//Construct a polynomial, make it a string
string Construct_multi(Node& cur_multi) {
    string res;
    for(auto x : cur_multi) {
        if(x.second == 0) continue; //指数为0跳过
        //using string stream convert float to string
        stringstream cof; stringstream exp;
        cof << x.first; exp << x.second;

        if(res.empty() || x.second < 0) {
            if(x.first != 0) {
                //.str(): get data out from stream
                res += exp.str() + "x^" + cof.str();
            } else {
                res += exp.str();
            }
        } else { //系数为正，加上加号
            if(x.first != 0) {
                res += "+" + exp.str() + "x^" + cof.str();
            } else {
                res += "+" + exp.str();
            }
        }
    }
    return res;
}

//sum the equation
Node Sum_two_multi(Node& fst, Node& sec) {
    map<float, float> res;
    for(auto x : fst) {
        float e = x.first, p = x.second;
        res[e] += p;
    }
    for(auto x : sec) {
        float e = x.first, p = x.second;
        res[e] += p;
    }
    return res;
}

//multiply two multiplies
Node Multiply_two_multi(Node& fst, Node& sec) {
    Node res;
    for (auto x: fst) {
        float e1 = x.first, p1 = x.second;
        for (auto y: sec) {
            float e2 = y.first, p2 = y.second;
            res[e1 + e2] += p1 * p2;
        }
    }
    return res;
}

void Show_all_multi() {
    cout << "All of the polynomials were as follows: " << endl;
    int cnt = 0;
    for (const auto& x: saved_multi) {
        cout << cnt << ": " << x << endl;
        cnt++;
    }
}

//save all the polynomials into buffer
void Save_multi(Node cur_multi) {
    multi_data.push_back(cur_multi);
    saved_multi.push_back(Construct_multi(cur_multi));
}

void Delete_multi() {
    int index = 1;
    //record all of deleted element
    unordered_set<int> deleted_list;
    while (index >= 0) {
        cin >> index;
        if (index >= (int) multi_data.size()) continue;
        else deleted_list.insert(index);
    }
    vector<Node> cur_val;
    vector<string> cur_str;
    for (int i = 0; i < (int) multi_data.size(); i++) {
        if (deleted_list.count(i)) continue;
        else {
            cur_val.push_back(multi_data[i]);
            cur_str.push_back(saved_multi[i]);
        }
    }
    //clear old data then refresh them with new ones
    multi_data.clear();
    multi_data = cur_val;
    saved_multi.clear();
    saved_multi = cur_str;
}

//Copy function
void Copy_multi(int idx) {
    Save_multi(multi_data[idx]);
}

//Show menu
void Display_menu() {
    cout << "Welcome to the polynomial calculator :) Press your operations" << "\n";
    cout << "Functions:" << "\n";
    cout << "a: Create a new polynomial" << "\n";
    cout << "b: Display all of polynomial current saved" << "\n";
    cout << "c: Delete polynomial" << "\n";
    cout << "d: Display the n-th polynomial" << "\n";

    cout << "e: Sum the polynomial" << "\n";
    cout << "f: Multiply the polynomial" << "\n";
    cout << "g: Copy the polynomial" << "\n";
    cout << "z: Quit the polynomial calculator" << endl;
}

//Copy the display menu
void Display_copy() {
    Show_all_multi();
    cout << "Please input the index you want to save:" << "\n";
    int num;
    cin >> num;
    int len_of_multi = (int) saved_multi.size();
    if (num < 0 || num >= len_of_multi) {
        cout << "The polynomial doesn't exist. Press any button to return to menu :(" << endl;
        string tmp;
        cin >> tmp;
        return Display_menu();
    }
    Copy_multi(num);
    cout << "The results are as follows:" << "\n";
    Show_all_multi();
    cout << "Press any button then ENTER to return to menu" << endl;
    string tmp;
    cin >> tmp;
    return Display_menu();
}

//Interface of creating a polynomial
void Show_construct_multi() {
    cout << "Please enter the number of polynomial:" << endl;
    int cnt;
    cin >> cnt;
    if (cnt <= 0) return Display_menu();

    cout << "Please enter the polynomial(enter # to quit):" << "\n";
    cout << "i.e: to make polynomial 3x^4 - 0.5x^0.6 + 7" << "\n";
    cout << "Please enter 3 4 -0.5 0.6 7 0 #" << "\n";
    for (int i = 0; i < cnt; i++) {
        Node tmp;
        Create_multi(tmp);
        Save_multi(tmp);
    }
    cout << "Created! Returning to menu!" << endl;
    return Display_menu();
}

//Interface of deleting a polynomial
void Show_delete_multi() {
    Show_all_multi();
    cout << "Please enter the index of the polynomial you want to delete:" << "\n";
    cout << "-1 to end your input." << "\n";
    Delete_multi();
    cout << "The Polynomial after deleted is:" << "\n";
    Show_all_multi();
    cout << "Press any button to return to the menu" << "\n";
    getchar();
    return Display_menu();
}

//Interface of a particular polynomial
void Show_particular_multi() {
    cout << "Please enter the index of polynomial: " << "\n";
    int len = (int) saved_multi.size() - 1;
    cout << "The range of index is: 0 ~ " << len << "\n";
    int idx;
    cin >> idx;
    cout << saved_multi[idx] << "\n";
    cout << "Press any button to return to the menu." << endl;
    getchar();
    return Display_menu();
}

//Interface of polynomial multiply
void Show_multiply() {
    vector<int> index;
    int len = (int) saved_multi.size() - 1;
    cout << "i.e: 0 1 0 -1 Enter" << "\n";
    cout << "Please input the index of the polynomial"
            "(input -1 to end, from 0 ~ " << len << "):" << endl;
    int idx;
    while (true) {
        cin >> idx;
        if (idx == -1) break;
        index.push_back(idx);
    }
    Node res = multi_data[index[0]];
    for (int i = 1; i < (int) index.size(); i++) {
        res = Multiply_two_multi(res, multi_data[index[i]]);
    }
    cout << "The result is: " << "\n";
    cout << Construct_multi(res) << endl;
    cout << "Do you want to save the results(yes:1 no:0)?" << endl;
    int val;
    cin >> val;
    if (val == 1) Save_multi(res);
    return Display_menu();
}

//Interface of sum polynomial
void Show_sum_multi() {
    vector<int> index;
    int len = (int) saved_multi.size() - 1;
    cout << "Please inter the index of the polynomial(ends with -1)" << "\n";
    cout << "i.e: 0 1 0 -1 Enter (The range: 0 ~ " << len << ")" << endl;
    int idx;
    while (true) {
        cin >> idx;
        if (idx == -1) break;
        index.push_back(idx);
    }
    Node res = multi_data[index[0]];
    for (int i = 1; i < (int) index.size(); i++) {
        res = Sum_two_multi(res, multi_data[i]);
    }
    cout << "The result are: " << "\n";
    cout << Construct_multi(res) << "\n";
    cout << "Do you want to save the results?" << endl;
    cout << "To save, press 1, No, press 0" << "\n";
    int inpt;
    cin >> inpt;
    if (inpt == 1) Save_multi(res);
    return Display_menu();
}

//The menu of the program
void Menu(char inpt) {
    switch (inpt) {
        case 'a': //Construct a polynomial
            Show_construct_multi();
            cin >> inpt;
            Menu(inpt);
            break;
        case 'b': //Display all saved polynomial
            Show_all_multi();
            cout << "Press any button and Enter to return to menu." << "\n";
            cin >> inpt;
            Display_menu();
            cin >> inpt;
            Menu(inpt);
            break;
        case 'c': //Delete
            Show_delete_multi();
            cin >> inpt;
            Menu(inpt);
            break;
        case 'd': //Display the n-th polynomial
            Show_particular_multi();
            cin >> inpt;
            Menu(inpt);
            break;
        case 'e': //sum
            Show_sum_multi();
            cin >> inpt;
            Menu(inpt);
            break;
        case 'f': //multiple
            Show_multiply();
            cin >> inpt;
            Menu(inpt);
            break;
        case 'g': //Copy
            Display_copy();
            cin >> inpt;
            Menu(inpt);
            break;
        case 'z': //Quit
            cout << "Thanks for using!" << endl;
            return;
        default:
            cout << "Input wrong, press any button to return to the menu." << endl;
            Display_menu();
            cin >> inpt;
            Menu(inpt);
            break;
    }
}

int main()
{
    multi_data.clear();
    Display_menu();
    cout << "Please input functions:" << endl;
    char keyboard_input;
    cin >> keyboard_input;
    Menu(keyboard_input);

    return 0;
}