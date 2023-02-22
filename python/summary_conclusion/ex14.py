class LinkedList:
    def __init__(self, nodes=None):
        self.head = None
        if nodes is not None:
            node = Node(data=nodes.pop(0))
            self.head = node
            for elem in nodes:
                node.next = Node(data=elem)
                node = node.next
                
    def __repr__(self):
        node = self.head
        nodes = []
        while node is not None:
            nodes.append(node.data)
            node = node.next
        nodes.append("None")
        return " -> ".join(nodes)
    
    def push_first(self, node):
        node.next = self.head
        self.head = node
        
    def pop_first(self):
        self.head = self.head.next
        return
        
    def remove_node(self, target_node_data):
        if self.head is None:
            print("List is empty")
            return
        if self.head.data == target_node_data:
            self.head = self.head.next
            return
        if None == target_node_data:
            print("kfotz")
            return
        previous_node = self.head
        for node in self:
            if node.data == target_node_data:
                previous_node.next = node.next
                return
            previous_node = node
            print("no data was found")
            
    def __iter__(self):
        node = self.head
        while node is not None:
            yield node
            node = node.next
    def __bool__(self):
        return self.head is None      
    def len(self):
        return (len(list(self)))
    

    def reverse(self):
        new_list = LinkedList()
        for node in self:
            new_node = Node(node.data)
            new_list.push_first(new_node)
        return new_list
    
    def copy(self):
        rev = self.reverse()
        return rev.reverse()

class Node:
    def __init__(self, data):
        self._data = data
        self._next = None

    @property
    def data(self):
        return self._data

    @data.setter
    def data(self, new_data):
        self._data = new_data

    @property
    def next(self):
        return self._next

    @next.setter
    def next(self, new_next):
        self._next = new_next

    def __repr__(self):
        return str(self.data)
    
    def copy(self):
        return Node(self.data)  
    
llist = LinkedList()
print(bool(llist))
llist = LinkedList(["a", "b", "c", "d", "e"])

llist.push_first(Node("F"))
print(llist)
print(llist.len())
llist.pop_first()
llist.remove_node(None)
print(llist)
print(llist.len())
print(bool(llist))
newl = llist.copy()

print(newl)

