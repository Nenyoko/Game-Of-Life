#ifndef GAMEOFLIFE_GRID_H
#define GAMEOFLIFE_GRID_H


class Grid {
public:
    Grid(int width, int height);
    ~Grid();

    void UpdateEdit();
    void UpdateTick();
    void Draw();
    void Clear();

    char GetCell(int x, int y);

private:
    void TickSingleCell(int x, int y);


    char* m_front_buffer;
    char* m_back_buffer;
    int m_width, m_height;

};


#endif //GAMEOFLIFE_GRID_H
