#include "graph.h"

namespace graph
{
	Graph::Graph() {}
	Graph::~Graph() {}

	void Graph::ReadGraph()
	{
		int edges_q;
		std::cout << "Input edges quantity: ";
		std::cin >> edges_q;

		vertex_quantity_ = 0;
		for (auto i = 0; i != edges_q; i++)
		{
			system("cls");

			int vertex_from;
			std::cout << "From:\t";
			std::cin >> vertex_from;
			if (vertex_from > vertex_quantity_)
				vertex_quantity_ = vertex_from;

			int vertex_to;
			std::cout << "To:\t";
			std::cin >> vertex_to;
			if (vertex_to > vertex_quantity_)
				vertex_quantity_ = vertex_to;

			int weight;
			std::cout << "Weight:\t";
			std::cin >> weight;

			VertexPair new_pair = { vertex_from, vertex_to, weight };
			graph_.push_back(new_pair);
		}
		vertex_quantity_ += 1;
		system("cls");
	}

	void Graph::PrintIdMatrix()
	{
		for (std::vector<int>& row : identityMatrix_)
		{
			for (int value : row)
			{
				std::cout << value << '\t';
			}
			std::cout << '\n';
		}
	}

	void Graph::PrintAdjMatrix()
	{
		for (std::vector<int>& row : adjacencyMatrix_)
		{
			for (int value : row)
			{
				std::cout << value << '\t';
			}
			std::cout << '\n';
		}
	}

	bool Graph::CheckEuler()
	{
		for (std::vector<int>& vertex : identityMatrix_)
		{
			int k = 0;
			for (int edge : vertex)
				k += edge;

			if (k != 0)
				return false;
		}

		return true;
	}

	void Graph::ConvertVecToIdMatrix()
	{
		identityMatrix_.clear();

		for (auto i = 0; i != vertex_quantity_; i++)
		{
			std::vector<int> new_vertex(graph_.size(), 0);
			identityMatrix_.push_back(new_vertex);
		}

		for (auto j = 0; j != graph_.size(); j++)
		{
			int vertex_1 = graph_[j].vertex_1;
			int vertex_2 = graph_[j].vertex_2;

			identityMatrix_[vertex_1][j] = 1;
			identityMatrix_[vertex_2][j] = -1;
		}
	}

	void Graph::ConvertIdToAdjMatrix()
	{
		adjacencyMatrix_.clear();
		for (auto i = 0; i != vertex_quantity_; i++)
		{
			std::vector<int> new_row(vertex_quantity_, 0);
			adjacencyMatrix_.push_back(new_row);
		}

		for (auto i = 0; i != graph_.size(); i++)
		{
			int begin_vertex = -1;
			int end_vertex = -1;
			for (auto j = 0; j != vertex_quantity_; j++)
			{
				if (identityMatrix_[j][i] == 1)
					begin_vertex = j;
				else if (identityMatrix_[j][i] == -1)
					end_vertex = j;
			}

			adjacencyMatrix_[begin_vertex][end_vertex] = 1;
		}
	}

