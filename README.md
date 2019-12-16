# A Simple Database Made in C

This simple C database is based on the tutorial by cstack found here (https://cstack.github.io/db_tutorial/).

## Additions

Additions to the tutorial, that I have done on my own are:

* **Refactoring:** The original tutorial was composed of a single C file. To make it more readable / understandable, I added a make file and paritioned the code into multiple different files. The program all supports two `DEBUG` modes to make development and testing easier.

* **Alternative Display:** In the tutorial the B+ Tree was displayed using a _depth first traversal_ I added a _breadth first traversal_ as well to provide a atlernative view of the tree.

* **Internal Node Splitting:** This was the most challenging addition. The tutorial (as of December 16th, 2019) left off with implementing the internal node splitting. After tons of research in B+ trees, the database can now handle `TABLE_MAX_PAGES` pages, and effitiantly sort them.

