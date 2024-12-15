#!/usr/bin/env python3
# min_heap_priority_queue.py

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

from heap_priority_queue import HeapPriorityQueue


class MinHeapPriorityQueue(HeapPriorityQueue):

    def __init__(self, get_key_func, set_key_func=None):
        """Initialize a minimum priority queue implemented with a heap.

        Arguments:
        get_key_func -- required function that returns the key for the
        objects stored. May be a static function in the object class.
        set_key_func -- optional function that sets the key for the objects
        stored. May be a static function in the object class.
        """
        HeapPriorityQueue.__init__(self, lambda x, y: x < y, float('inf'), get_key_func, set_key_func)

    def minimum(self):
        """Return the object with the minimum key in a heap."""
        return self.top_of_heap()

    def extract_min(self):
        """Return and delete the object with the minimum value in a heap."""
        return self.extract_top()

    def decrease_key(self, x, k):
        """Decrease the key of object x to value k.  Error if k is greater than x's current key.
            Update the heap structure appropriately.

        Arguments:
        x -- object whose key has been decreased
        k -- new key of x
        """

        if k > self.get_key(x):
            raise RuntimeError("Error in decrease_key: new key " + str(k)
                               + " is greater than current key " + str(x.get_key()))

        # Make the changes in the heap.
        self.update_key(x, k)

    def insert(self, x):
        """Insert x into the min heap.  Grows the heap as necessary."""
        HeapPriorityQueue.insert(self, x)
