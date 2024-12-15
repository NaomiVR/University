#!/usr/bin/env python3
# dijkstra.py

# Introduction to Algorithms, Fourth edition
# Linda Xiao and Tom Cormen

#########################################################################
#                                                                       #
# Copyright 2022 Massachusetts Institute of Technology                  #
#                                                                       #
# Permission is hereby granted, free of charge, to any person obtaining #
# a copy of this software and associated documentation files (the       #
# "Software"), to deal in the Software without restriction, including   #
# without limitation the rights to use, copy, modify, merge, publish,   #
# distribute, sublicense, and/or sell copies of the Software, and to    #
# permit persons to whom the Software is furnished to do so, subject to #
# the following conditions:                                             #
#                                                                       #
# The above copyright notice and this permission notice shall be        #
# included in all copies or substantial portions of the Software.       #
#                                                                       #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       #
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    #
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                 #
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS   #
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN    #
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN     #
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE      #
# SOFTWARE.                                                             #
#                                                                       #
#########################################################################

from min_heap_priority_queue import MinHeapPriorityQueue
from single_source_shortest_paths import initialize_single_source, relax


def dijkstra(G, s):
    """Solve single-source shortest-paths problem with no negative-weight edges.

    Arguments:
    G -- a directed, weighted graph
    s -- index of source vertex
    Assumption:
    All weights are nonnegative

    Returns:
    d -- distances from source vertex s
    pi -- predecessors
    """

    card_V = G.get_card_V()

    d, pi = initialize_single_source(G, s)

    # Key function for the priority queue is distance.
    queue = MinHeapPriorityQueue(lambda u: d[u])
    for u in range(card_V):
        queue.insert(u)

    while queue.get_size() > 0:  # while the priority queue is not empty
        u = queue.extract_min()  # extract a vertex with the minimum distance

        # Relax each edge and update d and pi.
        for edge in G.get_adj_list(u):
            v = edge.get_v()
            # Upon each relaxation, decrease the key in the priority queue.
            relax(u, v, edge.get_weight(), d, pi, lambda v: queue.decrease_key(v, d[u] + edge.get_weight()))

    return d, pi
