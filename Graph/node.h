#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <iostream>

template <class T> class edge;

template <class T> class node
{
	int id = 0;
	std::vector<edge<T>*> connections;
	bool visited = false;
	T data;
public:
	node(int id) { this->id = id; }

	node(T data, int id)
	{
		this->data = data;
		this->id = id;
	}

	~node() {
	    for (edge<T>* e : this->connections)
	        delete e;
	}

	void add_connection(edge<T>* n)
	{
		connections.push_back(n);
	}

	T get_data() { return this->data; }

	int get_id() { return this->id; }

	void set_data(T _data) { this->data = _data; }

	bool is_visited() { return this->visited; }

	void set_visited(bool val) { this->visited = val; }

	std::vector<edge<T>*> get_connections() { return this->connections; }
};

template <class T>  class edge {
    node<T>* _from;
    node<T>* _to;
    int weight = 0;
public:
    edge(node<T>* _from, node<T>* _to, int weight=0) {
        this->_from = _from;
        this->_to = _to;
        this->weight = weight;
    };
    ~edge() = default;

    void set_weight(int _weight) {
        this->weight = _weight;
    }

    int get_weight() {
        return this->weight;
    }

    node<T>* from() {return this->_from; }
    node<T>* to() {return this->_to; }
};



#endif /* NODE_H_ */
