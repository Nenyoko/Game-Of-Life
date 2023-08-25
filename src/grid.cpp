#include "grid.h"

#include <algorithm>
#include <raylib.h>

static const Color s_grid_colors[] = {
        RAYWHITE,
        BLACK
};

Grid::Grid(int width, int height) {
    m_width = width;
    m_height = height;
    m_front_buffer = (char*) malloc(sizeof(char) * width * height);
    m_back_buffer = (char*) malloc(sizeof(char) * width * height);

    for (int i = 0; i < m_width * m_height; i++) {
        m_front_buffer[i] = 0;
        m_back_buffer[i] = 0;
    }

    m_front_buffer[1 + 1 * width] = 1;
}

Grid::~Grid() {
    free(m_front_buffer);
    free(m_back_buffer);
}

void Grid::UpdateEdit() {
    float cell_width = (float)GetRenderWidth() / (float)m_width;
    float cell_height = (float)GetRenderHeight() / (float)m_height;

    Vector2 user_pos = GetMousePosition();
    int cell_x = (int)(user_pos.x / cell_width);
    int cell_y = (int)(user_pos.y / cell_height);

    if(cell_x >= 0 && cell_x < m_width && cell_y >= 0 && cell_y < m_height) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            m_front_buffer[cell_x + cell_y * m_width] = 1;
        } else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            m_front_buffer[cell_x + cell_y * m_width] = 0;
        }
    }
}

void Grid::UpdateTick() {
    for (int i = 0; i < m_width*m_height; i++) {
        TickSingleCell(i%m_width, i/m_width);
    }

    std::swap(m_front_buffer, m_back_buffer);
}

void Grid::Draw() {
    float cell_width = (float)GetRenderWidth() / (float)m_width;
    float cell_height = (float)GetRenderHeight() / (float)m_height;

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            DrawRectangleRec(
                    {cell_width*(float)x, cell_height*(float)y, cell_width, cell_height},
                    s_grid_colors[m_front_buffer[x + y * m_width]]);
        }
    }
}

void Grid::Clear() {
    for (int i = 0; i < m_width*m_height; i++) {
        m_front_buffer[i] = 0;
    }
}

char Grid::GetCell(int x, int y) {
    while(x < 0) x += m_width;
    while(x >= m_width) x -= m_width;
    while (y < 0) y += m_height;
    while(y >= m_height) y -= m_height;

    return m_front_buffer[x + y*m_width];
}


void Grid::TickSingleCell(int x, int y) {
    int sum = 0;
    sum += GetCell(x-1, y-1);
    sum += GetCell(x, y-1);
    sum += GetCell(x+1, y-1);
    sum += GetCell(x-1, y);
    sum += GetCell(x+1, y);
    sum += GetCell(x-1, y+1);
    sum += GetCell(x, y+1);
    sum += GetCell(x+1, y+1);

    if (sum == 2) {
        m_back_buffer[x + y*m_height] = m_front_buffer[x + y*m_height];
    } else if (sum == 3){
        m_back_buffer[x + y*m_height] = 1;
    } else {
        m_back_buffer[x + y*m_height] = 0;
    }
}