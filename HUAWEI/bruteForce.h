#include <vector>
#include "edge.h"
#define MAX_N 666

class bruteForce{
public:
	bruteForce(const &std::vector<int>, const &std::vector<int>, const &std::vector<int>);
	std::vector<int> singleSolution(int , int); // original node and terminal node
private:
	std::vector<edge> G[MAX_N];
};