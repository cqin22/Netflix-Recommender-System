#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <vector>
using namespace std;

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    
  public:
    class Iterator {
    public:
        Iterator(vector<ValueType> * v)
        {
            ptr = v;
            m_it = v->begin();
        }
        
        Iterator()
            
        {
            ptr = nullptr;
        }
        
        ValueType& get_value() const {
            return (*m_it);
        }
        
        bool is_valid() const {
            if(!ptr) return false;
            return m_it != ptr->end();
        }
        
        void advance() {
            ++m_it;
        }
        
    private:
        vector<ValueType> * ptr;
        typename std::vector<ValueType>::iterator m_it;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        clear(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        //check root
        if(!m_root){
            m_root = new Node(key, value);
            return;
        }
       
        // insert by comparing keys and inserting if either the key is found or nullptr is found
        Node * node = m_root;
        for(;;){
            if(key == node->m_key){
                node->m_vector.push_back(value);
                return;
            }
            else if(key < node->m_key){
                if(node->left == nullptr){
                    node->left = new Node(key, value);
                    return;
                }
                else node = node->left;
            }
            else{
                if(node->right == nullptr){
                    node->right = new Node(key, value);
                    return;
                }
                else node = node->right;
            }
        }
    }

    
    Iterator find(const KeyType& key) const
    {
        Node* ptr = m_root;
        while(ptr != nullptr){
            if(ptr == nullptr){
                return Iterator();
            }
            else if(key == ptr->m_key){
                return Iterator(&(ptr->m_vector));
            }
            else if(key < ptr->m_key){
                ptr = ptr->left;
            }
            else if(key > ptr->m_key){
                ptr = ptr->right;
            }
        }
        return Iterator();
    }

  private:
    
    struct Node{
        Node(const KeyType& k, const ValueType& v){
            m_key = k;
            m_vector.push_back(v);
        }
        Node(const KeyType& k){m_key = k;}
        KeyType m_key;
        Node* left=nullptr;
        Node* right=nullptr;
        vector<ValueType> m_vector;
    };
    
    Node* m_root;
    
    void clear(Node* node)
    {
        if(!node) return;
        // recusively delete
        clear(node->left);
        clear(node->right);
        delete node;
        }
};

#endif // TREEMULTIMAP_INCLUDED
