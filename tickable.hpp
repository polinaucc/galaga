#ifndef TICKABLE_HPP
#define TICKABLE_HPP


class Tickable
{
public:
  ~Tickable()
    {};
    virtual void on_tick() =0;
};

#endif // TICKABLE_HPP
