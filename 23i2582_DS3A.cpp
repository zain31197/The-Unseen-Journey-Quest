#include <iostream>
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
class stack
{
    public:
    struct stacknode
    {
    node *value;
    stacknode *next;
    
    };
    stacknode *top;
    
    stack()
    {
        top=NULL;
    }
    void push(node *value)
    {
     stacknode *NN=new stacknode();
     NN->value=value;
     NN->next=top;
     top=NN;
    }
    node * pop()
    {
        if(top==NULL)
        {
            cout<<"Stack is empty"<<endl;
            return NULL ;
        }
        stacknode *temp=top;
        node *temppop=top->value;
        top=top->next;
        delete temp;
        return temppop;
    }
    node *TopNode()
    {
        if(top==NULL)
        {
            cout<<"Stack is empty"<<endl;
            return NULL;
        }
        return top->value;
    }
    bool empty()
    {
        return top==NULL;
    }

};

class grid {
public:
    node* head;
    int rows;
    int cols;
    int gamestartdistance;
    int currentdistance;
    int playerxaxix;
    int playeryaxix;
    int keyxaxix;
    int keyyaxix;

    grid() {
        head = NULL;
        rows = 0;
        cols = 0;
        gamestartdistance = 0;
        currentdistance = 0;
        playerxaxix=0;
        playeryaxix=0;
        keyxaxix=0;
        keyyaxix=0;
    }
    void setplayeraxix(int x,int y)
    {
        this->playerxaxix=x;
        this->playeryaxix=y;
    }
    int getkeyxaxix()
    {
        return keyxaxix;
    }
    int getkeyyaxix()
    {
        return keyyaxix;
    }
     void setkeyaxix(int x,int y)
    {
        this->keyxaxix=x;
        this->keyyaxix=y;
    }
    int getplayerxaxix()
    {
        return playerxaxix;
    }
    int getplayeryaxix()
    {
        return playeryaxix;
    }

