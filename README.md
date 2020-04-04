# Find the nearest two points in set
-**Algorithm:** Solved by simple "divide and conquer" algorithm. To merge two solution I create **closest_set** of points. Distance between two any points in this set is less than min of two solutions. Than we compare min of two solutions and all distances between points in **closest_set**. Size of **closest_set** is **O(n)** on each iteration, so merge complexity is **O(n)**.  
-**Complexity:** Using Master theorem, **T(n) = O(n*log(n)), M(n) = O(n)**  
-**Build:** Use CMakeLists.txt  
