#include <iostream>
class node{
	public:
		node* parent;
		node* left;
		node* right;
		int value;
		void extend_tree();
		void generate_tree(int depth);
		int get_value();
		int depth_first();
	node(int value, node* parent){
		this -> parent = parent;
		this -> value = value;
	};
};
int node::get_value(){
	//returns value stored in the node
	return(this -> value);
}
void node::extend_tree(){	
	//creates left and right child nodes. left value is parent+1, right value is parent+2
	this -> left = new node(this -> value+1, this);
	this -> right = new node(this -> value+2, this);
}
void node::generate_tree(int depth){
	//recursively calls the extend_tree method to generate a tree of specified depth
	if(depth == 0){
		return;
	}
	this -> extend_tree();
	return(((*(this -> left)).generate_tree(depth-1)), ((*(this -> right)).generate_tree(depth-1)));
}
int node::depth_first(){
	//goes through the tree in a depth-first manner, plan is to have it search for a target value, and output its path in the future
	std::cout << this -> value;
	std::cout << " ";
	if((this -> left) == NULL and (this -> right) == NULL){
		return(this -> value);
	}else if((this -> left) != NULL and (this -> right) == NULL){
		return(this -> value, (*(this -> left)).depth_first());
	}else if((this -> left) == NULL and (this -> right != NULL)){
		return(this -> value, (*(this -> right)).depth_first());
	}else{
		return(this -> value, (*(this -> left)).depth_first(), (*(this -> right)).depth_first());
	}
}
class queue_item{
	//this class will keep track of nodes in a queue (as opposed to the default stack) to keep track of nodes in a depth-first search
	//it's basically just a singly linked list for nodes
	public:
		queue_item* next_item = NULL;
		node* value;
	queue_item(node* value){
		this -> value = value;
	};
	void append(node* value){
		//adds a queue item to the end of the current queue
		if(this -> next_item == NULL){
			this -> next_item = new queue_item(value);
		}else{
			queue_item* current_item = this -> next_item;
			while((*current_item).next_item != NULL){
				current_item = (*current_item).next_item;
			}
			(*current_item).next_item = new queue_item(value);
		}
	}
};
queue_item* breadth_checker(queue_item* current_item){
	//given a pointer to a queue_item, prints value at indicated node and appends the next items to the back of the queue
	if(current_item != NULL){
		std::cout << (*((*current_item).value)).value;
		std::cout << " ";
		if((*((*current_item).value)).left == NULL and (*((*current_item).value)).right == NULL){
			queue_item* next_item = (*current_item).next_item;
			delete current_item;
			return(next_item);
		}else if((*((*current_item).value)).left != NULL and (*((*current_item).value)).right == NULL){
			(*current_item).append((*(*current_item).value).left);
			queue_item* next_item = (*current_item).next_item;
			delete current_item;
			return(next_item);
		}else if((*((*current_item).value)).left == NULL and (*((*current_item).value)).right != NULL){
			(*current_item).append((*(*current_item).value).right);
			queue_item* next_item = (*current_item).next_item;
			delete current_item;
			return(next_item);
		}else{
			(*current_item).append((*(*current_item).value).left);
			(*current_item).append((*(*current_item).value).right);
			queue_item* next_item = (*current_item).next_item;
			delete current_item;
			return(next_item);
		}
	}else{
		return NULL;
	}
}
int breadth_first(queue_item* first_item, node* root){
	//manages the queue and handles end-cases for breadth_checker, returns 1 when complete
	if(first_item == NULL and root == NULL){
		return(1);
	}
	queue_item* current_item = first_item;
	if(first_item == NULL and root != NULL){
		current_item = new queue_item(root);
	}
	current_item = breadth_checker(current_item);
	return(breadth_first(current_item, NULL));
}
int main(){
	//at the moment, the two searches don't really search for a target value, they just print out all the tree values as they follow their search pattern
	node x = node(0, NULL); //defining root of the tree
	x.generate_tree(3); //building a tree with default values to depth of root + 3 (feel free to try changing this value!)
	std::cout << "depth-first search pattern: ";
	x.depth_first();
	std::cout << "\n";
	std::cout << "breadth-first search pattern: ";
	breadth_first(NULL, &x); //breadth-first search is not a method on the node class since it relies on the queue class as well
	std::cout << "\n";
}
//breadth first: need to make a queue of nodes, and get values at the nodes in a FIFO manner
//depth-first uses stack ordering of recursive calls, breadth-first needs queue ordering of recursive calls
//depth-first was much easier, breadth-first will require creation of a queue class
