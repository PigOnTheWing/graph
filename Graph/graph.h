#ifndef GRAPH_GRAPH_H_
#define GRAPH_GRAPH_H_

#include <iostream>
#include <list>
#include "node.h"

template <class T> class graph
{
	int next_id = 0;
	std::vector<node<T>*> nodes;
	node<T>** breadth_list = new node<T>*[100];
	int dfs_length = 0;

	node<T>** depth_list = new node<T>*[100];
	int bfs_length = 0;

	void clear_visited()
	{
	    for (node<T>* n : this->nodes)
	        n->set_visited(false);
	}

	void clear_breadth()
    {
	    for (int i = 0; i < 100; i++)
	        this->breadth_list[i] = 0;

	    this->bfs_length = 0;
    }

    void clear_depth()
    {
        for (int i = 0; i < 100; i++)
            this->depth_list[i] = 0;

        this->dfs_length = 0;
    }

	int dfs_rec(node<T>* n, int i)
	{
	    this->depth_list[i++] = n;
        n->set_visited(true);

        for (edge<T>* e : n->get_connections())
        {
            if (!e->to()->is_visited())
                i = dfs_rec(e->to(), i);
        }

        return i;
	}
public:
	graph() = default;

	~graph()
	{
		for (node<T>* n : this->nodes)
			delete n;

		delete[] this->breadth_list;
		delete[] this->depth_list;
	}

	void add_node(T data)
	{
		auto* n = new node<T>(data, this->next_id++);
		this->nodes.push_back(n);
	}

	void connect(int _from, int _to, int weight=0)
	{
	    auto* e = new edge<T>(this->nodes[_from], this->nodes[_to], weight);
		this->nodes[_from]->add_connection(e);
	}

	int bfs(int _from)
	{
	    int i = 0;
	    this->clear_visited();
	    this->clear_breadth();

	    std::list<node<T>*> q;

	    q.push_back(this->nodes[_from]);
	    this->breadth_list[i++] = nodes[_from];
	    this->nodes[_from]->set_visited(true);

	    while(!q.empty())
        {
	        node<T>* n = q.front();

            q.pop_front();

	        for (edge<T>* e : n->get_connections())
            {
	            if (!e->to()->is_visited()) {
	                e->to()->set_visited(true);
	                q.push_back(e->to());
	                this->breadth_list[i++] = e->to();
	            }
            }
        }
	    return i;
	}

	int dfs(int _from)
	{
	    this->clear_visited();
	    this->clear_depth();
        return this->dfs_rec(this->nodes[_from], 0);
	}

	void print()
    {
	    for (node<T>* n : this->nodes)
        {
	        std::cout << n->get_data() << ": ";

	        for (edge<T>* e : n->get_connections())
	            std::cout << e->to()->get_data() << "(" << e->get_weight() << ") ";

	        std::cout << std::endl;
        }
    }

    class iterator {

	    node<T>** curr;
	    int length;

	public:
	    iterator(node<T>* _nodes[], int length, bool is_begin)
        {
	        if (is_begin)
	            curr = _nodes;
	        else
	            curr = _nodes + length;
        }


        iterator& operator++()
        {
	        curr++;
	        return *this;
        }

        const iterator operator++(int)
        {
	        iterator tmp = *this;
	        ++(*this);
	        return tmp;
        }

        iterator& operator--()
        {
            curr--;
            return *this;
        }

        const iterator operator--(int)
        {
            iterator tmp = *this;
            --this;
            return tmp;
        }

        node<T>* operator*() { return *curr; }

        bool operator==(const iterator& rhs)
        {
            return this->curr == rhs.curr;
        }

        bool operator!=(const iterator& i1)
        {
	        return !((*this) == i1);
        }
	};

	iterator breadth_begin(int _from)
	{
	    this->bfs_length = this->bfs(_from);
        return iterator(this->breadth_list, this->bfs_length, true);
	}

	iterator breadth_end(int _from)
    {
	    return iterator(this->breadth_list, this->bfs_length, false);
    }

    iterator depth_begin(int _from)
    {
	    this->dfs_length = this->dfs(_from);
        return iterator(this->depth_list, this->dfs_length, true);
    }

    iterator depth_end(int _from)
    {
        return iterator(this->depth_list, this->dfs_length, false);
    }
};



#endif /* GRAPH_GRAPH_H_ */
