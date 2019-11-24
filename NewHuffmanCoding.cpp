#include <iostream>
#include <fstream>
#include <cmath> 
using namespace std;

class listBinTreeNode{
	public:
	string chStr;
	int prob;
	string code;
	listBinTreeNode*next;
	listBinTreeNode*left;
	listBinTreeNode*right;
	
	listBinTreeNode(){
		chStr="dummy";
		prob=0;
		code="";
		next=NULL;
		left=NULL;
		right=NULL;	
	}//dummyNode
	
	listBinTreeNode(string a,int p){
		chStr=a;
		prob=p;
		code="";
		next=NULL;
		left=NULL;
		right=NULL;	
	}//constructLinkedList chStr,prob
	
	listBinTreeNode(string a,int p, string c,listBinTreeNode* l,listBinTreeNode* r){
		chStr=a;
		prob=p;
		code=c;
		next=NULL;
		left=l;
		right=r;
	}//constructBinTree
	 
	void printNode(listBinTreeNode*T,ostream& outFile2){\
		outFile2<<" "<<T->chStr<<", "<<T->prob<<", "<<T->code<<" ";
		if(T->next!=NULL){		
	 	   outFile2<<","<<T->next->chStr;				 	
		}
		else if(T->left!=NULL){
			outFile2<<","<<T->left->chStr;
		}
		else if(T->right!=NULL){
			outFile2<<","<<T->right->chStr;
		}
		return;
	}
};

class HuffmanLListTree{
	public:
		
	listBinTreeNode* listHead;
	listBinTreeNode* root;
	
	HuffmanLListTree(){
		listBinTreeNode* dummyNode = new listBinTreeNode();       
        listHead=dummyNode; 
	}
	
	void constructLinkedList(ifstream& inFile,ostream& outFile1){		
		string chStr; int prob;
	    while(inFile>>chStr>>prob){  
	    	listBinTreeNode*spot = findSpot(listHead,prob);
	        listBinTreeNode*a= new listBinTreeNode(chStr,prob);			
	    	insertNewNode(spot,a);	
			printList(outFile1);	
	   }		   
	   inFile.close();		
	}//constructLinkedList,step2,outFile1
	
	void constructBinTree(ostream&outFile2){
		listBinTreeNode* n=listHead->next;
		while(n!=NULL&&n->next!=NULL){											
	       	listBinTreeNode* a= new listBinTreeNode(n->chStr+n->next->chStr, n->prob+n->next->prob,"", n,n->next); 			   
            a->printNode(a,outFile2);
            outFile2<<endl;
            listBinTreeNode* spot =findSpot(listHead, a->prob);
            insertNewNode(spot,a); 
            listHead->next=listHead->next->next->next;
            printList(outFile2);
            n=listHead->next; 		        
       }     
       root=listHead->next;
	}//constructBinTree,step3,outFile2
	
	void constructCode(listBinTreeNode*T,string code,ostream&outFile3){
	     if(T==NULL){
	     	cout<<"This is an empty tree!"<<endl;
	     	exit(0);
		 }	
		 if(T->left==NULL&&T->right==NULL){
		 	T->code=code;
		 	outFile3<<T->chStr<<" ,"<<T->code<<endl;
		 }
		 else {
		    	constructCode (T->left, code+"0",outFile3);
	            constructCode (T->right, code+"1",outFile3); 
	     }
	} //constructCode,step4,outFile3
	
	void preOrder(listBinTreeNode*T, ostream&outFile4){
		 if(T==NULL){
		 	return;
		 }
		 T->printNode(T,outFile4);outFile4<<endl;
		 preOrder(T->left,outFile4);
		 preOrder(T->right,outFile4);
	}//preOrder traversals of the Huffman binary tree,outFile4
	
	void inOrder(listBinTreeNode*T, ostream&outFile4){
    	if(T==NULL){
		 	return;
		}					
		 inOrder(T->left,outFile4);
	    T->printNode(T,outFile4);
	    outFile4<<endl;
		inOrder(T->right,outFile4);
	}//inOrder traversals of the Huffman binary tree,outFile4
	
	void postOrder(listBinTreeNode*T, ostream&outFile4){
		if(T==NULL){
		 	return;
		}
		postOrder(T->left,outFile4);		
	    postOrder(T->right,outFile4);
		T->printNode(T,outFile4);
		outFile4<<endl;		 
	}//postOrder traversals of the Huffman binary tree,outFile4
	
	listBinTreeNode* findSpot(listBinTreeNode* listHead, int prob){
		listBinTreeNode*spot =listHead;
		
		while( ((spot->next)!=NULL) && ((spot->next->prob)<prob) ){		
	    	if( ((spot->next)!=NULL) && ( (spot->next->prob)<prob) ){
		    	spot=spot->next;
		    }
	    	else return NULL;
      	}
		return spot;		
	}//findSpot

   void insertNewNode(listBinTreeNode* spot,listBinTreeNode* newNode){
   	     listBinTreeNode* s = findSpot(listHead,newNode->prob);
   	     if(s!=NULL){
   	       newNode->next=s->next;
		   s->next=newNode;	
		 }
   }//insertNewNode
   
   bool isEmpty(){
   	    return root==NULL;
   }
   
   void printList(ostream&outFile){  	 
        outFile<<"ListHead-->";   
        listBinTreeNode * ct = listHead; 
        while(ct!=NULL&&ct->next!=NULL){ 
   	          outFile<<"("<<ct->chStr<<","<<ct->prob<<","<<ct->next->chStr<<")"<<"-->";
   	          ct=ct->next;
        }    
        outFile<<"("<<ct->chStr<<","<<ct->prob<<",NULL)-->"<<"NULL"<<endl;
   } //step2 outFile1+step3 outFile2
}; //HuffmanLListTree

int main(int argc, char* argv[]){
	ifstream inFile;	
	inFile.open(argv[1]); 
	ofstream outFile1;
	outFile1.open(argv[2]);
	ofstream outFile2;
	outFile2.open(argv[3]);
	ofstream outFile3;
	outFile3.open(argv[4]);
	ofstream outFile4;
	outFile4.open(argv[5]);
	
	HuffmanLListTree* t = new HuffmanLListTree();
	t->constructLinkedList(inFile,outFile1);		
	t->constructBinTree(outFile2);		
	t->constructCode(t->root,"",outFile3);
	
	outFile4<<"PreOrder:"<<endl<<endl;	
	t->preOrder(t->root,outFile4);
	outFile4<<endl;
	
	
	outFile4<<"InOrder:"<<endl<<endl;
	t->inOrder(t->root,outFile4);
	outFile4<<endl;
	
	outFile4<<"PostOrder:"<<endl<<endl;
	t->postOrder(t->root,outFile4);
	outFile4<<endl;
	
	inFile.close(); 
	outFile1.close();
	outFile2.close();
	outFile3.close();
	outFile4.close();	
	return 0;

} 
