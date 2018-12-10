#ifndef UTIL
#define UTIL

/**
 * 交换两个值
 * @param t1, t2: 待交换的值
 */
template<typename T>
void swap(T & t1, T & t2) {
    if (t1 == t2) {
        return;
    }
    T temp = t1;
    t1 = t2;
    t2 = temp;
}


/**
 * 设置windows下cmd窗口中光标所在的行数
 * @param row: 光标所在行
 */
void setCurRow(const int row);

#endif // !UTIL
