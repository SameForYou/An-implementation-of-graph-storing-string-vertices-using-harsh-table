#include<iostream>
using namespace std;

typedef struct Node
{
	string data;
	int wt;
	Node* next;
	Node* list;// the list is where the edge information excatly stored
}* Linkedlist;
	
Node* GetNewNode (string x,int wt)
{
	Node* new_node = new Node();
	new_node->data = x;
	new_node->wt = wt;
	new_node->next = new_node->list = NULL;
	return new_node;
}
	
Node* Insert (Node* root,string x,int wt)/* avoid same elements adding */
{
	if (root == NULL)
	{
		root = GetNewNode(x,wt);
		return root;
	}
	if (x == root->data)
	{
		return root;
	}
	root->next = Insert(root->next,x,wt);
	return root;
}

class graph
{
private:
	Linkedlist* L;
	int T_S;
	
public:
	graph()
	{
		T_S = 50;
		L = new Linkedlist[T_S];
		for (int i = 0; i < T_S; i++)
			L[i] = NULL;
	}
	/* harsh function */
	

	int HarshCode(string str)
	{
		int sum = 0;
		for (const char& c : str)
			sum += (int)c;
		return sum;
	}
	
	int getkey(string str)
	{
		int code = HarshCode(str);
		int key = code % T_S;
		return key;
	}
	/****************************/
	Node* getpos (string str) // return the address of the source edge 
	{
		int i = getkey (str);
		Node* p = L[i];
		while(p != NULL)
		{
			if (p->data == str)
			{
				return p;
			}
			p = p->next;
		}
		return NULL;
	}

	void addEdge(string str1,string str2,int wt)
	{
		int key = getkey(str1);
		L[key] = Insert (L[key],str1,wt);                         /* Insert the source */
		getpos(str1)->list = Insert(getpos(str1)->list,str2,wt);  /* Insert the dest and weight*/
	}
	
	void Delete_vertice (string str)
	{
		int i = getkey(str);
		if (L[i] == NULL)
		{
			cout<<"Wrong information\n";
			return;
		}
		if (L[i]->data == str)
		{
			Node* temp = L[i];
			L[i] = L[i]->next;
			free(temp);
			return;
		}
		
		Node* curr = L[i];
		Node* prev = NULL;
		while (curr != NULL)
		{
			if (curr->data == str)
			{
				prev->next = curr->next;
				free(curr);
				return;
			}
			prev = curr;
			curr = curr->next;
		}
		cout<<"Wrong information\n";
	}
	
	void Delete_Edge(string str1,string str2)
	{
		Node* root = getpos(str1);
		if (root == NULL)/* No str1 found */
		{
			cout<<"Wrong information\n";
			return;
		}
		
		Node* r = root->list;
		if (r->data == str2) /* delete the head node */
		{
			Node* temp = r;
			root->list = r->next;
			free(temp);
			if (root->list == NULL)/* remove the vertice if no other edges */
				Delete_vertice(str1);
			return;
		}
		
		Node* prev = NULL;
		Node* curr = r;
		while (curr != NULL) /* for the other node */
		{
			if (curr->data == str2)
			{
				prev->next = curr->next;
				free(curr);
				return;
			}
			prev = curr;
			curr = curr->next;
		}
		cout<<"Wrong information\n";
	}
	
	void find_neighbors(string source)
	{
		Node* root = getpos(source);
		if (root == NULL)
		{
			cout<<"Wrong vertex\n";
			return;
		}
		Node* curr = root->list;
		while (curr != NULL)
		{
			cout<<curr->data<<" ";
			curr = curr->next;
		}
		cout<<"\n";
	}
	
	void display ()
	{
		cout<<"\n";
		for (int i = 0 ;i < T_S; i++)
			if (L[i] != NULL)/* L[i] which affected the source keys store all the source with the same key value*/
			{
				Node* R = L[i];
				while (R != NULL)
				{
					Node* r = R->list; /* R->list stores all the destnation */
					cout<<"key "<<i<<"\tNode "<<R->data<<"\n";
					while (r != NULL)
					{
						cout<<"\tmakes an edge with : "<<" "<<r->data<<"\tweight is : "<<r->wt<<"\n";
						r = r->next;
					}
					R = R->next;
					cout<<"\n";
				}
			}
	}
	~graph()
	{
		free(L);
	}
};

void Menu ()
{
	cout<<"\n**************************************\n";
	cout<<"1.Display\t\t2.Add an edge\n3.Delete an edge\t";
	cout<<"4.Remove an vertex\n5.Find neighbors\t6.Exit\n";
}

int main ()
{
	system("Color 0E");

	graph g;
	g.addEdge("halfway","night",9);
	g.addEdge("cloud","solid",2);
	g.addEdge("halfway","deep",3);
	g.addEdge("halfway","sample",4);
	g.addEdge("cloud","twisted",7);
	g.addEdge("halfway","shadow",9);
	g.addEdge("spark","inside",8);
	g.addEdge("spark","lost",8);
	g.addEdge("around","broken",20);
	g.addEdge("fairytale","mercy",10);
	g.addEdge("fairytale","light",1);
	g.addEdge("fairytale","pretend",3);
	g.Delete_Edge("halfway","shadow");
	g.display();
}
