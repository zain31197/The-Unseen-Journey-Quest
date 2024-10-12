#include <iostream>
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
    grid() 
    {
        head = NULL;
        rows=0;
        cols=0;
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
    
    playermovement(grid &g)
    {
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
    void leftmove()
    {
        if(position->left==NULL)
        {
            cout<<"invalid position"<<endl;
            return ;
        }
        if(position->left!=NULL)
        {
           
            position->data='#';
            position=position->left;
            position->data='P';
        }
    }
     void rightmove()
    {
        if(position->right==NULL)
        {
            cout<<"invalid position"<<endl;
            return ;
        }
        if(position->right!=NULL)
        {
           
            position->data='#';
            position=position->right;
            position->data='P';
        }
    }
    void upmove()
    {
        if(position->up==NULL)
        {
            cout<<"invalid position"<<endl;
            return ;
        }
        if(position->up!=NULL)
        {
           
            position->data='#';
            position=position->up;
            position->data='P';
        }
    }
    void downmove()
    {
        if(position->down==NULL)
        {
            cout<<"invalid position"<<endl;
            return ;
        }
        if(position->down!=NULL)
        {
           
            position->data='#';
            position=position->down;
            position->data='P';
        }
    }

    
};
int main() 
{
    grid g;
    g.creategrid(10, 10);
    g.placerandomelements();
    g.print();
    playermovement m(g);
    m.downmove();
    g.print();
    m.rightmove();
    g.print();
    m.leftmove();
    g.print();
    m.upmove();
    g.print();
    
    return 0;
}
