#ifndef ARCHIVE
#define ARCHIVE

#include <string>

class Archive {
public:
    Archive();
    Archive(const std::string & name,
        const int row, const int col,
        int * matrix);
    ~Archive();

    const std::string name;
    const int row;
    const int col;
    int * matrix;
};

#endif // !ARCHIVE
