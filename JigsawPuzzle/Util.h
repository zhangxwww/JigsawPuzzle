#ifndef UTIL
#define UTIL

/**
 * ��������ֵ
 * @param t1, t2: ��������ֵ
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
 * ����windows��cmd�����й�����ڵ�����
 * @param row: ���������
 */
void setCurRow(const int row);

#endif // !UTIL
