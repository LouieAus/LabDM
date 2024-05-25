#include <iostream>
#include "graph.h"

using namespace graph;

int main()
{
	setlocale(LC_ALL, "Rus");

	Graph graph_1;
	graph_1.ReadGraph();

	graph_1.ConvertVecToIdMatrix();
	std::cout << "Матрица инцидентности:\n";
	graph_1.PrintIdMatrix();

	std::cout << "\n\n" << "Граф Эйлеровый: " << graph_1.CheckEuler() << "\n\n";

	graph_1.ConvertIdToAdjMatrix();
	std::cout << "Матрица смежности:\n";
	graph_1.PrintAdjMatrix();

	std::cout << '\n';
	graph_1.CalculateMinDistances();
}