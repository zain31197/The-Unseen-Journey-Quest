#include <iostream>
#include <stack>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;
int score=0;
class node {
public:
    char data;
    node* down;
    node* up;
    node* left;
    node* right;

    node(char data) {
        this->data = data;
        this->down = NULL;
        this->left = NULL;
        this->up = NULL;
        this->right = NULL;
    }
};

class grid {
public:
    node* head;
    int rows;
    int cols;
    int gamestartdistance;
    int currentdistance;

    grid() {
        head = NULL;
        rows = 0;
        cols = 0;
        gamestartdistance = 0;
        currentdistance = 0;
    }

    void creategrid(int rows, int cols) {
        if (rows == 0 || cols == 0) 
            return;
        this->rows = rows;
        this->cols = cols;
        head = new node('#');
        node* temp = head;
        node* prevrow = NULL;
        for (int i = 0; i < rows; i++) {
            node* rowhead = temp;
            for (int j = 1; j < cols; j++) {
                node* newNode = new node('#');
                temp->right = newNode;
                newNode->left = temp;
                temp = temp->right;
            }
            if (prevrow) {
                node* tempupper = prevrow;
                node* templower = rowhead;
                while (tempupper && templower) {
                    tempupper->down = templower;
                    templower->up = tempupper;
                    tempupper = tempupper->right;
                    templower = templower->right;
                }
            }
            if (i < rows - 1) {
                node* nextRow = new node('#');
                rowhead->down = nextRow;
                nextRow->up = rowhead;
                temp = nextRow;
                prevrow = rowhead;
            }
        }
    }

    node* getnode(int row, int col) {
        node* temp = head;
        for (int i = 0; i < row; i++) {
            temp = temp->down;
        }
        for (int j = 0; j < col; j++) {
            temp = temp->right;
        }
        return temp;
    }

    void placerandomelements() {
        char elem[] = { 'P', 'K', 'D', 'B' };
        int size = 4;
        int randomRow, randomCol;
        node* targetNode;
        for (int i = 0; i < size; i++) {
            do {
                randomRow = rand() % rows;
                randomCol = rand() % cols;
                targetNode = getnode(randomRow, randomCol);
            } while (targetNode->data != '#');
            targetNode->data = elem[i];
        }
    }

    void placecoinrandomly() {
        clearcoins();
        int n = rand() % 5 + 1;
        for (int i = 0; i < n; i++) {
            int randomRow, randomCol;
            node* targetNode;
            do {
                randomRow = rand() % rows;
                randomCol = rand() % cols;
                targetNode = getnode(randomRow, randomCol);
            } while (targetNode->data != '#');
            targetNode->data = 'C';
        }
    }

    void clearcoins() {
        node* temp = head;
        while (temp != nullptr) {
            node* temp2 = temp;
            while (temp2 != nullptr) {
                if (temp2->data == 'C') {
                    temp2->data = '#';
                }
                temp2 = temp2->right;
            }
            temp = temp->down;
        }
    }

    node* getkeylocation() {
        node* temp = head;
        while (temp != nullptr) {
            node* temp2 = temp;
            while (temp2 != nullptr) {
                if (temp2->data == 'K') {
                    return temp2;
                }
                temp2 = temp2->right;
            }
            temp = temp->down;
        }
        return nullptr;
    }

    node* getplayerposition() {
        node* temp = head;
        while (temp != nullptr) {
            node* temp2 = temp;
            while (temp2 != nullptr) {
                if (temp2->data == 'P') {
                    return temp2;
                }
                temp2 = temp2->right;
            }
            temp = temp->down;
        }
        return nullptr;
    }

    void cityblockdistanceformula() {
        node* key = getkeylocation();
        node* playerloc = getplayerposition();
        if (!key || !playerloc) return;

        int playerx = 0, playery = 0;
        int keyx = 0, keyy = 0;
        node* temp = head;
        for (int i = 0; i < rows; i++) {
            node* temp2 = temp;
            for (int j = 0; j < cols; j++) {
                if (temp2 == key) {
                    keyx = i;
                    keyy = j;
                }
                if (temp2 == playerloc) {
                    playerx = i;
                    playery = j;
                }
                temp2 = temp2->right;
            }
            temp = temp->down;
        }
        currentdistance = abs(playerx - keyx) + abs(playery - keyy);
        if (gamestartdistance == 0) {
            gamestartdistance = currentdistance;
        }
    }

