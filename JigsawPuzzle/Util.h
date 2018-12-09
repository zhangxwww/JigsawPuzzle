#ifndef UTIL
#define UTIL

template<typename T>
void swap(T & t1, T & t2) {
    if (t1 == t2) {
        return;
    }
    T temp = t1;
    t1 = t2;
    t2 = temp;
}

void clearScreen();

#endif // !UTIL
