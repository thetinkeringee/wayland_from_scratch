# Wayland from Scratch

This repository is about learning how Wayland works by writting an applicaiton
without the use of the standard wayland-client libray. It's a work in progress, but
what's not.

## Inspiration

This work has been inspired by the following and probably some I'm missing. I
highly recommend you give them a read. 

* Philippe Gaultier's excelent blog post 
[Learn Wayland by writing a GUI from scratch](https://gaultier.github.io/blog/wayland_from_scratch.html)
* Drew DeVault's [Wayland Book](https://wayland-book.com/) 

## Coding Style 

I'm old. I learned C and C++ before there was an official C++ standard. So, I
like pointers and will use them in places that modern programmers might frown
on. While pointers can have there dangers, they are extremely powerful and can
make for extremely performant code. They can also lead to major problems when
used incorrectly. In the end, none of this matters since this is just a
learning exercise. So, why not use pointers and see if I can avoid segmentation
faults and memory leaks. 

> Note: I am using some C23 so this may not compile on all compilers. 
