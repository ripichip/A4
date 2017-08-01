//********************************************************************************************
// Alex Shershnov
// 01/05/2017
// This is program showcases the use of circular doubly linked lists
//********************************************************************************************

/* Use the comments given in each routine to complete the following program */


#include <iostream>
#include<string>
#include<fstream>
using namespace std;

class Node;
typedef Node* NodePtr;

class CircularDLL;
class Node 
{
  friend class CircularDLL;
private:
  int stId;
  string stName;
  string stEmail;
  int stAge;
  NodePtr next;
  NodePtr prev;
public:
  Node();
  Node(int id, string n, string e, int a);
  
};

class CircularDLL
{
private:
  NodePtr  top;
  void destroy (NodePtr&);

public:
  CircularDLL();
  CircularDLL(const CircularDLL& source);
  ~CircularDLL();
  void insertDataFromFile();
  void print ();
  bool search (int);
  void insertAfterFirst (int id, string name, string email, int age);
  void insertBeforeFirst (int id, string name, string email, int age);
  void insertAfterLast (int id, string name, string email, int age);
  void insertBeforeLast (int id, string name, string email, int age);
  void remove (int);
  void copy (NodePtr top1, NodePtr& top2);
};
//--------------------------------------------
//--------------------------------------------
// the default constructor

Node::Node()
{
  stId = stAge = 0;
  stName = stEmail = " ";
  next = NULL;
  prev = NULL;
}
Node::Node(int id, string n, string e, int a)
{
  stId = id;
  stName = n;
  stEmail = e;
  stAge = a;
  next = NULL;
  prev = NULL;
}
CircularDLL::CircularDLL()
{
  top = NULL;
}
//--------------------------------------------
//--------------------------------------------
// the copy constructor
CircularDLL::CircularDLL(const CircularDLL& source)
{
  copy(source.top, top);
}
//--------------------------------------------
//--------------------------------------------
// the destructor
CircularDLL::~CircularDLL()
{
  destroy(top);
}

//--------------------------------------------
//--------------------------------------------
// Read a transaction file and insert the data into it
// after reading a set of data you can call any of the 
// insert functions to insert the node into the linked list 
/* use the following data to test your program
   76543Marymary@csusm.edu19
   98765Kathykathy@csusm.edu30
   16438Floraflora@csusm.edu25
   43260Peterpeter@csusm.edu29
   87590kimkim@csusm.edu31
*/
void CircularDLL::insertDataFromFile()
{
  string n, e;
  int id, a;
  ifstream in;
  in.open("Transaction.txt");
  in >> id >> n >> e >> a;
  insertBeforeFirst(id, n, e, a);
  while(!in.eof())
    {
      in >> id >> n >> e >> a;
      insertAfterLast(id, n, e, a);
    }  
}
//--------------------------------------------
//--------------------------------------------
// print the linked list
void CircularDLL::print ()
{
  NodePtr p = top;
  NodePtr temp = top;
  do
    {
      cout << p -> stId << " " << p -> stName << " " << p -> stEmail << " " << p -> stAge << endl;
      temp = temp -> next;
      p = p -> next;
    }while(temp != top);
}
//--------------------------------------------
//--------------------------------------------
// search for a particular student id in the list
bool CircularDLL::search (int id)
{
  NodePtr temp = top;
  do
    {
      if(temp -> stId == id)
	{
	  return true;
	}
      temp = temp -> next;
    }while(temp != top);
  return false;
}
//--------------------------------------------
//--------------------------------------------
// creates a node and insert the node on the top of the
// linked list but after the first node. For example if the
// list constains 1 <--> 20 <-->13 <--> 4 <--> 5 <--> 6 <--> (links to the first node which is 1)
// after inserting 10, we should get:
// list constains 1 <--> 10 <--> 20 <-->13 <--> 4 <--> 5 <--> 6 <--> (links to the first node which is 1)

void CircularDLL::insertAfterFirst (int id, string name, string email, int age)
{
  NodePtr newNode = new Node(id, name, email, age);
  NodePtr temp = top -> next;
  if(top != NULL)
    {
      top -> next = newNode;
      newNode -> next = temp;
      newNode -> prev = top;
      temp -> prev = newNode;
    }
}
//--------------------------------------------
//--------------------------------------------
// creates a node and insert the node on the top of the
// linked list before the first node. For example if the
// list constains 1 <--> 20 <-->13 <--> 4 <--> 5 <--> 6 <--> (links to the first node which is 1)
// after inserting 10, we should get:
// list constains 10 <--> 1 <--> 20 <-->13 <--> 4 <--> 5 <--> 6 <--> (links to the first node which is 10)

