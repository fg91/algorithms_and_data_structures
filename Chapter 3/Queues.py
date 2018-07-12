class _QueueNode:
    
    def __init__(self, data, nextNode=None):
        self.data = data
        self.next = nextNode
        
    def __str__(self):
        return str(self.data)

class MyQueue:
    
    def __init__(self):
        self.first = None
        self.last = None
        
    def add(self, data):
        newNode = _QueueNode(data)
        if self.last is not None:
            self.last.next = newNode
        self.last = newNode
        if self.first is None:
            self.first = self.last

    def remove(self):
        if self.first is None:
            raise ValueError('No such element')
        item = self.first.data
        self.first = self.first.next
        if self.first is None:
            self.last = None
        return item
    
    def peek(self):
        if self.first is None:
            raise ValueError('No such element')
        return self.first.data
    
    def isEmpty(self):
        return self.first is None
    
    def __str__(self):
        values = [str(x) for x in self]
        return ' , '.join(values)
    
    def __iter__(self):
        current = self.first
        while current:
            yield current
            current = current.next

