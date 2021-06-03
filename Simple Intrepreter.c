#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char key[10];
    double value;
}item;

item H[50];
int count=0;
//Inserts the inputs of the file into an array of items(keys and values)
void insertHeap(item it){
    count++;
    H[count]=it;
}
//Sorts the array of items by value ascendingly
void heapSort(){
    int i;

    for(i=count/2;i>=1;i--)  //Creates a max heap from the array
        maxHeapify(i,count);

    for(i=count;i>=1;i--){  //sorts the array by reptitively swapping last element with first element(largest value) and then deleting it from the heap and fixes the new heap

        int temp1= H[1].value;
            char temp2[10]="";
            strcpy(temp2,H[1].key);
            H[1] = H[i];
            H[i].value=temp1;
            strcpy(H[i].key,temp2);
    maxHeapify(1,i-1);

    }
}
//takes and index and fixes the node at this index
void maxHeapify(int i,int count){
int l = left(i);
int r=right(i);

int max=0;
if(l<=count && H[l].value>H[i].value)
    max=l;
    else max=i;
 if(r<=count && H[r].value>H[max].value)
        max=r;

 if(max!=i){
    int temp1= H[max].value;
            char temp2[10]="";
            strcpy(temp2,H[max].key);
            H[max] = H[i];
            H[i].value=temp1;
            strcpy(H[i].key,temp2);
             maxHeapify(max,count);
 }



}
int left(int i)
{
    int j=i*2;
    return j;
}
int right(int i)
{
    int j=i*2+1;
    return j;
}
int parent(int i){
     int j=(i/2);
    return j;

}
/*void heapifyUp(int i){

if(i!=1){
 int p = parent(i);
    if( H[p].value < H[i].value ){
            int temp1= H[p].value;
            char temp2[10]="";
            strcpy(temp2,H[p].key);
            H[p] = H[i];
            H[i].value=temp1;
            strcpy(H[i].key,temp2);



        heapifyUp(p);
    }

}
}*/
//*****************************BST IMPLEMENTATION********************************//
typedef struct
{
    char  *key;
    double value;
    struct  Node* left;
    struct Node*right;
} Node;

Node* newNode(char *key,double v)
{
    Node* n=malloc(sizeof(Node));
    n->key=malloc(sizeof(char));
    n->value=v;
    strcpy(n->key,key);
    n->left=NULL;
    n->right=NULL;
    return n;
}

Node*insert(Node* root,char *key,double value)
{
    if(root==NULL)
        return newNode(key,value);
    else if(strcasecmp(key,root->key)==0)
    root->value=value;
    else if(strcasecmp(key,root->key)<0)
        root->left= insert(root->left,key,value);
    else
        root->right=insert(root->right,key,value);
    return root;
}
Node* searhRec(Node* root,double x)
{
    if(root==NULL)
        return NULL;
    else if (root->value==x)
        return root;
    else if (x<root->value)
        return searhRec(root->left,x);
    else
        return searhRec(root->right,x);
}

double search(Node* root,char *key)
{

    while(root)
    {

        if(strcasecmp(key,root->key)==0)
            return root->value;

        else if (strcasecmp(key,root->key)<0)
            root=root->left;
        else
            root=root->right;
    }
    return 0;
}
void inOrder(Node* root)
{
    if(root)
    {
        inOrder(root->left);
        printf("%s = %0.2f\n",root->key,root->value);
        inOrder(root->right);
    }

}

//**************************************STACKS IMPLEMENTATION WITH ARRAYS****************************************//
typedef union
{
    float fData;
    char  cData;
} Item;
/*
*
*/
typedef struct
{
    int top;

    Item items[1000];

} Stack;
/*
*
*/
Stack * initialize()
{
    Stack *s=malloc(sizeof(Stack));
    s->top=0;
    return s;
}
/*
*
*/
int isEmpty(Stack *s)
{
    if  (s->top==0)
        return 1;
    return 0;
}
/*
*
*/
Item top(Stack *s)
{
    return s->items[s->top-1];
}
/*
*
*/
Item pop(Stack *s)
{
    return s->items[--s->top];
}
/*
*
*/
void push(Stack *s, Item val)
{
    s->items[s->top++]=val;
}
/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME single-digit operands
* ASSUME ^*+-/ operators
*/