void CircularDLL::insertBeforeFirst (int id, string name, string email, int age)
{
  NodePtr newNode = new Node(id, name, email, age);
  if(top == NULL)
    {
      top = newNode;
      newNode -> next = top;
      newNode -> prev = top;
    }
  else
    {
      NodePtr temp = top;
      NodePtr prevNode = temp -> prev;
      top = newNode;
      newNode -> next = temp;
      temp -> prev = newNode;
      prevNode -> next = newNode;
      newNode -> prev = prevNode;
    }
}
//--------------------------------------------
//--------------------------------------------
// creates a node and insert the node on the bottom of the
// linked list after the last node. For example if the
// list constains 1 <--> 20 <-->13 <--> 4 <--> 5 <--> 6 <--> (links to the first node which is 1)
// after inserting 10, we should get:
// list constains 1 <--> 20 <-->13 <--> 4 <--> 5 <--> 6 <--> 10 <-->(links to the first node which is 1)

void CircularDLL::insertAfterLast (int id, string name, string email, int age)
{
  NodePtr temp = top;
  NodePtr newNode = new Node(id, name, email, age);
  if(temp != NULL)
    {
      while(temp -> next != top)
	{
	  temp = temp -> next;
	}
      temp -> next = newNode;
      newNode -> next = top;
      top -> prev = newNode;
      newNode -> prev = temp;
    }
  else
    {
      insertBeforeFirst(id, name, email, age);
    }
  
}
//--------------------------------------------
//--------------------------------------------
// creates a node and insert the node on the bottom of the
// linked list before the last node. For example if the
// list constains 1 <--> 20 <-->13 <--> 4 <--> 5 <--> 6 <--> (links to the first node which is 1)
// after inserting 10, we should get:
// list constains 1 <--> 20 <-->13 <--> 4 <--> 5 <--> 10 <--> 6 <--> (links to the first node which is 1)

void CircularDLL::insertBeforeLast (int id, string name, string email, int age)
{
  NodePtr newNode = new Node(id, name, email, age);
  if(top != NULL)
    {
      NodePtr temp = top -> prev;
      NodePtr temp2 = temp -> prev;
      temp -> prev = newNode;
      newNode -> prev = temp2;
      temp2 -> next = newNode;
      newNode -> next = temp;
    }
}
//--------------------------------------------
//--------------------------------------------
// removes a node from the list based on the given student id 
void CircularDLL::remove (int id)
{
  NodePtr searchNode = top;
  if(top !=NULL)
    {
      do
	{
	  if(searchNode -> stId == id)
	    {
	      NodePtr prevNode = searchNode -> prev;
	      NodePtr nextNode = searchNode -> next;
	      prevNode -> next = nextNode;
	      nextNode -> prev = prevNode;
	      delete searchNode;
	    }
	  searchNode = searchNode -> next;
	}while(searchNode != top);
    }
}
//--------------------------------------------
//--------------------------------------------
// copies one list into another
void CircularDLL::copy (NodePtr atop, NodePtr& btop)
{
  NodePtr a, b;
  if(atop != NULL)
    {
      btop = new(Node);
      btop -> stId = atop -> stId;
      btop -> stName = atop -> stName;
      btop -> stEmail = atop -> stEmail;
      btop -> stAge = atop -> stAge;
      a = atop;
      b = btop;
      while(a -> next != atop)
	{
	  b -> next = new(Node);
	  a = a -> next;
	  b = b -> next;
	  b -> stId = a -> stId;
	  b -> stName = a -> stName;
	  b -> stEmail = a -> stEmail;
	  b -> stAge = a -> stAge;
	}
       b -> next = btop;
    }
}       
//--------------------------------------------
// deallocate the nodes in a linked list
void CircularDLL::destroy(NodePtr& top) 
{
  NodePtr temp, curr;
  curr = top;
  do
    {
      temp = curr;
      curr = curr -> next;
      delete temp;
    }while(curr != top);
  top = NULL;
}
//--------------------------------------------

int main () 
{
  CircularDLL list1;
  list1.insertDataFromFile();
  cout << "First print:\n";
  list1.print();
  list1.insertAfterFirst (54321, "Jim", "jim@csusm.edu", 25);
  list1.insertBeforeFirst (54123, "Joe", "joe@csusm.edu", 35);
  cout << "\nSecond print:\n";
  list1.print();
  list1.insertAfterLast (63421, "Adam", "adam@csusm.edu", 20);
  list1.insertBeforeLast (66641, "Nancy", "nancy@csusm.edu", 27);
  cout << "\nThird print:\n";
  list1.print();
  bool  found = list1.search (12321);
  if (found)
    cout << "\nthe record was found" << endl;
  else
     cout << "\nthe record was not found" << endl;
  list1.remove (54321);
  cout << "\nFourth print:\n";
  list1.print();
  CircularDLL list2(list1);
  cout << "\nCopied linked list:\n";
  list2.print();
  return 0;
}
//--------------------------------------------