	std::vector<std::vector<int>> Graph::Deikstra(
		int begin_point, 
		std::vector<int> passed_vetexes,
		std::vector<std::vector<int>> vertexes_to_point,
		std::vector<int> vertexes_data)
	{
		if (passed_vetexes.size() == vertex_quantity_)
		{
			return vertexes_to_point;
		}

		for (int i = 0; i != vertex_quantity_; i++)
		{
			if (identityWeightMatrix_[begin_point][i] != 0)
			{
				bool passed = true;
				for (int v : passed_vetexes)
				{
					if (v == i)
					{
						passed = false;
						break;
					}
				}

				if (passed)
				{
					int new_w = vertexes_data[begin_point] + identityWeightMatrix_[begin_point][i];
					if (vertexes_data[i] == -1 || vertexes_data[i] > new_w)
					{
						vertexes_data[i] = new_w;

						std::vector<int> new_path = vertexes_to_point[begin_point];
						new_path.push_back(i);

						vertexes_to_point[i] = new_path;
					}
				}
			}
		}

		passed_vetexes.push_back(begin_point);

		int min_vertex = 0;
		int min_value;
		bool first = true;
		for (int i = 0; i != vertex_quantity_; i++)
		{
			if (vertexes_data[i] != -1)
			{
				bool passed = true;
				for (int v : passed_vetexes)
				{
					if (v == i)
					{
						passed = false;
						break;
					}
				}

				if (passed)
				{
					if (first)
					{
						first = false;
						min_vertex = i;
						min_value = vertexes_data[i];
					}
					else
					{
						if (min_value > vertexes_data[i])
						{
							min_value = vertexes_data[i];
							min_vertex = i;
						}
					}
				}
			}
		}

		return Deikstra(min_vertex, passed_vetexes, vertexes_to_point, vertexes_data);
	}

	bool AreVecSimilar(std::vector<int> a, std::vector<int> b)
	{
		if (a.size() != b.size())
			return false;

		bool ordinary_check = true;
		for (int i = 0; i != a.size(); i++)
		{
			if (a[i] != b[i])
			{
				ordinary_check = false;
				break;
			}
		}
		if (ordinary_check)
			return true;

		bool reversed_check = true;
		for (int i = 0; i != a.size(); i++)
		{
			if (a[i] != b[b.size() - 1 - i])
			{
				reversed_check = false;
				break;
			}
		}
		if (reversed_check)
			return true;

		return false;
	}

	int Graph::GetDistance(std::vector<int> vec)
	{
		int result = 0;
		for (int i = 0; i != vec.size() - 1; i++)
		{
			result += identityWeightMatrix_[vec[i]][vec[i + 1]];
		}
		return result;
	}

	void Graph::CalculateMinDistances()
	{
		identityWeightMatrix_.clear();
		for (auto i = 0; i != vertex_quantity_; i++)
		{
			std::vector<int> new_vertex(vertex_quantity_, 0);
			identityWeightMatrix_.push_back(new_vertex);
		}

		for (VertexPair& pair : graph_)
		{
			int vertex_1 = pair.vertex_1;
			int vertex_2 = pair.vertex_2;
			int weight = pair.value;

			int weight_12 = identityWeightMatrix_[vertex_1][vertex_2];
			int weight_21 = identityWeightMatrix_[vertex_2][vertex_1];

			if (weight_12 == 0 || weight_12 > weight)
			{
				identityWeightMatrix_[vertex_1][vertex_2] = weight;
				identityWeightMatrix_[vertex_2][vertex_1] = weight;
			}
		}

		std::vector<std::vector<int>> result;
		for (int i = 0; i != vertex_quantity_; i++)
		{
			std::vector<int> passed;

			std::vector<std::vector<int>> to_point(vertex_quantity_, std::vector<int>{});
			to_point[i] = std::vector<int>{ i };

			std::vector<int> data(vertex_quantity_, -1);
			data[i] = 0;

			std::vector<std::vector<int>> i_res = Deikstra(i, passed, to_point, data);

			for (std::vector<int>& vec : i_res)
			{
				if (vec.size() != 1)
				{
					bool not_in_result = true;
					for (std::vector<int>& vec_check : result)
					{
						if (AreVecSimilar(vec, vec_check))
						{
							not_in_result = false;
							break;
						}
					}
					if (not_in_result)
						result.push_back(vec);
				}
			}
		}

		for (std::vector<int>& vec : result)
		{
			int vertex_a = vec[0];
			int vertex_b = vec[vec.size() - 1];

			std::cout << "(" << vertex_a << ", " << vertex_b << ") = " << GetDistance(vec) << '\n';
			for (int i = 0; i != vec.size(); i++)
			{
				std::cout << vec[i];

				if (i != vec.size() - 1)
					std::cout << " - ";
			}
			std::cout << "\n\n";
		}
	}
}