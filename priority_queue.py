import heapq
class pq:
    def __init__(self, ):
        self.a = []
    
    def push(self, x):
        heapq.heappush(self.a, x)

    def pop(self):
        return heapq.heappop(self.a)
    
    def top(self):
        return self.a[0]