    void sensepower() {
        cityblockdistanceformula();
        if (gamestartdistance > currentdistance) {
            cout << "You are getting closer." << endl;
        } else if (currentdistance > gamestartdistance) {
            cout << "You are getting farther." << endl;
        } else {
            cout << "You are at the same distance." << endl;
        }
        gamestartdistance = currentdistance; 
    }

    void print() {
        node* row = head;
        while (row != nullptr) {
            node* temp = row;
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->right;
            }
            cout << endl;
            row = row->down;
        }
        cout << endl;
    }
};

class playermovement {
public:
    node* position;
    stack<node*> undo;
    vector<pair<int, int>> collectedCoins;
    int remainingundo;
    int noofmovesremaining;
    bool gameover;

    playermovement(grid& g) {
        remainingundo = 5;
        position = g.getplayerposition();
        noofmovesremaining=8;
        gameover=false;
    }
    void calculatefinalscore()
    {
         score += remainingundo; 
         score+=noofmovesremaining;
        cout << "Final Score: " << score << endl;
    }
    
    void move(node* newposition) {
        noofmovesremaining--;
        if(noofmovesremaining<=0)
        {
            cout<<"Moves limit reached"<<endl;
            cout<<"GameOver"<<endl;
            calculatefinalscore();
            gameover=true;
            return ;
        }
        if (newposition->data == 'B') {
            cout << "You steped in to Bomb Game Over" << endl;
            calculatefinalscore();
            return;
        }
        if (remainingundo > 0) {
            undo.push(position);
        }
        if (newposition->data == 'C') {
            cout << "Coin collected!" << endl;
            score+=2;
            remainingundo++;
        }
        position->data = '#';
        position = newposition;
        position->data = 'P';
    }

    void leftmove() {
        if (position->left == nullptr) {
            cout << "Invalid move!" << endl;
            return;
        }
        move(position->left);
    }

    void rightmove() {
        if (position->right == nullptr) {
            cout << "Invalid move!" << endl;
            return;
        }
        move(position->right);
    }

    void upmove() {
        if (position->up == nullptr) {
            cout << "Invalid move!" << endl;
            return;
        }
        move(position->up);
    }

    void downmove() {
        if (position->down == nullptr) {
            cout << "Invalid move!" << endl;
            return;
        }
        move(position->down);
    }

    void undofeature() {
        if (undo.empty()) {
            cout << "No moves to undo!" << endl;
            return;
        }
        if (remainingundo == 0) {
            cout << "No remaining undo power!" << endl;
            return;
        }
        position->data = '#';
        position = undo.top();
        undo.pop();
        position->data = 'P';
        remainingundo--;
    }
      bool isGameOver() {
        return gameover;
    }
};

int main() {
    srand(time(0));
    grid g;
    g.creategrid(10, 10);
    g.placerandomelements();
    g.placecoinrandomly();
    g.print();
    g.sensepower();
    
    playermovement p(g);
    char choice;
    do {
        cout << "Enter move (w/a/s/d) or 'u' for undo: ";
        cin >> choice;
        switch (choice) {
            case 'w': p.upmove(); break;
            case 'a': p.leftmove(); break;
            case 's': p.downmove(); break;
            case 'd': p.rightmove(); break;
            case 'u': p.undofeature(); break;
            default: cout << "Invalid input!" << endl;
        }
        cout<<"Hint : "<<endl;
        g.sensepower();
        cout<<"Score : "<<score<<endl;
       cout<<"No of remaining moves are : " << p.noofmovesremaining<<endl;
        g.print();
       if (p.isGameOver()) {
            break;
        }
    } while (choice != 'q');
    
    return 0;
}
