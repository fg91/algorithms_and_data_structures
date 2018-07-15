class _StackNode:
    
    def __init__(self, data, nextNode=None):
        self.data = data
        self.next = nextNode
        
    def __str__(self):
        return str(self.data)

class MyStack:
    
    def __init__(self):
        self.top = None
        
    def push(self, data):
        if self.top is None:
            self.top = _StackNode(data)
        else:
            self.top = _StackNode(data, nextNode=self.top)
    
    def pop(self):
        if self.top is None:
            raise ValueError('Stack is Empty')
        item = self.top.data
        self.top = self.top.next
        return item
    
    def peek(self):
        if self.top is None:
            raise ValueError('Stack is Empty')
        return self.top.data
    
    def isEmpty(self):
        return self.top is None

    def __str__(self):
        values = [str(x) for x in self]
        return ' , '.join(values)
    
    def __iter__(self):
        current = self.top
        while current:
            yield current
            current = current.next


