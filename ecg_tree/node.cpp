#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stack>
#include "node.h"

int Node::node_id = 0;

Node::Node(const std::string &name)
: name(name) {
    node_id++;
    if (name.empty()) {
        std::stringstream str_sm;
        str_sm << node_id;
        std::string node_id_str = str_sm.str();
        Node::name = "node_"+node_id_str;
    }
}

Node::~Node() {
    std::cout << "enter ~node() of \"" <<name << "\"" << std::endl;
    for (Node* child : children) {
        delete child;
    }
    std::cout << "leave ~node() of \"" <<name << "\"" << std::endl;
}

std::string Node::get_name() const {
    return name;
}

void Node::set_name(const std::string& new_name) {
    Node::name = new_name;
}

void Node::add_child(Node *child) {
    children.push_back(child);
}

int Node::get_nr_children() const {
    return children.size();
}

Node* Node::get_child(int i) const {
    if( i >= 0 && i < children.size()){
        return children[i];
    }
    return nullptr;
}

void Node::print(std::ostream& str, int depth) const {
    for(int d = 0; d < depth;d++){
        str << "    ";
    }
    str << name<< std::endl;
    for (Node* child : children ){
        child->print(str, depth+1);
    }
}

void Node::safe_print(std::ostream& str, int depth, std::vector<Node*> checked)  {
    for(int d = 0; d < depth;d++){
        str << "    ";
    }
    str << name<< std::endl;
    checked.push_back(this);


    for (Node* child : children ){
        if (std::find(checked.begin(), checked.end(), child) != checked.end()) {
        }else{
            child->safe_print(str, depth+1,checked);
        }
    }
}

std::ostream &operator<<(std::ostream &str, Node &obj) {
        //obj.print(str,0);
        std::vector<Node*> checked;
        //obj.safe_print(str,0, checked);
        obj.safe_print_it(str);
        return str;
}

void Node::safe_print_it(std::ostream &str) {
    str << name<< std::endl;
    std::stack<Node*> stack;
    std::vector<Node*> checked;
    checked.push_back(this);
    Node* active = this;
    bool run = true;
    int depth = 0;
    while (depth >= 0) {
        for (Node* child : this->children){
            if (std::find(checked.begin(), checked.end(), child) != checked.end()) {
            }else{
                for(int d = 0; d < depth;d++){
                    str << "    ";
                }
                str << child->name<< std::endl;
                checked.push_back(child);
                
                stack.push(active);
                active = child;
            }
        }
        active = stack.top();
        stack.pop();
        depth -= 1;
    }
}

Node* create_complete_tree(int nr_child_nodes, int tree_depth){
    if (tree_depth >= 2) {
        Node* tree =  new Node("");
        for (int i = 0; i < nr_child_nodes;i++){
            Node* node = create_complete_tree(2, tree_depth - 1);
            tree->add_child(node);
        }
        return tree;
    }else{
        Node* node = new Node("");
        return node;
    }
}






