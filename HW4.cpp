#include<iostream>

using namespace std;

class team
{
    public:
        team()
        {
            elementNum=0;
            for(int i=0;i<1000;i++)
            {
            	element[i]=0;
			}
        }
        int element[1000];
        int elementNum;//How many element are in each team
};


class chainNode
{
    //friend class linkqueue;
public:
    chainNode(int element, chainNode* Next=0)
    {
        data=element;
        link=Next;
    }
    int data;
    chainNode* link;
};


class linkqueue
{
public:
    linkqueue()
    {
        front=0;
        rear=0;
    }
    chainNode* front;
    chainNode* rear;
    int isEmpty()
    {
        if(front==0)
        {
            return 1;
        }
        else{
            return 0;
        }
    }
    void push(int e)
    {
        if(isEmpty())
        {
            front=new chainNode(e, 0);
            rear=front;
        }
        else
        {
            rear->link=new chainNode(e, 0);
            rear=rear->link;
        }
    }
    void pop()
    {
        if(!isEmpty())
        {
            chainNode* delNode=front;
            front=front->link;
            delete delNode;
        }
    }

};

int main()
{
    while(1)
    {
        linkqueue queue;
        linkqueue output;
        team *teams=new team[1000];
        int teamNum;
        cin>>teamNum;
        if(teamNum==0) break;

        for(int i=0;i<teamNum;i++)
        {
            cin>>teams[i].elementNum;
            for(int j=0;j<teams[i].elementNum;j++)
            {
                cin>>teams[i].element[j];
            }
        }

        //Enqueue or Dequeue
        string str1;
        while(cin>>str1)
        {
            //stop
            if(str1.compare(0, 1, "S")==0) break;

            //dequeue
            if(str1.compare(0, 1, "D")==0)
            {
                if(!queue.isEmpty())
                {
                    output.push(queue.front->data);
                    queue.pop();
                }
            }

            //enqueue
            if(str1.compare(0, 1, "E")==0)
            {

            }
        }
    }//while end

}
