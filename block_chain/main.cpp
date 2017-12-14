//
//  main.cpp
//  block_chain
//
//  Created by shaswat satapathy on 15/11/17.
//  Copyright © 2017 shaswat satapathy. All rights reserved.
//

//========================================================================
//immutability in Blockchain
//========================================================================


#include <iostream>
#include "sha1.hpp"
#include <string.h>
#include <cstring>
#include <vector>
class Block;
Block *head;
using namespace std;
class Block
{
private:
    string prevhash;
    string tr;
    string total_hash;
    Block *next;
public:
    Block(Block *node  )
    {
        head = new Block;
        head->next=NULL;
        head->prevhash=sha1("FirstHash");
        head->tr="Very first tr";
        head->total_hash=sha1(prevhash+sha1(tr));
        cout<<"\t\t\tGenesis Block Created\n\n";
        
    }
    Block()
    {
        
    }
    Block* visit_last()
    {
        Block* temp= head;
        while(temp->next!=NULL)
            temp=temp->next;
        return temp;
        
    }
    
    void addtr(string tr)
    {
        
        Block *temp2 = visit_last();
        Block* new_node = new Block;
        new_node->next=NULL;
        new_node->tr=tr;
        
        new_node->prevhash=sha1(temp2->tr);
        new_node->total_hash=sha1(new_node->total_hash+sha1(tr));
        temp2->next=new_node;
        
    }
    void change()
    {
        string old;
        string new_val;
        cout<<"Enter old transaction: ";
        cin>>old;
        cout<<"Enter new transaction: ";
        cin>>new_val;
        Block *temp= head;
        while(temp->tr!=old)
            temp=temp->next;
        cout<<"\n Old Values : \n";
        cout<<temp->tr<<endl;
        cout<<temp->prevhash<<endl;
        cout<<temp->total_hash<<endl;
        cout<<"\n New Value :";
        cout<<new_val;
        if(sha1(prevhash+sha1(new_val))==total_hash)
        {
            cout<<"No change";
        }
        else
        {
            cout<<"\n You are changing the value \n";
            char choice;
            cout<<" Do you REALLY want to modify the entire Blockchain ???? : "<<"\t"<<endl;
            
            cin>>choice;
            if(choice=='y')
            {
                
                temp->tr=new_val;
                temp->total_hash=sha1(prevhash+sha1(new_val));
                string prevtranshash = temp->total_hash;
                string prevtrans=temp->tr;
                temp=temp->next;
                
                while(temp!=NULL)
                {
                    temp->prevhash=sha1(prevtrans);
                    temp->total_hash=sha1(sha1(temp->tr)+prevtranshash);
                    prevtranshash=temp->total_hash;
                    prevtrans=temp->tr;
                    temp=temp->next;
                }
                
            }
        }
    }
    void display()
    {
        Block* node = head;
        while(node!=NULL)
        {
            cout<<"Detail of block : \n"<<endl;
            cout<<"Present transaction detail:\t ";
            cout<<node->tr<<endl;
            cout<<"Previous hash: \t";
            cout<<node->prevhash<<endl;
            cout<<"Present  hash: \t";
            cout<<sha1(node->tr)<<endl;
            
            cout<<"Total hash: \t";
            cout<<node->total_hash<<endl;
            cout<<"\n\n";
            node=node->next;
        }
        
    }
};
int main()
{
    
    cout<<"\t ---------------------------------------------------------------\n"<<endl;
    cout<<"\t \t \tImpelmenting immutability in blockchain\n"<<endl;
    cout<<"\t ---------------------------------------------------------------\n\n\n"<<endl;
    Block ob(head) ;//genesis block created!
    int n;
    int i,j=1;
    char cho;
    string tr;
    cout<<"Enter the number of transactions you wish to enter: "<<"\t";
    cin>>n;
    
    for(i=0;i<n;i++)
    {
        cout<<"Enter transaction "<<j<<endl;
        j++;
        cin>>tr;
        ob.addtr(tr);
        ob.display();
    }
    cout<<"Do you want to modify a Transaction? : ";
    cin>>cho;
    switch (cho) {
        case 'y':
            ob.change();
            ob.display();
            cout<<"Thank you for your patience !!!"<<endl;
            break;
        case 'n':
            cout<<"Thank you for your patience !!!"<<endl;
            break;
        default:
           break ;
    }
   
    /*
     
    
     Block ob(head) ; //genesis
    string tr = "grape";
    ob.addtr(tr);
    string tr1 = "orange";
    ob.addtr(tr1);
    ob.display();
    ob.change("grape","grape");
    ob.display();
    */
}




