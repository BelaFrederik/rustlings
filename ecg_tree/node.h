#include <string>
#include <vector>

class Node {
    public:
    Node(const std::string& name);

    virtual ~Node();

    std::string get_name() const;
    void set_name(const std::string& new_name);
    int get_nr_children() const;

    Node* get_child(int i) const;
    void add_child(Node* child);

    void print(std::ostream& str, int depth) const;

    void safe_print(std::ostream& str, int depth, std::vector<Node*> checked);
    void safe_print_it(std::ostream& str);

    friend std::ostream& operator<<(std::ostream& os,  Node& obj);

    private:

    std::string name;
    std::vector<Node*> children;
    static int node_id;

};

