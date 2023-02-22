class LinkedList:
    def __init__(self, *args):
        self.head = None
        for i in args:
            self.push_first(i)

                
    # def __repr__(self):
    #     node = self.head
    #     nodes = []
    #     while node is not None:
    #         nodes.append(node.data)
    #         node = node.next
    #     nodes.append("None")
    #     return " -> ".join(nodes)
    
    def push_first(self, data):
        node = Node(data)
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

    def print_slist(self):
        n = self.head
        while n is not None:
            print(n.data, end=" --> ")
            n = n.next
        print("None")

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
    
print()
llist = LinkedList("a", "b", "c", "d", "e",(1,5))
llist.print_slist()
llist.pop_first()
llist.print_slist()

llist.remove_node("c")
llist.print_slist()
print(llist.len())
print(bool(llist))
newl = llist.copy()

newl.print_slist()
rev = newl.reverse()
rev.print_slist()






