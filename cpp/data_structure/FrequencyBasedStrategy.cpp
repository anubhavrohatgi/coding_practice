/**
 *  Frequency-based, or so-call counter-based strategy. every put() and get() will lead corresponding object counter+1.
 *  When the cache is full, evict the one with smallest count. If there are multiple, just evict any of them
 *
 *  For example, cache size = 3, objects (key, value, count) are ("abc", "x", 5), ("bcd", "y", 3), ("cde", "z", 2)
 *  if we execute put("def", "xx"), ("cde", "z", 2) will be evicted, therefore the obejects become ("abc", "x", 5), ("bcd", "y", 3), put("def", "xx")
 *
 *  At first I use the hash + min heap, where heap stores the objects, ordering by it's count, and map is similar to LRU, where map->key = key,
 *  map->value = pointer that points to the object in the min heap.
 *  The problem of this approach is that when you touch a object, here touch is either put() or get(), we need to increase the object's count by 1.
 *  However, after the increment, we will need to do a bubble_down function on the object, but most of the programming languages I know do not support
 *  this function. That means I need to implement my own heap.
 *  Furthermore, the time complexity will be O(lgK) on both put() and get(), where K is the cache size. Because we need to call bubble_down() for both
 *  operation. The time complexity is not ideal.
 *
 *  Better approach will be similar to LRU implementation. In LRU, we put the latest element in the front of the doubly linked list, second latest element
 *  in the second position of the doubly linked list, and so on. Now for frequency-based, we put the object with largest count in the front of dll, object
 *  with second largest count in the second postion, and so on. When the cache is full and we need to evict the element, we just remove the very last element
 *  from the dll. 
 *  One concern raised, when we touch an object, we need to increase the count. And because the count becomes larger, we need to move the object forward.
 *  Image the dll:
 *  
 *  O1 - O2 - O3 - O4 - O5 - O6
 *  13 - 10 - 10 - 10 - 10 - 2
 * 
 *  Object 1 has count = 11, obj2 has count = 10, and so on. Say now we touch O5, then the count for O5 becomes 11. It means that we need to reorder the
 *  object. Simply move forward until we see the count which is slightly greater than 11 will lead O(k) time complexity, even worse than min heap approach.
 *  Even if we can use skip list to optimize the search, we still need O(lgK) to find the insert position.
 *
 *  But here is an idea - why don't we group up the objects that have same count. So now the dll is storing groups but objects. Take above dll for exmample,
 *  it will become:
 *
 *  G1 - G2 - G3
 *  13 - 10 - 2
 *
 *  Where we group up O2 ~ O5 to G2, and once we touch O5, we just need to see if the increment count is equal to the count of previous group. If it is 
 *  equal, just join the group, if not, create another group with the count and insert the group in the middle. Of course with this approach, you need to 
 *  either store GroupNode *belongs_to_group in the object node, or use a int->GroupNode* map to locate the group node. But it works. And the time complexity 
 *  will be O(1) for both get() and put() because you either need to join the previous group, or create a new group and insert in the middle. It guarantees 
 *  the ordering and running time is also ideal.
 */ 

#include <iostream>
#include <utility>
#include <unordered_map>
#include <list>
#include "Strategy.h"

using namespace std;

class FrequencyBasedStrategy : public Strategy {
	// inherit constructor
	using Strategy::Strategy;

};
