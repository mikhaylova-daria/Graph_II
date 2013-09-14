#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
#include <memory>
#include <stack>
#include <vector>
template <typename T>
class Vertex {
public:
    T name;
    std::map<std::weak_ptr <Vertex>, int> list;
    Vertex (const T && _name):name(_name){;}
    ~Vertex() {}
};

template <typename T>
bool operator < (std::weak_ptr<Vertex<T> > ptr, std::weak_ptr<Vertex<T> > other_ptr){
    return (ptr.lock())->name < (other_ptr.lock())->name;
}

template <typename T>
bool operator == (std::weak_ptr<Vertex<T> > ptr, std::weak_ptr<Vertex<T> > other_ptr){
    return (ptr.lock())->name == (other_ptr.lock())->name;
}

template <typename T>
class Graph {
    std::map<T,std::shared_ptr<Vertex<T> > > V;
public:
    Graph(){;}
    ~Graph(){;}
    typename std::map<T,std::shared_ptr<Vertex<T> > >::iterator add_vertex(const T && name) {
        std::shared_ptr <Vertex<T> > vtx(new Vertex<T>(std::move(name)));
        return V.insert(make_pair(name,vtx)).first;
    }
    void rem_vertex(const T && name){
        V.erase(name);
        return;
    }
    void add_edge(const T && name_start, const T&& name_finish, int weight){
        typename std::map<T,std::shared_ptr<Vertex<T> > >::iterator insrt1;
        insrt1 = V.find(name_start);
        if (insrt1 == V.end()){
            insrt1 = add_vertex (std::move(name_start));
        }
        typename std::map<T,std::shared_ptr<Vertex<T> > >::iterator insrt2;
        insrt2 = V.find(name_finish);
        if (insrt2 == V.end()){
            insrt2 = add_vertex (std::move(name_finish));
        }
        std::pair< std::shared_ptr< Vertex<T> >, int> edg(insrt2->second, weight);
        insrt1->second->list.insert(edg);// кинуть исключение если повторилось ребро
        return;
    }
    void rem_edge(const T && name_start, const T&& name_finish){
        typename std::map<T,std::shared_ptr<Vertex<T> > >::iterator itr_s;
        typename std::map<T,std::shared_ptr<Vertex<T> > >::iterator itr_f;
        itr_s = V.find(name_start);
        if (itr_s == V.end()){
           //кинуть исключение
        } else {
            itr_f = V.find(name_finish);
            if (itr_f == V.end()){
               //кинуть исключение
            } else {
                itr_s->list.erase(itr_f);
            }
        }
        return;
    }
    void print () const {
        std::cout<<"name_start - name_finish : weight\n";
        typename std::map<T, std::shared_ptr <Vertex <T> > >::const_iterator itr;
        for (itr = V.cbegin(); itr != V.cend();++itr) {
            typename std::map<std::weak_ptr<Vertex<T> >, int >::const_iterator itr_list;
            std::cout<< itr-> first<<std::endl;
            for (itr_list = itr->second->list.cbegin(); itr_list != itr->second->list.cend();++itr_list){
                std::cout <<itr-> first << " - " << (itr_list->first).lock()->name << " : "<<itr_list->second<< std::endl;
            }
        }
        return;
    }

 /*   std::vector <std::set<T> > Tarjan() const{
        std::map<T, int> color_map;
        std::stack<std::map<T, std::shared_ptr<Vertex<T> > >::iterator > DFSstack;
        std::vector<T> ALGOstack;
        std::vector<std::pair<int, int> > low_id;
        int current_index = 0;
        DFSstack.push((*V.cbegin()));
        while (!DFSstack.empty()) {
            DFSstack.push(DFSstack.top()->second->list.next);
            T current = DFSstack.top()->name;
            std::pair<std::map<T, int>, bool> p;
            p = color_map.insert(std::make_pair<T, int>(name, 1));
            if (p.second = false) {// если серая
                p.first->second += 1;
            }

        }


    }*/


};


#endif // GRAPH_H
