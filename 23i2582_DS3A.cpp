#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
using namespace std;

class node 
{
public:
    char data;
   node *down;
   node *up;
   node *left;
   node *right;
    
    node(char data) 
    {
        this->data = data;
      this->down=NULL;
      this->left=NULL;
      this->up=NULL;
      this->right=NULL;
    }
};

class grid 
{
public:
    node *head;
    int rows;
    int cols;
    int gamestartdistance;
    int currentdistance;
    grid() 
    {
        head = NULL;
        rows=0;
        cols=0;
        gamestartdistance=0;
        currentdistance=0;
    }
    void creategrid(int rows, int cols) 
    {
        if (rows == 0 || cols == 0) 
        return;
        this->rows=rows;
        this->cols=cols;
        head = new node('#');  
        node* temp = head;     
        node* prevrow = NULL;  
        for (int i = 0; i < rows; i++) 
        {
            node* rowhead = temp;  
            for (int j = 1; j < cols; j++) 
            {
                node* newNode = new node('#');
                temp->right = newNode;
                newNode->left = temp;
                temp = temp->right;
            }
            
            if (prevrow) 
            {
                node* tempupper = prevrow;
                node* templower = rowhead; 
                while (tempupper && templower) 
                {
                    tempupper->down = templower;
                    templower->up = tempupper;
                    tempupper = tempupper->right;
                    templower = templower->right;
                }
            }
            if (i < rows - 1) 
            {
                node* nextRow = new node('#');
                rowhead->down = nextRow;
                nextRow->up = rowhead;
                temp = nextRow;
                prevrow = rowhead;
            }
        }
    }
    
    node *getnode(int rows,int cols)
    {
        node *temp=head;
        for(int i=0;i<rows;i++)
        {
            temp=temp->down;
        }
        for(int j=0;j<cols;j++)
        {
            temp=temp->right;
        }
        return temp;
    }
    void placerandomelements()
    {
          srand(time(0));
          char elem[]={'P', 'K', 'D', 'C', 'B'};
          int size=5;
             int randomRow, randomCol;
            node* targetNode;
           for(int i=0;i<size;i++)
           {
            do {
                randomRow = rand() % rows;
                randomCol = rand() % cols;
                targetNode = getnode(randomRow, randomCol);
            } while (targetNode->data != '#');

            targetNode->data = elem[i];
        }
    }
    node *getkeylocation()
    {
        node *temp=head;
        node *temp2=head;
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
            if(temp2->data=='K')
            {
            return temp2;
            }
            temp2=temp2->right;
            }
        temp=temp->down;
        temp2=temp;
        }
        return  NULL;// key missing
    }

     node *getplayerposition()
    {
        node *temp=head;
        node *temp2=head;
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
            if(temp2->data=='P')
            {
            return temp2;
            }
            temp2=temp2->right;
            }
        temp=temp->down;
        temp2=temp;
        }
        return  NULL;// nahi mila kuch
    }
    void cityblockdistanceformula()
    {
        node *key=getkeylocation();
        node *playerloc=getplayerposition();
     
        node *temp=head;
        node *temp2=head;
        int playerxaxix=0;
        int playeryaxix=0;
        int keyxaxix=0;
        int keyyaxix=0;
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
            if(temp2==key)
            {
            keyxaxix=i;
            keyyaxix=j;
            }
            if(temp2==playerloc)
            {
                playerxaxix=i;
                playeryaxix=j;
            }
            temp2=temp2->right;
            }
        temp=temp->down;
        temp2=temp;
        }
    currentdistance = abs(playerxaxix - keyxaxix) + abs(playeryaxix - keyyaxix);
    if (gamestartdistance == 0)
    {
        gamestartdistance = currentdistance;
    }

    }

    void sensepower()
    {
        cityblockdistanceformula();
        // cout<<"Game start Distance"<<gamestartdistance<<endl;
        // cout<<"Current Distance"<<currentdistance<<endl;
        if(gamestartdistance>currentdistance)
        {
            cout<<"Your are getting closer"<<endl;
        }
        else if (currentdistance>gamestartdistance)
        {
            cout<<"Your Are getting Futher"<<endl;
        }
        else 
        {
            cout<<"your are at the same distance noob"<<endl;
        }
         gamestartdistance = currentdistance; // Update gamestartdistance for next comparison.
    }
    
    void print() 
    {
        node* row = head;
        while (row != nullptr) 
        {
            node* temp = row;
            while (temp != nullptr) 
            {
                cout << temp->data << " ";
                temp = temp->right;
            }
            
            cout << endl;
            row = row->down;
        }
        cout<<endl;
    }
};
class playermovement {
    public:
    node *position;
    stack <node*> undo;
    int remainingundo;
    playermovement(grid &g)
    {
        remainingundo=5;
        for(int i=0;i<g.rows;i++)
        {
            for(int j=0;j<g.cols;j++)
            {
                node *temp=g.getnode(i,j);
                if(temp->data=='P')
                {
                    position=temp;
                    return ;
                }
            }
        }
    }
    void move(node *newposition)
    {
        if(remainingundo>0)
        {
            undo.push(position);
        }
        position->data = '#';
        position = newposition;
        position->data = 'P';
    }
    void leftmove()
    {
        if(position->left==NULL)
        {
            cout<<"invalid position"<<endl;
            return ;
        }
        move(position->left);
    }
     void rightmove()
    {
        if(position->right==NULL)
        {
            cout<<"invalid position"<<endl;
            return ;
        }
          move(position->right);
    }
    void upmove()
    {
        if(position->up==NULL)
        {
            cout<<"invalid position"<<endl;
            return ;
        }
          move(position->up);
    }
    void downmove()
    {
        if(position->down==NULL)
        {
            cout<<"invalid position"<<endl;
            return ;
        }
          move(position->down);
    }
void undofeature()
{
    if(!undo.empty()&&remainingundo>0)
    {
        node *prevpos=undo.top();
        undo.pop();
        position->data='#';
        position=prevpos;
        position->data='P';
        remainingundo--;
         cout << "Undo successful. Remaining undos: " << remainingundo << endl;
        } else {
            cout << "No more undos available!" << endl;
        }
    
}
    
};
int main() 
{
    grid g;
    g.creategrid(10, 10);
    g.placerandomelements();
    g.print();
    g.cityblockdistanceformula();
    playermovement m(g);
    m.downmove();
    g.sensepower();
    g.print();
    m.rightmove();
    g.sensepower();
    g.print();
    m.leftmove();
    g.sensepower();
    g.print();
    m.upmove();
    g.sensepower();
    g.print();
    m.undofeature();
    g.print();
    return 0;
}
