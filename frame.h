#ifndef FRAME_H
#define FRAME_H

class Frame {
public:
    Frame(); // Constructor for a new frame
    Frame(const Frame& other); // Copy constructor for duplicating
    ~Frame();
};

#endif // FRAME_H
