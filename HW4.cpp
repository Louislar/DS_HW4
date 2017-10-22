#include<iostream>
#include<fstream>
#include<string>
#include<string.h>

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
    void insert(int e, chainNode* c)//insert behind node c
    {
        if(!isEmpty())
        {
            chainNode* temp=new chainNode(e, c->link);
            if(c==rear)
            {
                rear=temp;
            }
            c->link=temp;
        }
    }

};

int main()
{
    //input file
    ifstream ifs;
    string str;
    cout<<"Input file name: ";
    cin>>str;
    char* cstr=new char [str.length()+1];
    strcpy(cstr, str.c_str());
    ifs.open(cstr, ios::in);


    int k=0;
    while(1)
    {
        linkqueue queue;
        linkqueue output;
        team *teams=new team[1000];
        int teamNum;
        ifs>>teamNum;
        if(teamNum==0) break;

        for(int i=0;i<teamNum;i++)
        {
            ifs>>teams[i].elementNum;
            for(int j=0;j<teams[i].elementNum;j++)
            {
                ifs>>teams[i].element[j];
            }
        }

        //Enqueue or Dequeue
        string str1;
        while(ifs>>str1)
        {
            //stop
            if(str1.compare(0, 1, "S")==0) break;

            //dequeue
            if(str1.compare(0, 1, "D")==0)
            {
                if(!queue.isEmpty()){
                output.push(queue.front->data);
                queue.pop();
                }
            }

            //enqueue
            if(str1.compare(0, 1, "E")==0)
            {
                int enqueueNum;
                int enqueueNumTeamIndex;
                ifs>>enqueueNum;

                //find which team enqueueNum is in
                for(int i=0;i<teamNum;i++)
                {
                    int temp=0;
                	for(int j=0;j<teams[i].elementNum;j++)
                	{
                		if(teams[i].element[j]==enqueueNum)
                		{
                			enqueueNumTeamIndex=i;
                			temp=1;
                			break;
						}
					}
					if(temp) break;
				}

                // find if there are any number in queue
				// which is in the same team with enqueueNum
				chainNode* sameTeamNum;
				int sameTeamNumExist=0;
				{
				    chainNode* currentPointer=queue.front;
				    while(currentPointer!=0)
                    {
                        for(int i=0;i<teams[enqueueNumTeamIndex].elementNum;i++)
                        {
                           if(teams[enqueueNumTeamIndex].element[i]==currentPointer->data)
                           {
                               sameTeamNum=currentPointer;
                               sameTeamNumExist=1;
                           }
                        }
                        if(currentPointer->link==0) break;
                        currentPointer=currentPointer->link;
                    }
				}

				//execute
				if(sameTeamNumExist!=0)
                {
                    queue.insert(enqueueNum, sameTeamNum);
                }
                else
                {
                    queue.push(enqueueNum);
                }

                //test
                /*cout<<"queue: "<<endl;
                chainNode* test=queue.front;
                while(test!=0)
                {
                    cout<<test->data<<endl;
                    test=test->link;
                }
                cout<<"enqueueNum: "<<enqueueNum<<endl;
                cout<<"enqueueNumTeamIndex: "<<enqueueNumTeamIndex<<endl;
                if(sameTeamNumExist!=0)
                cout<<"sameTeamNum: "<<sameTeamNum->data<<endl;
                cout<<endl;*/

            }//enqueue if end
        }//while enqueue or dequeue end

        //output
        cout<<"Scenario #"<<++k<<endl;
        chainNode* out=output.front;
        while(out!=0)
        {
            cout<<out->data<<endl;
            out=out->link;
        }
        cout<<endl;

    }//while end

}
