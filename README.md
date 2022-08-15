# search-tree

![visualisation of the tree data structure](imgs/visualization.jpg)

## Overview
Inspired by Twitch chat's emote hinting (i.e. 'Coo' gets filled to 'CoolCat' when pressing TAB)

This tree data structure is useful for finding all kept words given the prefix.
Hopefully should be much faster than using other data structures, such as vectors.

Visualisation of this data structure is shown in the picture above.

## Installing from source
**WARNING:** make sure `git`, `cmake` and `make` is installed on your computer.

In order to use the library, we need to install it first. Here's how to compile and install it from source.

Clone the source code of the library:
```shell
$ git clone https://github.com/Piggey/search-tree.git
$ cd search-tree
```

Now we need to compile the source:
```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

The library should be compiled now. Now to install it to your personal computer:
```shell
$ sudo make install
```

All needed files should be installed to the default directory. 
(`/usr/local/` for UNIX systems, `c:/Program Files/search-tree` for Windows) 
You should be able to use it in your own programs now!

## Getting started
Typical use case of `Tree` class would look like as such:
```c++
#include <search-tree/Tree.h>

st::Tree t;
t.put("bar"); // puts the word "baz" into a tree object t
t.put("baz"); // same with "bar"

// returns a vector of all words in a tree object with this prefix
t.find("ba"); // returns: { "bar", "baz" }

/* SINCE VERSION 1.2.0 */
// you can now ignore case sensitivity when searching for a word
t.put("BAR");
t.find("bar", true); // returns: { "bar", "BAR" }
```

Alternatively, we can initialize a `Tree` object with a list of words to be put inside.
```c++
#include <search-tree/Tree.h>

st::Tree t({ "bar", "baz" }); // puts all words from the list to the tree

t.find("ba"); // returns: { "baz", "bar" }
```

## Functionality
`Tree` class' API:
- `Tree.put(word)` - puts given word into a tree object and increments word counter.
- `Tree.remove(word)` - removes given word from a tree and decrements word counter. Does nothing if word wasn't there to begin with.
- `Tree.find(prefix)` - find and return a vector of all stored words with given prefix. Returns empty vector if there's none.
- `Tree.size()` - returns a number of stored words in a tree object.

## Problems with current implementation
Problems that I'll try to fix in the next version of this project.

### Not sharing nodes

Consider a case when we try to put "Ba" and "Da" into a tree.

That object would look like this:

![visualisation of a bad case](imgs/bad_case.jpg)

As you can see, the 'a' node is being created for every parent node. This is BAD!
This means that memory size of the Tree object will grow exponentially.

Instead, both nodes 'B' and 'D' should use the same 'a' node.

**Update:** either I'm very dumb, or joining nodes like that would dramatically slow down the searching,
which is the main point of this data structure, so I decided to keep it as is.
