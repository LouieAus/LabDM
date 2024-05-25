#pragma once
#include <vector>
#include <iostream>

namespace graph
{
	struct VertexPair
	{
		int vertex_1;
		int vertex_2;
		int value;
	};

	class Graph
	{
	private:
		std::vector<VertexPair> graph_;					// взвешенный граф в виде вектора ребер
		int vertex_quantity_ = 0;
		std::vector<std::vector<int>> identityMatrix_;	// матрица инцидентности
		std::vector<std::vector<int>> adjacencyMatrix_;	// матрица смежности

		std::vector<std::vector<int>> identityWeightMatrix_;

		std::vector<std::vector<int>> Deikstra(
			int begin_point,
			std::vector<int> passed_vetexes,
			std::vector<std::vector<int>> vertexes_to_point,
			std::vector<int> vertexes_data);

		int GetDistance(std::vector<int> vec);
	public:
		Graph();
		~Graph();

		void ReadGraph();
		void PrintIdMatrix();
		void PrintAdjMatrix();

		bool CheckEuler();

		void ConvertVecToIdMatrix();
		void ConvertIdToAdjMatrix();
		
		void CalculateMinDistances();
	};
}