    void creategrid(int rows, int cols) {
        if (rows == 0 || cols == 0) 
            return;
        this->rows = rows;
        this->cols = cols;
        head = new node('.');
        node* temp = head;
        node* prevrow = NULL;
        for (int i = 0; i < rows; i++) {
            node* rowhead = temp;
            for (int j = 1; j < cols; j++) {
                node* newNode = new node('.');
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
                node* nextRow = new node('.');
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
        //  player key Door Boomb1 Boomb2 Boomb3
        char elem[] = { 'P', '.', 'D', 'B','B' ,'B'};
        int size = 6;
        int randomRow, randomCol;
        node* targetNode;
        for (int i = 0; i < size; i++) {
            do {
                
                randomRow = rand() % rows;
                randomCol = rand() % cols;
                targetNode = getnode(randomRow, randomCol);
            } while (targetNode->data != '.');
            if(elem[i]=='P')
            {
            setplayeraxix(randomRow,randomCol);
            }
             if(elem[i]=='.')
            {
            setkeyaxix(randomRow,randomCol);
            }

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
            } while (targetNode->data != '.');
            targetNode->data = 'C';
        }
    }

    void clearcoins() {
        node* temp = head;
        while (temp != nullptr) {
            node* temp2 = temp;
            while (temp2 != nullptr) {
                if (temp2->data == 'C') {
                    temp2->data = '.';
                }
                temp2 = temp2->right;
            }
            temp = temp->down;
        }
    }

    // node* getkeylocation() {
    //     node* temp = head;
    //     while (temp != nullptr) {
    //         node* temp2 = temp;
    //         while (temp2 != nullptr) {
    //             if (temp2->data == 'K') {
    //                 return temp2;
    //             }
    //             temp2 = temp2->right;
    //         }
    //         temp = temp->down;
    //     }
    //     return nullptr;
    // }
    void printgamestartdistance()
    {
        cout<<"game sart distance : "<<gamestartdistance<<endl;
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
  
    int getgamestartdistance()
    {
        return gamestartdistance;
    }
    void cityblockdistanceformula() {
        // cout<<"key " <<keyxaxix<<" , "<<keyyaxix<<endl;
        currentdistance = abs(playerxaxix-keyxaxix) + abs(playeryaxix - keyyaxix);
        if (gamestartdistance == 0) {
            gamestartdistance = currentdistance;
        }
    }

    void sensepower() {
        cityblockdistanceformula();
        if (gamestartdistance >= currentdistance) {
            cout << "You are getting closer." << endl;
        } if (currentdistance > gamestartdistance) {
            cout << "You are getting farther." << endl;
        } 
        // cout<<"gamestartdistance : "<<gamestartdistance<<endl;
        // cout<<"current distance : "<<currentdistance<<endl;
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
    stack undo;
    vector<pair<int, int>> collectedCoins;
    int remainingundo;
    int noofmovesremaining;
    bool gameover;
    bool keystatus;
    int playerxaxix;
    int playeryaxix;
    int keyxaxix;
    int keyyaxix;
    playermovement(grid& g) {
        position = g.getplayerposition();
        noofmovesremaining=0;
        gameover=false;
        keystatus=false;
        this->playerxaxix=g.getplayerxaxix();
        this->playeryaxix=g.getplayeryaxix();
        this->keyxaxix=g.getkeyxaxix();
        this->keyyaxix=g.getkeyyaxix();
    }
    int getplayerxaxix()
    {
        return playerxaxix;
    }
    int getplayeryaxix()
    {
        return playeryaxix;
    }
    void setnoofmoves(int n)
    {
        this->noofmovesremaining=n;
    }
    int getremainingnoofmoves()
    {
        return noofmovesremaining;
    }
    void printplayeraxix()
    {
        cout<<"x"<<playerxaxix<<endl;
        cout<<"y"<<playeryaxix<<endl;
        
    }
    void setkeystatustrue()
    {
        this->keystatus=true;
    }
    bool getkeystatus()
    {
        return keystatus;
    }
    void setundovalues(int n)
    {
        this->remainingundo=n;
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
            gameover=true;
              position->data = '.';
        position = newposition;
        position->data = 'P';
            return;
        }
        if(newposition->data=='.'&&playerxaxix==keyxaxix&&playeryaxix==keyyaxix)
        {
            setkeystatustrue();
        }

       
        if(newposition->data=='D')
        {
            if(getkeystatus()==true)
            {
                cout<<"Congratulations you Found the key and enter the exit Door"<<endl;
                cout<<"GAME END"<<endl;
                calculatefinalscore();
                gameover=true;
                return;
            }
            if(getkeystatus()==false)
            {
                cout<<"You cannot enter the exit door without key"<<endl;
                return;
            }
        }
        if (remainingundo > 0) {
            undo.push(position);
        }
        if (newposition->data == 'C') {
            cout << "Coin collected!" << endl;
            score+=2;
            remainingundo++;
            collectedCoins.push_back({playerxaxix,playeryaxix});
        }
        position->data = '.';
        position = newposition;
        position->data = 'P';
    }
    void revealkeyaxix()
    {
        cout<<"Key was hidden at : "<<keyxaxix<<","<<keyyaxix<<endl;
    }
    void printcoinslocation()
    {
        if(collectedCoins.empty())
        {
            cout<<"No Coins are collected"<<endl;
            return ;
        }
        cout<<"Coins Collected at these locations"<<endl;
        for(const auto &coin:collectedCoins)
        {
            cout<<"("<<coin.first<<","<<coin.second<<")"<<" ";
        }
        cout<<endl;
    }
    void leftmove() {
        if (position->left == nullptr) {
            cout << "Invalid move!" << endl;
            return;
        }
        playeryaxix=playeryaxix-1;
        move(position->left);
    }

    void rightmove() {
        if (position->right == nullptr) {
            cout << "Invalid move!" << endl;
            return;
        }
         playeryaxix=playeryaxix+1;
        move(position->right);
    }

    void upmove() {
        if (position->up == nullptr) {
            cout << "Invalid move!" << endl;
            return;
        }
        playerxaxix=playerxaxix-1;
        move(position->up);
    }
int getundomoves()
{
    return remainingundo;
}
    void downmove() {
        if (position->down == nullptr) {
            cout << "Invalid move!" << endl;
            return;
        }
         playerxaxix=playerxaxix+1;
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
        position->data = '.';
        position = undo.TopNode();
        undo.pop();
        position->data = 'P';
        remainingundo--;
    }
      bool isGameOver() {
        return gameover;
    }
};

int main() {
    int level;
    cout<<"Please enter the level difficulty for EASY press 1 ,for MEDIUM Press 2 and for HARD press 3"<<endl;
    cin>>level;
    srand(time(0));
    grid g;
    if(level==1)
    {
        g.creategrid(10, 10);
    }
    else if(level==2)
    {
        g.creategrid(15, 15);
    }
    else 
    {
    g.creategrid(20, 20);
    }
    g.placerandomelements();
    g.placecoinrandomly();
    g.print();
    g.cityblockdistanceformula();
    // g.sensepower();
    g.printgamestartdistance();
    playermovement p(g);
     if(level==1)
    {
       p.setundovalues(6);
       int n=g.getgamestartdistance()+6;
       p.setnoofmoves(n);
    }
    else if(level==2)
    {
            p.setundovalues(4);
             int n=g.getgamestartdistance()+2;
       p.setnoofmoves(n);
    }
    else 
    {
        p.setundovalues(1);
         int n=g.getgamestartdistance();
       p.setnoofmoves(n);
    }
    char choice;
    char lastturn='\0';
    while(choice!='q')
    {
        cout << "Enter move (w/a/s/d) or 'u' for undo: ";
        cin >> choice;
        bool invalidmove=false;
        switch (choice)
        {
        case 'w' :
        if(lastturn=='s')
        {
            cout<<"You cannot move back without using undo feature"<<endl;
            invalidmove=true;
        }
        break;
         case 's' :
        if(lastturn=='w')
        {
            cout<<"You cannot move back up without using undo feature"<<endl;
            invalidmove=true;
        }
        break;
        case 'd' :
        if(lastturn=='a')
        {
            cout<<"You cannot move back left without using undo feature"<<endl;
            invalidmove=true;
        }
        break;
        case 'a' :
        if(lastturn=='d')
        {
            cout<<"You cannot move back right without using undo feature"<<endl;
            invalidmove=true;
        }
        break;
        default :
        break;
        }
        if(invalidmove)
        {
            continue;
        }
        switch (choice) {
            case 'w':
             p.upmove();
            lastturn='w';
             break;
            case 'a': 
            p.leftmove(); 
             lastturn='a';
            break;
            case 's': 
            p.downmove();
             lastturn='s';
            break;
            case 'd': 
            p.rightmove(); 
             lastturn='d';
            break;
            case 'u': 
            p.undofeature();
            lastturn='\0';
             break;
            default: cout << "Invalid input!" << endl;
        }
        cout<<"Remaining Undo Moves "<<p.getundomoves()<<endl;
        cout<<"Hint : "<<endl;
        int playerx=p.getplayerxaxix();
        int playery=p.getplayeryaxix();
        g.setplayeraxix(playerx,playery);
        g.sensepower();
        cout<<"Score : "<<score<<endl;
       cout<<"No of remaining moves are : " << p.noofmovesremaining<<endl;

       cout<<"Key Status : ";
       if(p.getkeystatus()==0)
       {
        cout<<"NOT FOUND"<<endl;
       }
       else 
       {
        cout<<"FOUND"<<endl;
       }
        g.print();
       if (p.isGameOver()) {
        cout<<"Game is Over!"<<endl;
        p.printcoinslocation();
        p.calculatefinalscore();
        p.revealkeyaxix();
            break;
        }
    } 
    
    return 0;
}