int priority (char c) //determines the priority of the operator
{
    if(c=='*'||c=='/')
        return 1;
    else if(c=='+'||c=='-')
    {

        return 0;
    }

    else if(c=='^')
        return 2;

    else
        return -1;

}
void infixToPostfix(char* infix, char* postfix,Node* root)
{
    Stack *s = initialize();
    Item in;
    int i;
    int k=0;

   for(i=0;i<strlen(infix);){
        char str[]="";
        str[1]='\0';
        int j=0;
        int flag = 0; //

//neglects spaces in the infix expression and puts it in a string
if(infix[i]==' ')
{
      i++;
    continue;
}

//checks if there is a number(multi digit-float) and puts it in a string
   while(isdigit(infix[i]) || infix[i]=='.')
   {   flag=1;
       str[j++]=infix[i++];
   }

//checks if there is a negative number and puts it in a string
   if( infix[i]=='-' && isdigit(infix[i+1]) && (isdigit(infix[i-1])==0) && (isalpha(infix[i-1])==0))
{
    while (isdigit(infix[i]) || infix[i]== '-'  || infix[i]=='.' ){
       flag=1;
       str[j++]=infix[i++];
    }

   }

//checks if there is a variable and puts its name in a string
    while(isalpha(infix[i]))
   {    flag=1;
       str[j++]=infix[i++];
   }
//if not any of the above it just puts the character in a string
 if (!flag)
 str[0]=infix[i++];


//performs the infix to postfix operations using stacks
        if(str[0]=='(')
        {
            in.cData = str[0];
            push(s, in);
        }

        else   if(str[0]==')')
        {
            while(top(s).cData!= '(')
            {
                postfix[k++] = pop(s).cData;
                postfix[k++] = ' ';
            }
            pop(s);
        }
        else if(priority(str[0])==1||priority(str[0])==0||priority(str[0])==2)
        {
            if(str[0]=='-' && isdigit(str[1]))
            { int n=0;
                while (isdigit(str[n]) || str[n]== '-'  || str[n]=='.' )
                    postfix[k++]=str[n++];

                postfix[k++] = ' ';
            }

            else if (isEmpty(s))
            {

                in.cData = str[0];
                push(s, in);
            }
            else
            {
                while(priority(top(s).cData)>=priority(str[0]))
                {
                    postfix[k++]=pop(s).cData;
                    postfix[k++] = ' ';
                }
                in.cData = str[0];
                push(s,in);
            }

        }
        else
        {

               if(isdigit(str[0])){
                strcat(postfix,str);
               k=k+strlen(str);
               }

//gets the value of the variable from the BST
            if(isalpha(str[0])){

               double value=search(root,str);
               char output[10];
               snprintf(output,50,"%0.2f",value);
               strcat(postfix,output);
               k=k+strlen(output);

            }


            postfix[k++] = ' ';


        }



    }
    while(!isEmpty(s))
    {
        postfix[k++]  = pop(s).cData;
        postfix[k++] = ' ';
    }
    postfix[k] = '\0';


}

/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
* ASSUME single-digit operands
*/
isDigit(char c)
{
    if(c>='0'&&c<='9')
        return 1;
    else
        return 0;

}
int isOperator(char c)
{
    switch (c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return 1;
        default:
            return 0;
    }
}
int isNegative(char *c)
{

    if(c[0]=='-' && isdigit(c[1]))
        return 1 ;
    else
        return 0;
}
Item calculate(float op1,float op2, char c)
{
    float result;
    switch (c)
    {
        case '+':
            result = op2+op1;
            break;
        case '-':
            result = op2-op1;
            break;
        case '*':
            result = op2*op1;
            break;
        case '/':
            result = op2/op1;
            break;
        case '^':
            result = pow(op2,op1);
            break;
    }
    Item it;
    it.fData = result;
    return it;
}
float evaluatePostfix(char* postfix)
{


    Stack *s = initialize();
    Item operand[2];
    Item Operator,pf;
    char *str = strtok(postfix," ");

    int i=0;
    while(str != NULL)
    {
        if(isDigit(str[0]))
        {

            pf.fData = atof(str);
            push(s,pf);
        }
        else if (isNegative(str))
        {
            pf.fData = atof(str);
            push(s,pf);
        }
        else if(isOperator(str[0]))
        {
            operand[0].fData = pop(s).fData;
            operand[1].fData = pop(s).fData;
            push(s,calculate(operand[0].fData,operand[1].fData,str[0]));


        }

        str = strtok('\0'," ");
    }
    return pop(s).fData;
}

//parses the input file into the BST
Node*  loadFile(char *file){
Node* root = NULL;
FILE*fp=fopen(file,"r");
char line[150];
item it;

while(!feof(fp)){
   char key[]=" ";
   double value;

   fgets(line,150,fp);
   char *token;
   token = strtok(line,"= "); //tokenizes each line of the input file into two tokens(variable name - infix expression)
   strcpy(key,token);
   token = strtok(NULL,"");

   if(token[strlen(token)-1]=='\n')
   token[strlen(token)-1]='\0';

  char postfixExpr[256] = "";
  infixToPostfix(token, postfixExpr,root); //passes the infix expression to functions to get the postfix expression and evaluates it
  double result = evaluatePostfix(postfixExpr);

  root=insert(root,key,result);
 strcpy(it.key,key);
  it.value=result;

  insertHeap(it);



}


return root;
}



int main()
{ int i=0;
    printf("PLEASE ENTER THE NAME OF THE FILE YOU WANT TO LOAD\n");
    char file[10];
    printf("FILE NAME:  ");
    scanf("%s",file);
    strcat(file,".txt");
    Node* root = loadFile(file);
    printf("\n\nIN ORDER TRAVERSAL\n");
    printf("------------------------\n");
    inOrder(root);
    printf("\n");
    heapSort();
    printf("SORTED VALUES BY HEAP SORT ALGORITHM\n");
    printf("------------------------\n");
    for(i=1;i<count+1;i++)
    printf("%s = %0.2f\n",H[i].key,H[i].value);


    return 0;
}
