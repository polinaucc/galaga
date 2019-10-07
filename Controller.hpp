#pragma once

class ControllerTemplateMethod
{
protected:
    bool is_left, is_right, is_shoot;
public:
    void left_event(bool direction) { is_left = direction; }
    void right_event(bool direction) { is_right = direction; }
    void shoot_event(bool direction) { is_shoot = direction; }
    void discard_events()
    {
        is_left = false;
        is_right = false;
        is_shoot = false;
    }

    virtual void left_action() = 0;
    virtual void right_action() = 0;
    virtual void shoot_action() = 0;

    void process_events()
    {
        if (is_left)
            left_action();
        if (is_right)
            right_action();
        if (is_shoot)
            shoot_action();
    }
};
