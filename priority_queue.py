#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2024-03-21 21:19:42
# @Author  : Andy Zhu
# @Version : 1.0.0

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

