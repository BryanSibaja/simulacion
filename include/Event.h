#ifndef EVENT_H
#define EVENT_H


class Event {
public:
  Event(int e, float t) : evento(e), tiempo(t){}
    int evento;
    float tiempo;
};

inline bool operator<(const Event& a, const Event& b) {
    return a.tiempo > b.tiempo;
}


#endif // EVENT_H
