#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <cmath>
#include <ctime>
#include "8puzzle.h"

using namespace std;

struct overLoadComparsion
{
	bool operator()(const Problem node1, const Problem node2)
	{
		return (node1.depth + node1.heuristic) > (node2.depth + node2.heuristic);
	}
};
int start_s, stop_s;
const int columns = 3;
const int rows = 3;
int new_maximum_nodes = 0;
int new_maximum_priority = 0;
int puzzle[puzzleSize];
int tracebackCtr = 0;
int node_creation_counter = 0;
stack<Problem> traceback;
vector<Problem> newNodes;
vector<Problem> visitedNodes;
bool goalFound = false;

priority_queue< Problem, vector<Problem> , overLoadComparsion >priorityQ; 
int depth;
int childrenDepth = 0;


Problem::Problem()
{
	for (int i = 0; i < puzzleSize; i++)
	{
		parent[i] = 0;
	}
}
void Problem::vctrOutput()		
{
	cout << this->parent[0] << " " << this->parent[1] << " " << this->parent[2] << endl;
	cout << this->parent[3] << " " << this->parent[4] << " " << this->parent[5] << endl;
	cout << this->parent[6] << " " << this->parent[7] << " " << this->parent[8] << endl;
}

int Problem::findZero()
{
	for (int i = 0; i < puzzleSize; i++)
	{
		if(this->parent[i] == 0)
		{
			return i;
		}
	}
	cout << "Zero is not present in the puzzle\n";
	return -1;
}
bool Problem::goalCheck()
{
	if (this->parent[0] == 1 && this->parent[1] == 2 && this->parent[2] == 3 && this->parent[3] == 4 && this->parent[4] == 5 && this->parent[5] == 6 && this->parent[6] == 7 && this->parent[7] == 8 && this->parent[8] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Problem::duplicateBoard(int destBoard[puzzleSize], int origBoard[puzzleSize])
{
	for (int i = 0; i < puzzleSize; i++)
	{
		destBoard[i] = origBoard[i];
	}
}
void Problem::moveRight(int x, Problem root, int choice)
{
	if(!goalFound)
	{
		if(x % columns < columns - 1)
		{
			cout << endl;
			Problem childrenNode;
			duplicateBoard(childrenNode.parent, root.parent);
			swap(childrenNode.parent[x + 1], childrenNode.parent[x]);	
			childrenNode.predessor.push_back(root);
			if(childrenNode.goalCheck() == true)
			{
				if(choice == 1)
				{
					childrenNode.heuristic = 0;
				}
				if(choice == 2)
				{
					childrenNode.heuristic = childrenNode.checkMisplacedTile(childrenNode);
				}
				if(choice == 3)
				{
					childrenNode.Euclidean();
				}
				cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = 0 is...\n";
				childrenNode.vctrOutput();
				goalFound = true;
				traceback.push(childrenNode);
				pathtrace(childrenNode, choice);
			}
			else
			{
				childrenNode.depth = childrenDepth;
				if(choice == 1)
				{
					newNodes.push_back(childrenNode);
					childrenNode.heuristic = 0;
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = 0 is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n";
				}
				if(choice == 2)
				{
					childrenNode.heuristic = childrenNode.checkMisplacedTile(childrenNode);
					priorityQ.push(childrenNode);
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = " << childrenNode.heuristic << " is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n";
				}
				if(choice == 3)
				{
					childrenNode.Euclidean();
					priorityQ.push(childrenNode);
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = " << childrenNode.heuristic << " is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n";
				}
			}
		}
		new_node_size_check();
		priority_queue_size_check();
	}
}
void Problem::moveLeft(int x, Problem root, int choice)
{
	if(!goalFound)
	{
		if(x % columns > 0)
		{
			cout << endl;
			Problem childrenNode;
			duplicateBoard(childrenNode.parent, root.parent);
			swap(childrenNode.parent[x - 1], childrenNode.parent[x]);
			childrenNode.predessor.push_back(root);
			if(childrenNode.goalCheck() == true)
			{
				if(choice == 1)
				{
					childrenNode.heuristic = 0;
				}
				if(choice == 2)
				{
					childrenNode.heuristic = childrenNode.checkMisplacedTile(childrenNode);
				}
				if(choice == 3)
				{
					childrenNode.Euclidean();
				}
				cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = 0 is..\n";
				childrenNode.vctrOutput();
				goalFound = true;
				traceback.push(childrenNode);
				pathtrace(childrenNode, choice);
			}
			else
			{
				childrenNode.depth = childrenDepth;
				if(choice == 1)
				{
					newNodes.push_back(childrenNode);
					childrenNode.heuristic = 0;
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = 0 is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n";
				}
				if(choice == 2)
				{
					childrenNode.heuristic = childrenNode.checkMisplacedTile(childrenNode);
					priorityQ.push(childrenNode);
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = " << childrenNode.heuristic << " is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n";
				}
				if(choice == 3)
				{
					childrenNode.Euclidean();
					priorityQ.push(childrenNode);
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = " << childrenNode.heuristic << " is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n";
				}
			}
		}
		new_node_size_check();
		priority_queue_size_check();
	}
}
void Problem::moveUp(int x, Problem root, int choice)
{
	if(!goalFound)
	{
		if(x - columns >= 0)
		{
			cout << endl;
			Problem childrenNode;
			duplicateBoard(childrenNode.parent, root.parent);
			swap(childrenNode.parent[x - 3], childrenNode.parent[x]);
			childrenNode.predessor.push_back(root);
			if(childrenNode.goalCheck() == true)
			{
				if(choice == 1)
				{
					childrenNode.heuristic = 0;
				}
				if(choice == 2)
				{
					childrenNode.heuristic = childrenNode.checkMisplacedTile(childrenNode);
				}
				if(choice == 3)
				{
					childrenNode.Euclidean();
				}
				cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = 0 is...\n";
				childrenNode.vctrOutput();
				goalFound = true;
				traceback.push(childrenNode);
				pathtrace(childrenNode, choice);
			}
			else
			{
				childrenNode.depth = childrenDepth;
				if(choice == 1)
				{
					newNodes.push_back(childrenNode);
					childrenNode.heuristic = 0;
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = 0 is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n\n";
				}
				if(choice == 2)
				{
					childrenNode.heuristic = childrenNode.checkMisplacedTile(childrenNode);
					priorityQ.push(childrenNode);
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = " << childrenNode.heuristic << " is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n";
				}
				if(choice == 3)
				{
					childrenNode.Euclidean();
					priorityQ.push(childrenNode);
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = " << childrenNode.heuristic << " is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n" ;
				}
			}
		}
		new_node_size_check();
		priority_queue_size_check();
	}
}
void Problem::moveDown(int x, Problem root, int choice)
{
	if(!goalFound)
	{
		if(x + columns < puzzleSize)
		{
			cout << "\n";
			Problem childrenNode;
			duplicateBoard(childrenNode.parent, root.parent);
			swap(childrenNode.parent[x + 3], childrenNode.parent[x]);
			childrenNode.predessor.push_back(root);
			if(childrenNode.goalCheck() == true)
			{
				if(choice == 1)
				{
					childrenNode.heuristic = 0;
				}
				if(choice == 2)
				{
					childrenNode.heuristic = childrenNode.checkMisplacedTile(childrenNode);
				}
				if(choice == 3)
				{
					childrenNode.Euclidean();
				}
				cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = 0 is...\n" ;
				childrenNode.vctrOutput();
				goalFound = true;
				traceback.push(childrenNode);
				pathtrace(childrenNode, choice);
			}
			else
			{
				childrenNode.depth = childrenDepth;
				if(choice == 1)
				{
					newNodes.push_back(childrenNode);
					childrenNode.heuristic = 0;
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = 0 is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n";
				}
				if(choice == 2)
				{
					childrenNode.heuristic = childrenNode.checkMisplacedTile(childrenNode);		
					priorityQ.push(childrenNode);
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = " << childrenNode.heuristic << " is...\n";
					childrenNode.vctrOutput();
					cout << endl << "Expanding this node...\n";
				}
				if(choice == 3)
				{
					childrenNode.Euclidean();			
					priorityQ.push(childrenNode);
					cout << "The best state to expand with g(n) = " << childrenDepth << " and h(n) = " << childrenNode.heuristic << " is...\n";
					childrenNode.vctrOutput();
					cout << "Expanding this node...";
				}
			}
		}
		new_node_size_check();
		priority_queue_size_check();
	}
}
void Problem::expansion(Problem root, int x)			
{
	root.goalCheck();		
	int zeroPos = root.findZero();
	childrenDepth++;
	node_creation_counter++;
	moveRight(zeroPos, root, x);
	moveLeft(zeroPos, root, x);
	moveUp(zeroPos, root, x);
	moveDown(zeroPos, root, x);
}
bool Problem::exact_puzzle(Problem node)
{
	bool exact_puzzle = true;
	for (int i = 0; i < puzzleSize; i++)
	{
		if( parent[i] != node.parent[i])
		{
			exact_puzzle = false;
		}
	}
	return exact_puzzle;
}
bool contains(vector<Problem> list, Problem object)		
{
	bool contains = false;

	for(int i = 0; i < list.size(); i++)		
	{
		if(list[i].exact_puzzle(object))
		{
			contains = true;
		}
	}
	return contains;
}
void Problem::new_node_size_check()				
{
	int temp = newNodes.size();
	if(temp > new_maximum_nodes)
	{
		new_maximum_nodes = newNodes.size();
	}
}
void Problem::priority_queue_size_check()				
{
	int temp = priorityQ.size();
	if(temp > new_maximum_priority)
	{
		new_maximum_priority = priorityQ.size();
	}
}
void Problem::uni_search(Problem node, int choice)
{
	cout << "Expanding State: " << endl;
	node.vctrOutput();
	cout << endl;
	newNodes.push_back(node);
	new_node_size_check();

	while(newNodes.size() > 0 && !goalFound)
	{
		Problem currentNode = newNodes.front();		
		visitedNodes.push_back(currentNode);				
		if(currentNode.goalCheck() == false)
		{
			newNodes.erase(newNodes.begin());
			expansion(currentNode, choice);
		}
		else
		{
			goalFound = true;
			cout << "Goal Found!!!" << endl;
			currentNode.heuristic = 0;
			traceback.push(currentNode);
			pathtrace(currentNode, choice);
		}
	}
}
void Problem::euclid_dist_search(Problem node, int choice)
{
	node.depth = 0;
	node.Euclidean();
	priorityQ.push(node);

	while(priorityQ.size() > 0 && !goalFound)
	{
		Problem currentNode = priorityQ.top();
		visitedNodes.push_back(currentNode);
		priority_queue_size_check();
		if(currentNode.goalCheck() == false)
		{
			priorityQ.pop();
			expansion(currentNode, choice);
		}
		else
		{
			goalFound = true;
			cout << "Goal Found!!!" << endl;
			traceback.push(currentNode);
			pathtrace(currentNode, choice);
		}
	}
}

void Problem::misplaced_tile_search(Problem node, int choice)
{
	node.depth = 0;
	node.heuristic = checkMisplacedTile(node);
	priorityQ.push(node);

	while(priorityQ.size() > 0 && !goalFound)
	{
		Problem currentNode = priorityQ.top();
		visitedNodes.push_back(currentNode);
		priority_queue_size_check();
		if(currentNode.goalCheck() == false)
		{
			priorityQ.pop();
			expansion(currentNode, choice);
		}
		else
		{
			goalFound = true;
			cout << "Goal Found!!!" << endl;
			traceback.push(currentNode);
			pathtrace(currentNode, choice);
		}
	}
}
void result_summary(int x)
{
	cout << "\n";
	cout << "Goal!!!\n\n";
	cout << "To solve this problem the search algorithm expanded a total of " << node_creation_counter << " nodes." << "\n";
	if(x == 1)
	{
		cout << "The maximum number of nodes in the queue at any one time:" << new_maximum_nodes << "." << "\n";
	}
	else
	{
		cout << "The maximum number of nodes in the queue at any one time:" << new_maximum_priority << "." << "\n";
	}
}

bool Problem::originalMatrixCheck(Problem node)
{
	if (node.parent[0] == puzzle[0] && node.parent[1] == puzzle[1] && node.parent[2] == puzzle[2] && node.parent[3] == puzzle[3] && node.parent[4] == puzzle[4] && node.parent[5] == puzzle[5] && node.parent[6] == puzzle[6] && node.parent[7] == puzzle[7] && node.parent[8] == puzzle[8])
	{
		return true;
	}
	return false;

}

void Problem::Euclidean()
{
	int one = 0;
	int two = 1;
	int three = 2;
	int four = 3;
	int five = 4;
	int six = 5;
	int seven = 6;
	int eight = 7;
	int hCounter = 0; //heuristic counter
	for(int i = 0; i < puzzleSize; i++)
	{
		if(this->parent[i] != 0)
		{
			if(this->parent[i] == 1)
			{
				int temp = (abs(i - one));
				if(temp == 1 || temp == 3)
				{
					hCounter += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					hCounter += 2;
				}
				if(temp == 5 || temp == 7)
				{
					hCounter += 3;
				}
				if(temp == 8)
				{
					hCounter += 4;
				}

			}
			if(this->parent[i] == 2)
			{
				int temp = (abs(i - two));
				if(temp == 1 || temp == 3)
				{
					hCounter += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					hCounter += 2;
				}
				if(temp == 5 || temp == 7)
				{
					hCounter += 3;
				}
				if(temp == 8)
				{
					hCounter += 4;
				}	
			}
			if(this->parent[i] == 3)
			{
				int temp = (abs(i - three));
				if(temp == 1 || temp == 3)
				{
					hCounter += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					hCounter += 2;
				}
				if(temp == 5 || temp == 7)
				{
					hCounter += 3;
				}
				if(temp == 8)
				{
					hCounter += 4;
				}
			}
			if(this->parent[i] == 4)
			{
				int temp = (abs(i - four));
				if(temp == 1 || temp == 3)
				{
					hCounter += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					hCounter += 2;
				}
				if(temp == 5 || temp == 7)
				{
					hCounter += 3;
				}
				if(temp == 8)
				{
					hCounter += 4;
				}
			}
			if(this->parent[i] == 5)
			{
				int temp = (abs(i - five));
				if(temp == 1 || temp == 3)
				{
					hCounter += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					hCounter += 2;
				}
				if(temp == 5 || temp == 7)
				{
					hCounter += 3;
				}
				if(temp == 8)
				{
					hCounter += 4;
				}
			}
			if(this->parent[i] == 6)
			{
				int temp = (abs(i - six));
				if(temp == 1 || temp == 3)
				{
					hCounter += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					hCounter += 2;
				}
				if(temp == 5 || temp == 7)
				{
					hCounter += 3;
				}
				if(temp == 8)
				{
					hCounter += 4;
				}
			}
			if(this->parent[i] == 7)
			{
				int temp = (abs(i - seven));
				if(temp == 1 || temp == 3)
				{
					hCounter += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					hCounter += 2;
				}
				if(temp == 5 || temp == 7)
				{
					hCounter += 3;
				}
				if(temp == 8)
				{
					hCounter += 4;
				}
			}
			if(this->parent[i] == 8)
			{
				int temp = (abs(i - eight));
				if(temp == 1 || temp == 3)
				{
					hCounter += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					hCounter += 2;
				}
				if(temp == 5 || temp == 7)
				{
					hCounter += 3;
				}
				if(temp == 8)
				{
					hCounter += 4;
				}
			}
		}
	}
	this->heuristic = hCounter;
}

void Problem::pathtrace(Problem node, int choice)
{
	vector<Problem> path;

	while(originalMatrixCheck(node) != true)
	{
		depth++;
		node = node.predessor.front();		
		traceback.push(node);				
	}

	cout << "\nOutput of traceback : \n";
	while(!traceback.empty())
	{
		Problem obj = traceback.top();
		traceback.pop();
		if(choice == 3)
		{
			obj.Euclidean();
		}
		cout << "\n";
		obj.vctrOutput();
		tracebackCtr++;
		if(!traceback.empty())
		{
			cout << endl << "Expanding this node... \n";
		}
	}

	result_summary(choice);
}

int Problem::checkMisplacedTile(Problem node) // Check Misplaced Tile 
{
	int cost = 0;
	if(node.parent[0] != 1)
	{
		cost++;
	}
	if(node.parent[1] != 2)
	{
		cost++;
	}
	if(node.parent[2] != 3)
	{
		cost++;
	}
	if(node.parent[3] != 4)
	{
		cost++;
	}
	if(node.parent[4] != 5)
	{
		cost++;
	}
	if(node.parent[5] != 6)
	{
		cost++;
	}
	if(node.parent[6] != 7)
	{
		cost++;
	}
	if(node.parent[7] != 8)
	{
		cost++;
	}
	return cost;
}

int main()
{
	depth = 0;			//Initializing g(n) as zero
	int user_choice;
	cout << "\nWelcome to \"861284867\" 8 puzzle solver. \n";
	cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle. \n";
	cin >> user_choice;
	if (user_choice == 1)
	{
		puzzle[0] = 1;
		puzzle[1] = 2;
		puzzle[2] = 3;

		puzzle[3] = 4;
		puzzle[4] = 8;
		puzzle[5] = 0;

		puzzle[6] = 7;
		puzzle[7] = 6;
		puzzle[8] = 5;

		cout << "\nEnter your choice of algorithm \n";
		cout << "\n1. Uniform Cost Search ";
		cout << "\n2. A* with Misplaced Tile heuristic.";
		cout << "\n3. A* with Euclidean distance heuristic.\n";
		cin >> user_choice;
		if(user_choice == 1)
		{
			cout << endl;
			Problem object;
			object.duplicateBoard(object.parent, puzzle);
			object.vctrOutput();		
			start_s=clock();
			object.uni_search(object, user_choice); // Uniform Search
			stop_s=clock();
		}
		if(user_choice == 2)
		{
			Problem object;
			object.duplicateBoard(object.parent, puzzle);
			object.vctrOutput();		
			start_s=clock();
			object.misplaced_tile_search(object, user_choice); // Misplaced Tile Search Algorithm
			stop_s=clock();
			user_choice = 0;
		}
		if(user_choice == 3)
		{
			Problem object;
			object.duplicateBoard(object.parent, puzzle);
			object.vctrOutput();		
			start_s = clock();
			object.euclid_dist_search(object, user_choice); // Euclidian Distance Search Algotithm
			stop_s = clock();
			user_choice = 0;
		}
	}
	if(user_choice == 2)
	{
		cout << "Insert a zero to represent blank spot in the puzzle \n";
		
		cout << "Enter 3 numbers seperated with spaces for this 1st row\n";
		int var1, var2, var3;
		cin >> var1 >> var2 >> var3; // Row 1
		puzzle[0] = var1;
		puzzle[1] = var2;
		puzzle[2] = var3;
		
		cout << endl << "Enter 3 numbers seperated with spaces for this 2nd row \n";
		cin >> var1 >> var2 >> var3; // Row 2
		puzzle[3] = var1;
		puzzle[4] = var2;
		puzzle[5] = var3;

		cout << endl << "Enter 3 numbers seperated with spaces for this 3rd row \n";
		cin >> var1 >> var2 >> var3; // Row 3
		puzzle[6] = var1;
		puzzle[7] = var2; 
		puzzle[8] = var3;

		cout << "\n";
		cout << "Enter your choice of algorithm: \n";
		cout << "\n" << "1. Uniform Cost Search ";
		cout << "\n" << "2. A* with misplaced_tile_search Tile heuristic ";
		cout << "\n" << "3. A* with Euclidean distance heuristic \n";
		cin >> user_choice;
		
		if(user_choice == 1)
		{
			cout << endl;
			Problem object;
			object.duplicateBoard(object.parent, puzzle);
			object.vctrOutput();		//outputting vector
			object.uni_search(object, user_choice);
		}
		
		if(user_choice == 2)
		{
			Problem object;
			object.duplicateBoard(object.parent, puzzle);
			object.vctrOutput();		//outputting vector
			object.misplaced_tile_search(object, user_choice);
		}
		
		if(user_choice == 3)
		{
			Problem object;
			object.duplicateBoard(object.parent, puzzle);
			object.vctrOutput();		//outputting vector
			object.euclid_dist_search(object, user_choice);
		}
		
	}
	cout << "\nThank you for using \"861284867 \" 8-Puzzle \n\n";

}
