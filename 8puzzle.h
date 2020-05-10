#include <vector>

using namespace std;

const int puzzleSize = 9; //Size of the puzzle 3x3 = 9

class Problem
{

	private:

	public:
		Problem();
		int parent[puzzleSize];
		vector<Problem> children;
		vector<Problem> predessor;
		int depth;
		int heuristic;
		void moveUp(int x, Problem root, int choice);
		void moveDown(int x, Problem root, int choice);
		void moveLeft(int x, Problem root, int choice);
		void moveRight(int x, Problem root, int choice);
		int findZero();
		void vctrOutput();
		void vctrOutput(int origpuzzle[puzzleSize]);
		bool goalCheck();
		void duplicateBoard(int destBoard[puzzleSize], int origBoard[puzzleSize]);
		void expansion(Problem node, int x);
		bool ifListContainsNode(Problem node);
		bool exact_puzzle(Problem node);
		void uni_search(Problem node, int x);
		void pathtrace(Problem node, int);
		bool originalMatrixCheck(Problem node);
		int checkMisplacedTile(Problem node);
		void misplaced_tile_search(Problem node, int x);
		void Euclidean();
		void euclid_dist_search(Problem node, int x);
		void new_node_size_check();
		void priority_queue_size_check();

};
