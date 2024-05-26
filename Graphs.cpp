#pragma once
#include <vector> 
#include <iostream> 
#include <queue> 
#include <iterator> 
#include <algorithm> 
#include <limits> 
#include <map> 
#include <exception>
using namespace std;


template<typename Vertex, typename Distance = double>
struct edge {
	Vertex from;
	Vertex to;
	Distance dist;

	edge(Vertex from, Vertex to) : from(from), to(to), dist(0) {};
	edge(Vertex from, Vertex to, Distance dist) : from(from), to(to), dist(dist) {};
};

template<typename Vertex, typename Distance = double>
class graph {
private:
	vector<Vertex>  _vert;
	vector<edge<Vertex, Distance>> _edg;
public:
	graph() : _edg(vector<edge<Vertex, Distance>>()), _vert(Vector<Vertex>()) {};

	bool has_vertex(const Vertex& vert) const {
		for (const auto& vertex : _vert) {
			if (vertex == vert) {
				return true;
			}
		}
		return false;
	}

	void add_vertex(const Vertex& vert) {
		if (!has_vertex(vert)) {
			_vert.push_back(vert);
		}
	}

	bool remove_vertex(const Vertex& vert) {
		if (!has_vertex(vert)) {
			return false;
		}

		for (int i = 0; i < _edg.size(); i++) {
			if (_edg[i].to == vert || _edg[i].from == vert) {
				 _edg.erase(_edg[i]);
				i--;
			}
		}

		for (int i = 0; i < _vert.size(); i++) {
			if (_vert[i] == vert) {
				_vert.erase(_vert.begin() + i);
				return true;
			}
		}
	}

	vector<Vertex> vertices() const {
		return _vert;
	}

	bool has_edge(const Vertex& from, const Vertex& to) const {
		for (const edge<Vertex, Distance>& edge : _edg) {
			if (edge.from == from && edge.to == to)
				return true;
		}
		return false;
	}

	bool has_edge(const edge<Vertex, Distance>& e) {
		for (const edge<Vertex, Distance>& edge : _edg) {
			if (edge.from == e.from && edge.to == e.to && edge.dist == e.dist)
				return true;
		}
		return false;
	}

	void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
		edge<Vertex, Distance> e(from, to, d);
		if (has_vertex(from) && has_vertex(to)){
			_edg.push_back(e);
		}
	}

	bool remove_edge(const Vertex& from, const Vertex& to) {
		for (int i = 0; i < _edg.size(); i++) {
			if (_edg[i].from == from && _edg[i].to == to)
				_edg.erase(_edg.begin() + i);
			return true;
		}
		return false;
	}

	bool remove_edge(const edge<Vertex, Distance>& e) {
		for (int i = 0; i < _edg.size(); i++) {
			if (_edg[i].from == e.from && _edg[i].to == e.to && _edg[i].dist == e.dist)
				_edg.erase(_edg.begin() + i);
			return true;
		}
		return false;
	}

	vector<edge<Vertex, Distance>> edges(const Vertex& vertex) const {
		vector<edge<Vertex, Distance>> res;
		for (auto edge : _edg) {
			if (edge.from == vertex) {
				res.push_back(edge);
			}
		}
		return res;
	}

	size_t degree(const Vertex& vert) const {
		size_t res = 0;
		for (const auto& edge : _edg) {
			if (edge.from == vert)
				res += 1;
		}
		return res;
	}

	vector<Vertex> vertices(const Vertex& start) const {

		vector<Vertex> res;

		vector<edge<Vertex, Distance>> e = edges(start);

		for (const auto& edge : e) {
			res.push_back(edge.to);
		}

		return res;
	}

	Distance shorted_path(const Vertex& start, const Vertex& finish) {
		
		vector<Vertex> unvisit = vertices();
		map<Vertex, Distance> shortest;

		for (const Vertex& v : unvisit) {
			shortest[v] = numeric_limits<Distance>::max();
		}
		shortest[start] = 0;

		while (!unvisit.empty()) {
			Vertex current = unvisit[0];
			for (const Vertex v : unvisit) {
				if (shortest[v] < shortest[current]) {
					current = v;
				}
			}

			vector<Vertex> near = vertices(current);
			for (const Vertex n : near) {

				Distance d;

				for (const auto edge : _edg) {
					if (edge.from = current && edge.to == n) {
						d = edge.dist;
					}
				}

				Distance temp = shortest[current] + d;
				if (temp < shortest[n]) {
					shortest[n] = temp;
				}
			}
			int i = 0;
			while (i < unvisit.size()){
				if (unvisit[i] == current) {
					break;
				}
				i++;
			 }
			unvisit.erase(unvisit.begin() + i);
		}
		return shortest[finish];
	}

	vector<Vertex> walk(const Vertex& start_vertex) const {
		queue<Vertex> que;
		que.push(start_vertex);
		vector<Vertex> res;

		while (!que.empty()) {

		}
	}
};
