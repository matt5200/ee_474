#include <Arduino.h>

// Doubley Linked List

// Define TCB struct, holds task 
// and task data
typedef struct TCB {
  void (*myTask)(void*);
  void* taskDataPtr;
} TCB; 



TCB a;
TCB b;
TCB c;
TCB d;
TCB e;
// Solar Panel Control
TCB f;
// Console Key Pad
TCB h;
// Battery Temp
TCB l;
TCB m;
// Pirate Detection
TCB n;
// Pirate Management
TCB o;
// Command Task
TCB p;
// Earth Task
TCB q;
// Remote  Data Computer
TCB r;
// self destruct
TCB s;
// t_secret_game
TCB t;


// Define NodeTCB, holds TCB,
// next and prev node pointers
typedef struct NodeTCB {
        TCB* func;
        struct NodeTCB* prev;
        struct NodeTCB* next;
} NodeTCB;

// Doubley Linked List methods
int currentLength;
void deleteNode(NodeTCB** front,NodeTCB** back, int index);
void insert(NodeTCB** front,NodeTCB** back, TCB* newNode2);
TCB removeNode(NodeTCB** front,NodeTCB** back);
TCB* getN(NodeTCB** front,NodeTCB** back, int index);
NodeTCB* getNode(NodeTCB** front,NodeTCB** back,int index);

// Insert node to doubley linked list
 void insert(NodeTCB** front,NodeTCB** back, TCB* newNode2) {
      NodeTCB* newNode = (NodeTCB*)malloc(sizeof( NodeTCB));
      newNode->func = (TCB*)malloc(sizeof(TCB));
      *newNode->func = *newNode2;
        if (currentLength == 0) {
           (*front) = newNode;
           (*back) = newNode;
          delay(100);
        } else if (currentLength == 1) {
            (*front)->next = newNode;
            newNode->prev = *front;
            *back = newNode;
        }   else {
            (*back)->next = newNode;
            newNode->prev = *back;
            *back = newNode;
        }
        currentLength++;
    }

// Remove node from back of doubley linked list
    TCB removeNode(NodeTCB** front,NodeTCB** back){
        NodeTCB* last = *back;
        Serial.println("here 5");
        if (currentLength > 1) {
            *back = last->prev;
             free((*back)->next);
        }
        else {
           *back = NULL;
           *front = NULL;
        }
        currentLength--;
        return *last->func;
    }

// Delete node from index of list
   void deleteNode(NodeTCB** front,NodeTCB** back, int index) {
        if (index == currentLength - 1) {
            removeNode(front, back);
            return;
        }
        NodeTCB* rem = getNode(front, back, index);
        if (index == 0) {
            *front = (*front)->next;
            free(rem);
            (*front)->prev = NULL;
        } else {
            NodeTCB* behind = getNode(front, back, index - 1);
            NodeTCB* inFront = getNode(front, back, index + 1);
            behind->next = inFront;
            inFront->prev = behind;
            free(rem);
            free(rem);
        }
        currentLength--;
        return;
    }
 
     TCB* getN(NodeTCB** front,NodeTCB** back, int index) {
        return (getNode(front, back, index))->func;
    }

// Get node from location in doubley linked list
 NodeTCB* getNode(NodeTCB** front,NodeTCB** back,int index) {
            NodeTCB* result = *front;
            for (int i = 0; i < index; i++) {
                result = (result->next);
            }
            delay(1000);
            return result;
        }
        
NodeTCB* front = NULL; 
NodeTCB* back = NULL;
    
